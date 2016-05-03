// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/memory/scoped_ptr.h"
#include "base/threading/sequenced_worker_pool.h"


int main(int argc, char* argv[]) {
  scoped_ptr<base::SequencedWorkerPool> my_pool(new base::SequencedWorkerPool(5, "fangr_"));



  return 0;
}
