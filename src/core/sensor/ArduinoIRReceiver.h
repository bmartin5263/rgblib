//
// Created by Brandon on 5/13/25.
//

#ifndef RGBLIB_ARDUINOIRRECEIVER_H
#define RGBLIB_ARDUINOIRRECEIVER_H

#include "Sensor.h"
#include "PushButton.h"
#include "IRButton.h"

namespace rgb {

class ArduinoIRReceiver : public Sensor {
public:
  explicit ArduinoIRReceiver(PinNumber pin);

  std::optional<IRButtonType> lastCommand;

protected:
  auto doStart() -> bool override;
  auto doRead() -> void override;

private:
  PinNumber pin;
};

}


#endif //RGBLIB_ARDUINOIRRECEIVER_H
