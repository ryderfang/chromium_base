#ifndef TASK_POOL_HPP_
#define TASK_POOL_HPP_

#include "base/bind.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/sequenced_worker_pool.h"
#include "base/synchronization/waitable_event.h"
#include "base/threading/thread.h"
#include "base/timer/timer.h"

#include <qdebug.h>

#include <vector>
#include <string>

class Foo 
    : public base::RefCountedThreadSafe<Foo> {
public:
    Foo(size_t t)
        : worker_pool_(new base::SequencedWorkerPool(t, "fangr_")),
          event_(false, false),
          timer_(true, false) {
    }

    void stop() {
        worker_pool_->Shutdown();
    }

    void start_agagin() {
        timer_.Reset();
    }

    void pause() {
        timer_.Stop();
    }

    void upload_file(const std::string& file) {
        timer_.Start(FROM_HERE, base::TimeDelta::FromMilliseconds(1), 
        base::Bind(&Foo::ScheduleWork, this));
        base::SequencedWorkerPool::SequenceToken token = worker_pool_->GetSequenceToken();
        for (int i = 0; i < file.size(); ++i) {
            event_.Wait();

            worker_pool_->PostSequencedWorkerTaskWithShutdownBehavior(token, FROM_HERE, 
                base::Bind(&Foo::DoWork, this, i, file[i]), base::SequencedWorkerPool::CONTINUE_ON_SHUTDOWN);
        }
    }

private:
    void DoWork(int id, char p) {
        ::Sleep(500);
        qDebug("file_%d_piece:%c", id, p);
    }

    void ScheduleWork() {
        event_.Signal();
    }

private:
    scoped_refptr<base::SequencedWorkerPool> worker_pool_;

    base::WaitableEvent event_;

    base::Timer timer_;
};

#endif // !TASK_POOL_HPP_