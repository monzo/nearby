// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#import "platform/impl/ios/Source/Platform/multi_thread_executor.h"

#include "platform/base/runnable.h"
#import "platform/impl/ios/Source/Platform/scheduled_executor.h"

namespace location {
namespace nearby {
namespace ios {

MultiThreadExecutor::MultiThreadExecutor(int max_concurrency) {
  scheduled_executor_ = std::make_unique<ScheduledExecutor>(max_concurrency);
}

void MultiThreadExecutor::Shutdown() { scheduled_executor_->Shutdown(); }

void MultiThreadExecutor::Execute(Runnable&& runnable) {
  scheduled_executor_->Execute(std::move(runnable));
}

bool MultiThreadExecutor::DoSubmit(Runnable&& runnable) {
  return scheduled_executor_->DoSubmit(std::move(runnable));
}

}  // namespace ios
}  // namespace nearby
}  // namespace location
