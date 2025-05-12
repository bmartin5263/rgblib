//
// Created by Brandon on 2/16/25.
//

#ifndef RGBLIB_OTA_SUPPORT_H
#define RGBLIB_OTA_SUPPORT_H

#include <esp_wifi_types.h>
#include "Wireless.h"

namespace rgb {

class OTASupport {
public:
  static constexpr auto Enabled() -> bool {
    return Wifi::Enabled();
  }

  static auto Start() -> bool;
  static auto Update() -> void;

private:
  bool started{false};

  auto start() -> bool;
  auto update() -> void;

  static auto Instance() -> OTASupport&;
};


}

#endif //RGBLIB_OTA_SUPPORT_H
