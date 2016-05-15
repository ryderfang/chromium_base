#ifndef WORK_LOOP_
#define WORK_LOOP_

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/message_loop/message_loop.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread.h"

#include "task_pool.hpp"

#include <map>
#include <queue>
#include <set>
#include <string>

#define MAX_UPLOADING_COUNT 3

namespace {
template <class T>
typename T::iterator safety_erase(T& container, typename T::const_iterator pos) {
    if (pos != container.end()) {
        return container.erase(pos);
    }
    return container.end();
}
} // namespace

class WorkLoop :
    public QObject,
    public base::RefCountedThreadSafe<WorkLoop>,
    public WorkDelegate {
    Q_OBJECT

public:
    WorkLoop() : is_stop_(false) {
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

    void Start(const std::string& name) {
        work_thread_->message_loop()->PostTask(FROM_HERE,
            base::Bind(&WorkLoop::ScheduleTask, this, name));
    }

    void Pause(const std::string& name) {
        work_thread_->message_loop()->PostTask(FROM_HERE,
            base::Bind(&WorkLoop::PauseOne, this, name));
    }

    void Delete(const std::string& name) {
        work_thread_->message_loop()->PostTask(FROM_HERE,
            base::Bind(&WorkLoop::DeleteOne, this, name));
    }

    void Stop() {
        is_stop_ = true;

        work_thread_->message_loop()->PostTask(FROM_HERE, 
            base::Bind(&Foo::stop, task_pool_));
    }

    void CompleteOne(const std::string& name, int offset, std::wstring* cost) {
        base::AutoLock auto_lock(lock_);
        auto it = running_tasks_.find(name);
        // stoped
        if (!video_map_.count(name)) {
            safety_erase(running_tasks_, it);
            // needless
            emit update_progress(name, 0, 0);
            return;
        }

        int pos = (double)(offset + 1) / video_map_[name].sz() * 100;
        qDebug() << cost->c_str();
        //emit update_progress(name, pos, *cost);
        
        // paused
        if (it == running_tasks_.end())  {
            return;
        }

        video_map_[name].offset = ++offset;

        if (offset == video_map_[name].sz()) {
            running_tasks_.erase(it);
            return;
        }
        task_pool_->upload_one(name, offset, video_map_[name].piece[offset]);
    }

    // switch to work_thread
    void PushData(const std::string& name, const VideoInfo& info) {
        base::AutoLock auto_lock(lock_);
        video_map_[name] = info;
    }

signals:
    void update_progress(const std::string& name, int pos, int64 speed);

private:
    void InitTaskPool() {
        task_pool_ = new Foo(MAX_UPLOADING_COUNT, this);
    }

    void ScheduleTask(const std::string& name) {
        base::AutoLock auto_lock(lock_);
        if (!video_map_.count(name)) return;

        if (running_tasks_.size() < MAX_UPLOADING_COUNT) {
            running_tasks_.insert(name);
            int offset = video_map_[name].offset;
            if (offset < video_map_[name].sz()) {
                task_pool_->upload_one(name, offset, video_map_[name].piece[offset]);
            } else {
                running_tasks_.erase(name);
            }
        }
        else {
            waiting_tasks_.push(name);
        }
    }

    void PauseOne(const std::string& name) {
        base::AutoLock auto_lock(lock_);
        safety_erase(running_tasks_, running_tasks_.find(name));
    }

    void DeleteOne(const std::string& name) {
        base::AutoLock auto_lock(lock_);
        safety_erase(video_map_, video_map_.find(name));
    }

    void AutoRun() {
        while (true) {
            if (is_stop_) break;

            base::AutoLock auto_lock(lock_);
            if (!waiting_tasks_.empty() && running_tasks_.size() < MAX_UPLOADING_COUNT) {
                std::string name = waiting_tasks_.front();
                running_tasks_.insert(name);
                int offset = video_map_[name].offset;
                if (offset < video_map_[name].sz()) {
                    work_thread_->message_loop()->PostTask(FROM_HERE, 
                        base::Bind(&Foo::upload_one, task_pool_, name, offset, video_map_[name].piece[offset]));
                    waiting_tasks_.pop();
                }
            }
        }
    }

private:
    scoped_refptr<Foo> task_pool_;

    base::Thread* work_thread_;

    base::Thread* running_thread_;

    mutable base::Lock lock_;

    bool is_stop_;

    std::map<std::string, VideoInfo> video_map_;

    std::queue<std::string> waiting_tasks_;

    std::set<std::string> running_tasks_;

    DISALLOW_COPY_AND_ASSIGN(WorkLoop);
};

#endif // !WORK_LOOP_