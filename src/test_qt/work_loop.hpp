#ifndef WORK_LOOP_
#define WORK_LOOP_

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/message_loop/message_loop.h"
#include "base/run_loop.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread.h"
#include "base/synchronization/lock.h"
#include "base/synchronization/waitable_event.h"
#include "base/timer/timer.h"

#include "global_def.h"
#include "task_pool.hpp"

#include <map>
#include <queue>
#include <string>

#define MAX_UPLOADING_COUNT 2

class WorkLoop :
    public QObject,
    public base::RefCountedThreadSafe<WorkLoop>,
    public WorkDelegate {
    Q_OBJECT

public:
    WorkLoop() : is_stop(false) {
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

        running_thread_ = new base::Thread("Running Thread");
        if (!running_thread_->IsRunning()) {
            running_thread_->Start();
        }
        running_thread_->message_loop()->PostTask(FROM_HERE,
            base::Bind(&WorkLoop::AutoRun, this));
    }

    void Start(const std::string& file_name) {
        work_thread_->message_loop()->PostTask(FROM_HERE,
            base::Bind(&WorkLoop::ScheduleTask, this, file_name));
    }

    void Pause(const std::string& file_name) {
        /*schedule_thread_->message_loop()->PostTask(FROM_HERE, 
            base::Bind(&WorkLoop::StopTimer, this));*/
    }

    void Stop() {
        is_stop = true;

        work_thread_->message_loop()->PostTask(FROM_HERE, 
            base::Bind(&Foo::stop, task_pool_));
    }

    void CompleteOne(const std::string& name, int offset) {
        base::AutoLock auto_lock(lock_);
        // check all pieces complete of file [name] then pop
        for (std::vector<std::string>::iterator i = running_tasks_.begin(); 
            i < running_tasks_.end(); ++i) {
            if (*i == name) {
                if (offset + 1 < video_map_[name].sz()) {
                    video_map_[name].offset++;
                    task_pool_->upload_one(name, offset+1, video_map_[name].piece[offset+1]);
                } else {
                    running_tasks_.erase(i);
                    break;
                }
            }
        }
    }

    void NotifyProgress(const std::string& name, int pos) {
        int p = pos;
        emit update_progress(pos);
    }

    void PushData(const std::string& name, const VideoInfo& info) {
        video_map_[name] = info;
    }

signals:
    void update_progress(int pos);

private:
    void InitTaskPool() {
        task_pool_ = new Foo(MAX_UPLOADING_COUNT, this);
    }

    void ScheduleTask(const std::string& name) {
        {
            base::AutoLock auto_lock(lock_);
            if (running_tasks_.size() < MAX_UPLOADING_COUNT) {
                running_tasks_.push_back(name);
                int offset = video_map_[name].offset;
                task_pool_->upload_one(name, offset, video_map_[name].piece[offset]);
            }
            else {
                waiting_tasks_.push(name);
            }
        }
    }

    void AutoRun() {
        while (true) {
            if (is_stop) break;
            base::AutoLock auto_lock(lock_);
            if (!waiting_tasks_.empty() && running_tasks_.size() < MAX_UPLOADING_COUNT) {
                std::string name = waiting_tasks_.front();
                running_tasks_.push_back(name);
                int offset = video_map_[name].offset;
                work_thread_->message_loop()->PostTask(FROM_HERE, 
                    base::Bind(&Foo::upload_one, task_pool_, name, offset, video_map_[name].piece[offset]));
                waiting_tasks_.pop();
            }
        }
    }

private:
    scoped_refptr<Foo> task_pool_;

    base::Thread* work_thread_;

    base::Thread* running_thread_;

    mutable base::Lock lock_;

    bool is_stop;

    std::map<std::string, VideoInfo> video_map_;

    std::queue<std::string> waiting_tasks_;

    std::vector<std::string> running_tasks_;

    DISALLOW_COPY_AND_ASSIGN(WorkLoop);
};

#endif // !WORK_LOOP_