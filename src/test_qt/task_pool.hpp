#ifndef TASK_POOL_HPP_
#define TASK_POOL_HPP_

#include "base/bind.h"
#include "base/memory/scoped_ptr.h"
#include "base/synchronization/waitable_event.h"
#include "base/threading/sequenced_worker_pool.h"
#include "base/threading/thread.h"
#include "base/timer/timer.h"
#include "global_def.h"

#include <qdebug.h>
#include <vector>
#include <string>

class Foo 
    : public base::RefCountedThreadSafe<Foo> {
public:

    class TaskObserver {
    public:
        TaskObserver() {}

        virtual void NotifyProgress(const std::string& name, int pos) = 0;

    protected:
        virtual ~TaskObserver() {};
    };

    Foo(size_t t, base::WaitableEvent* e)
        : worker_pool_(new base::SequencedWorkerPool(t, "fangr_")),
          complete_(false, true),
          event_(e) {
        VideoInfo f1;
        f1.piece.resize(100, "file1");
        video_map_["file1"] = f1;

        VideoInfo f2;
        f2.piece.resize(200, "fiel2");
        video_map_["file2"] = f2;

        VideoInfo f3;
        f3.piece.resize(1000, "file3");
        video_map_["file3"] = f3;
    }

    void add_observer(TaskObserver* ob) {
        observer_ = ob;
    }

    void stop() {
        worker_pool_->Shutdown();
    }

    void upload_file(const std::string& file_name) {
        token_ = worker_pool_->GetNamedSequenceToken(file_name);

        name_ = file_name;

        size_t& pos = video_map_[name_].offset;
        size_t sz = video_map_[name_].piece.size();

        while (pos < sz) {
            event_->Wait();
            complete_.Wait();

            double radio = (double) pos / sz * 100;
            observer_->NotifyProgress(file_name, (int)(radio));

            worker_pool_->PostSequencedWorkerTaskWithShutdownBehavior(token_, FROM_HERE, 
                base::Bind(&Foo::DoWork, this, pos, video_map_[name_].piece[pos]), 
                base::SequencedWorkerPool::CONTINUE_ON_SHUTDOWN);
            ++pos;
        }
    }

private:

    void DoWork(size_t pos, std::string p) {
        ::Sleep(500);
        qDebug("%s--%d", p.c_str(), pos);
        complete_.Signal();
    }


private:
    scoped_refptr<base::SequencedWorkerPool> worker_pool_;

    base::SequencedWorkerPool::SequenceToken token_;

    std::string name_;

    std::map<std::string, VideoInfo> video_map_;

    base::WaitableEvent* event_;

    base::WaitableEvent complete_;

    TaskObserver* observer_;
};

#endif // !TASK_POOL_HPP_