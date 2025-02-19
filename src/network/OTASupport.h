//
// Created by Brandon on 2/16/25.
//

#ifndef RGBLIB_WIFI_H
#define RGBLIB_WIFI_H


namespace rgb {

class OTASupport {
public:
  static auto Start() -> bool;
  static auto Update() -> void;

private:
  bool started{false};

  auto start() -> bool;
  auto update() -> void;

  static auto Instance() -> OTASupport&;
};


}

#endif //RGBLIB_WIFI_H
