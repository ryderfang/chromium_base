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

    virtual void CompleteOne(const std::string& name, int offset, std::wstring* cost) = 0;

protected:
    ~WorkDelegate() {} ;
};

class Foo 
    : public base::RefCountedThreadSafe<Foo> {
public:
    Foo(size_t t, WorkDelegate* loop)
        : worker_pool_(new base::SequencedWorkerPool(t, "fangr_")),
          delegate_(loop) {
    }

    void stop() {
        worker_pool_->Shutdown();
    }

    void upload_one(const std::string& name, int offset, const std::string& piece) {
        //int64* cost = new int64(base::TimeTicks::Now().ToInternalValue());
        std::wstring* cost = new std::wstring();
        //worker_pool_->PostTaskAndReply(FROM_HERE, 
        //    base::Bind(&Foo::DoUpload, this, name, offset, piece, cost),
        //    base::Bind(&WorkDelegate::CompleteOne, base::Unretained(delegate_), name, offset, base::Owned(cost)));
        worker_pool_->PostTask(FROM_HERE,
            base::Bind(&Foo::DoUpload, this, name, offset, piece, cost));
    }

private:
    void DoUpload(const std::string& name, int offset, const std::string& piece, std::wstring* cost) {
        ::Sleep(500);
        qDebug() << name.c_str() << " " << piece.c_str() << "--" << base::PlatformThread::GetName();
        //*cost = base::TimeTicks::Now().ToInternalValue() - *cost;
        *cost = L"Shit!!";
    }

private:
    scoped_refptr<base::SequencedWorkerPool> worker_pool_;

    WorkDelegate* delegate_;

    DISALLOW_COPY_AND_ASSIGN(Foo);
};

#endif // !TASK_POOL_HPP_