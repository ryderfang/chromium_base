#ifndef TASK_POOL_HPP_
#define TASK_POOL_HPP_

#include "base/bind.h"
#include "base/memory/scoped_ptr.h"
#include "base/message_loop/message_loop.h"
#include "base/threading/sequenced_worker_pool.h"
#include "base/threading/platform_thread.h"
#include "base/threading/thread.h"
#include "base/time/time.h"
#include "global_def.h"

#include <qdebug.h>
#include <vector>
#include <string>

class WorkDelegate {
public:
    WorkDelegate()  {}

    virtual void CompleteOne(const std::string& name, int offset, int64 cost) = 0;

protected:
    ~WorkDelegate() {} ;
};

class Foo 
    : public base::RefCountedThreadSafe<Foo> {
public:
    Foo(size_t t, WorkDelegate* loop)
        : worker_pool_(new base::SequencedWorkerPool(t, "fangr_")),
          delegate_(loop),
          cost_(0) {
    }

    void stop() {
        worker_pool_->Shutdown();
    }

    void upload_one(const std::string& name, int offset, const std::string& piece) {
        worker_pool_->PostTaskAndReply(FROM_HERE, 
            base::Bind(&Foo::DoUpload, this, name, offset, piece),
            base::Bind(&WorkDelegate::CompleteOne, base::Unretained(delegate_), name, offset, cost_));
    }

private:
    void DoUpload(const std::string& name, int offset, const std::string& piece) {
        base::TimeTicks start = base::TimeTicks::Now();
        ::Sleep(500);
        qDebug() << name.c_str() << " " << piece.c_str() << "--" << base::PlatformThread::GetName();
        cost_ = (base::TimeTicks::Now() - start).ToInternalValue();
    }

private:
    scoped_refptr<base::SequencedWorkerPool> worker_pool_;

    WorkDelegate* delegate_;

    int64 cost_;

    DISALLOW_COPY_AND_ASSIGN(Foo);
};

#endif // !TASK_POOL_HPP_