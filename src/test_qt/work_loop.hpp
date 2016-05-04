#ifndef WORK_LOOP_
#define WORK_LOOP_

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/message_loop/message_loop.h"
#include "base/run_loop.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread.h"

#include "task_pool.hpp"

#include <string>

class WorkLoop {
public:
    WorkLoop() {
        main_task_thread_ = new base::Thread("main task");
        if (!main_task_thread_->IsRunning()) {
            main_task_thread_->Start();
        }

        main_task_thread_->message_loop()->PostTask(FROM_HERE, 
            base::Bind(&WorkLoop::Run, base::Unretained(this)));
    }

    ~WorkLoop() {
        
    }

    void DoWork(const std::string& file) {
        task_pool_->upload_file(file);
    }

    void Continue() {
        main_task_thread_->message_loop()->PostTask(FROM_HERE,
            base::Bind(&Foo::start_agagin, task_pool_));
    }

    void Pause() {
        main_task_thread_->message_loop()->PostTask(FROM_HERE,
            base::Bind(&Foo::pause, task_pool_));
    }
        
    void Run() {
        task_pool_ = new Foo(5);
    }

    void Stop() {
        main_task_thread_->message_loop()->PostTask(FROM_HERE,
            base::Bind(&Foo::stop, task_pool_));
    }

private:
    base::Thread* main_task_thread_;

    scoped_refptr<Foo> task_pool_;

    DISALLOW_COPY_AND_ASSIGN(WorkLoop);
};

#endif // !WORK_LOOP_