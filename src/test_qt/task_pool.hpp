#ifndef TASK_POOL_HPP_
#define TASK_POOL_HPP_

#include "base/bind.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/sequenced_worker_pool.h"
#include "base/synchronization/waitable_event.h"
#include "base/threading/thread.h"
#include "base/timer/timer.h"
#include "global_def.h"

#include <qdebug.h>
#include <vector>
#include <string>


class Foo 
    : public base::RefCountedThreadSafe<Foo> {
public:
    Foo(size_t t, base::WaitableEvent* e)
        : worker_pool_(new base::SequencedWorkerPool(t, "fangr_")),
          complete_(false, true),
          event_(e) {
        VideoInfo f1;
        f1.piece = {"f1_p1", "f1_p2", "f1_p3"};
        video_map_["file1"] = f1;

        VideoInfo f2;
        f2.piece = {"f2_p1"};
        video_map_["file2"] = f2;

        VideoInfo f3;
        f3.piece = {"f3_p1", "f3_p2", "f3_p3", "f3_p4", "f3_p5", "f3_p6"};
        video_map_["file3"] = f3;
    }

    void stop() {
        worker_pool_->Shutdown();
    }

    void upload_file(const std::string& file_name) {
        token_ = worker_pool_->GetNamedSequenceToken(file_name);

        name_ = file_name;

        size_t& pos = video_map_[name_].offset;
        size_t sz = video_map_[name_].piece.size();

        while (true) {
            event_->Wait();
            complete_.Wait();

            worker_pool_->PostSequencedWorkerTaskWithShutdownBehavior(token_, FROM_HERE, 
                base::Bind(&Foo::DoWork, this, video_map_[name_].piece[pos]), 
                base::SequencedWorkerPool::CONTINUE_ON_SHUTDOWN);
            ++pos;
            if (pos >= sz)  pos = pos % sz;
        }
        
    }

private:

    void DoWork(std::string p) {
        //::Sleep(5000);
        qDebug("file_piece: %s", p.c_str());
        complete_.Signal();
    }


private:
    scoped_refptr<base::SequencedWorkerPool> worker_pool_;

    base::SequencedWorkerPool::SequenceToken token_;

    std::string name_;

    std::map<std::string, VideoInfo> video_map_;

    base::WaitableEvent* event_;

    base::WaitableEvent complete_;
};

#endif // !TASK_POOL_HPP_