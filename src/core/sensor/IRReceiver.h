//
// Created by Brandon on 5/13/25.
//

#ifndef RGBLIB_IRREMOTE_H
#define RGBLIB_IRREMOTE_H

#include <functional>
#include "Sensor.h"
#include "PushButton.h"
#include "IRButton.h"

namespace rgb {

class IRReceiver : public Sensor {
public:
  explicit IRReceiver(PinNumber pin);

  std::optional<IRButtonType> lastCommand;

protected:
  auto doStart() -> bool override;
  auto doRead() -> void override;

private:
  PinNumber pin;
};

}


#endif //RGBLIB_IRREMOTE_H
