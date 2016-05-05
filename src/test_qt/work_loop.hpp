#ifndef WORK_LOOP_
#define WORK_LOOP_

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/message_loop/message_loop.h"
#include "base/run_loop.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread.h"
#include "base/synchronization/waitable_event.h"
#include "base/timer/timer.h"

#include "task_pool.hpp"

#include <map>
#include <string>

class WorkLoop :
    public base::RefCountedThreadSafe<WorkLoop> {
public:
    WorkLoop(): event_(false, false),
                timer_(true, true) {
    }

    ~WorkLoop() {
    }

    void Init() {
        work_thread_ = new base::Thread("Work Thread");
        if (!work_thread_->IsRunning()) {
            work_thread_->Start();
        }
        work_thread_->message_loop()->PostTask(FROM_HERE, 
            base::Bind(&WorkLoop::InitTaskPool, this));

        control_thread_ = new base::Thread("Control Thread");
        if (!control_thread_->IsRunning()) {
            control_thread_->Start();
        }
        control_thread_->message_loop()->PostTask(FROM_HERE, 
            base::Bind(&WorkLoop::InitTimer, this));
    }

    void Start(const std::string& file_name) {
        control_thread_->message_loop()->PostTask(FROM_HERE, 
            base::Bind(&WorkLoop::ResetTimer, this));

        work_thread_->message_loop()->PostTask(FROM_HERE, 
            base::Bind(&Foo::upload_file, task_pool_, file_name));
    }

    void Pause(const std::string& file_name) {
        control_thread_->message_loop()->PostTask(FROM_HERE, 
            base::Bind(&WorkLoop::StopTimer, this));
    }

    void Stop() {
        work_thread_->message_loop()->PostTask(FROM_HERE, 
            base::Bind(&Foo::stop, task_pool_));
    }

private:
    void InitTaskPool() {
        task_pool_ = new Foo(2, &event_);
    }

private:
    void InitTimer() {
        timer_.Start(FROM_HERE, base::TimeDelta::FromMicroseconds(1), 
            base::Bind(&WorkLoop::ScheduleTask, this));
        timer_.Reset();
    }

    void ScheduleTask() {
        event_.Signal();
    }

    void ResetTimer() {
        timer_.Reset();
    }

    void StopTimer() {
        timer_.Stop();
    }

private:
    scoped_refptr<Foo> task_pool_;

    base::Thread* work_thread_;

    base::Thread* control_thread_;

    base::WaitableEvent event_;

    base::Timer timer_;

    DISALLOW_COPY_AND_ASSIGN(WorkLoop);
};

#endif // !WORK_LOOP_