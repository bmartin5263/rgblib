//
// Created by Brandon on 5/6/26.
//

#ifndef RGBLIB_IICArduino_H
#define RGBLIB_IICArduino_H

#include <Arduino.h>
#include <Wire.h>
#include "Pin.h"
#include "IICBase.h"

#ifndef RGB_IIC_SDA
#define RGB_IIC_SDA SDA
#endif

#ifndef RGB_IIC_SCL
#define RGB_IIC_SCL SCL
#endif

namespace rgb::priv {

class IICArduino : public IICBase {
public:
  auto start() -> bool;
  auto stop() -> void;
  auto isStarted() const -> bool;

  static constexpr auto sdaPin() -> PinNumber { return PinNumber{RGB_IIC_SDA}; }
  static constexpr auto sclPin() -> PinNumber { return PinNumber{RGB_IIC_SCL}; }

private:
  bool mStarted{false};
};

}
#endif //RGBLIB_IICArduino_H
