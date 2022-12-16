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

#include "fastpair/internal/impl/windows/device_info.h"

#include <functional>
#include <string>

#include "gtest/gtest.h"
#include "absl/synchronization/notification.h"
#include "fastpair/internal/api/device_info.h"

namespace location {
namespace nearby {
namespace windows {
namespace {

TEST(DeviceInfo, DISABLED_GetOsType) {
  EXPECT_EQ(DeviceInfo().GetOsType(), api::DeviceInfo::OsType::kWindows);
}

TEST(DeviceInfo, DISABLED_IsScreenLocked) {
  EXPECT_TRUE(DeviceInfo().IsScreenLocked());
}

TEST(DeviceInfo, DISABLED_RegisterScreenLockedListener) {
  std::function<void(api::DeviceInfo::ScreenStatus)> listener_1 =
      [](api::DeviceInfo::ScreenStatus) {};
  std::function<void(api::DeviceInfo::ScreenStatus)> listener_2 =
      [](api::DeviceInfo::ScreenStatus) {};

  DeviceInfo device_info;
  EXPECT_EQ(device_info.screen_locked_listeners_.size(), 0);

  device_info.RegisterScreenLockedListener("listener_1", listener_1);
  EXPECT_EQ(device_info.screen_locked_listeners_.size(), 1);

  device_info.RegisterScreenLockedListener("listener_2", listener_2);
  EXPECT_EQ(device_info.screen_locked_listeners_.size(), 2);
}

TEST(DeviceInfo, DISABLED_UnregisterScreenLockedListener) {
  std::function<void(api::DeviceInfo::ScreenStatus)> listener_1 =
      [](api::DeviceInfo::ScreenStatus) {};
  std::function<void(api::DeviceInfo::ScreenStatus)> listener_2 =
      [](api::DeviceInfo::ScreenStatus) {};

  DeviceInfo device_info;
  EXPECT_EQ(device_info.screen_locked_listeners_.size(), 0);

  device_info.RegisterScreenLockedListener("listener_1", listener_1);
  device_info.RegisterScreenLockedListener("listener_2", listener_2);
  EXPECT_EQ(device_info.screen_locked_listeners_.size(), 2);

  device_info.UnregisterScreenLockedListener("listener_1");
  EXPECT_EQ(device_info.screen_locked_listeners_.size(), 1);

  device_info.UnregisterScreenLockedListener("listener_2");
  EXPECT_EQ(device_info.screen_locked_listeners_.size(), 0);
}

TEST(DeviceInfo, DISABLED_UpdateScreenLockedListener) {
  absl::Notification notification;

  api::DeviceInfo::ScreenStatus screen_locked_tracker =
      api::DeviceInfo::ScreenStatus::kUndetermined;

  std::function<void(api::DeviceInfo::ScreenStatus)> listener =
      [&screen_locked_tracker,
       &notification](api::DeviceInfo::ScreenStatus status) {
        screen_locked_tracker = api::DeviceInfo::ScreenStatus::kLocked;
        notification.Notify();
      };

  DeviceInfo device_info;
  device_info.RegisterScreenLockedListener("listener", listener);
  EXPECT_TRUE(notification.WaitForNotificationWithTimeout(absl::Seconds(5)));
  EXPECT_EQ(screen_locked_tracker, api::DeviceInfo::ScreenStatus::kLocked);
}

}  // namespace
}  // namespace windows
}  // namespace nearby
}  // namespace location
