// Copyright 2022 Google LLC
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

#ifndef THIRD_PARTY_NEARBY_FASTPAIR_INTERNAL_API_FAST_PAIR_PLATFORM_H_
#define THIRD_PARTY_NEARBY_FASTPAIR_INTERNAL_API_FAST_PAIR_PLATFORM_H_

#include <functional>
#include <memory>
#include <string>

#include "absl/strings/string_view.h"
#include "fastpair/internal/api/device_info.h"
#include "fastpair/internal/api/timer.h"

namespace location {
namespace nearby {
namespace api {

class ImplementationFastPairPlatform {
 public:
  static std::unique_ptr<DeviceInfo> CreateDeviceInfo();

  // Timer API
  static std::unique_ptr<Timer> CreateTimer();
};

}  // namespace api
}  // namespace nearby
}  // namespace location

#endif  // THIRD_PARTY_NEARBY_FASTPAIR_INTERNAL_API_FAST_PAIR_PLATFORM_H_
