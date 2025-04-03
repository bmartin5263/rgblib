//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_WIRELESS_H
#define RGBLIB_WIRELESS_H


#include <esp_wifi_types.h>

namespace rgb {

class Wifi {
public:
  static auto SetMode(wifi_mode_t mode) -> void;
  static auto Start() -> bool;
  static auto Update() -> void;

private:
  bool started{false};

  static auto Instance() -> Wifi&;
  auto start() -> bool;
  auto update() -> void;

  static const char* NAME;
  static const char* PASSWORD;
};

}


#endif //RGBLIB_WIRELESS_H
