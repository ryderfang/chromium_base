// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/bind.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/sequenced_worker_pool.h"
#include "base/threading/thread.h"
#include <iostream>
using namespace std;

class Foo 
    : public base::RefCountedThreadSafe<Foo> {
public:
    Foo(int t) 
      : a_(t),
        worker_pool_(new base::SequencedWorkerPool(3, "fangr_")) { 
    }

    ~Foo() {
        worker_pool_->Shutdown();
    }

    void work() {
        worker_pool_->PostWorkerTask(FROM_HERE, base::Bind(&Foo::DoWork, this));
    }

    void ordered_tasks() {
        base::SequencedWorkerPool::SequenceToken token = worker_pool_->GetSequenceToken();

        worker_pool_->PostSequencedWorkerTask(token, FROM_HERE, base::Bind(&Foo::DoTask1, this));

        worker_pool_->PostSequencedWorkerTask(token, FROM_HERE, base::Bind(&Foo::DoTask2, this));
    }

private:
    void DoWork() {  
        for (int i = -10; i < a_; ++i) {
            cout << i << ",\t";
        }
    }

    void DoTask1() {
        for (int i = 0; i < 10; ++i) {
            cout << 'a' + i << "|\t";
        }
    }

    void DoTask2() {
        for (int i = 1; i < 10; ++i) {
            cout << "foo" << "$\t";
        }
    }

private:
    scoped_refptr<base::SequencedWorkerPool> worker_pool_;

    int a_;
};

scoped_refptr<Foo> test;

int main(int argc, char* argv[]) {
    cout << "test!!!" << endl; 

    test = new Foo(10);
    while (true) {
        test->work();
        test->ordered_tasks();
    }

    return 0;
}
