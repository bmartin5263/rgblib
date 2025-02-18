//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_WIRELESS_H
#define RGBLIB_WIRELESS_H


namespace rgb {

class Wifi {
public:
  static auto Start() -> void;

private:
  bool started{false};

  static auto Instance() -> Wifi&;
  auto start() -> void;

  static const char* NAME;
  static const char* PASSWORD;
};

}


#endif //RGBLIB_WIRELESS_H
