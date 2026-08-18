//
// Created by Brandon on 8/17/26.
//

#ifndef RGBLIB_NATIVEIRRECEIVER_H
#define RGBLIB_NATIVEIRRECEIVER_H

#include <functional>
#include "Sensor.h"
#include "PushButton.h"
#include "IRButton.h"

namespace rgb {

class NativeIRReceiver : public Sensor {
public:
  explicit NativeIRReceiver(PinNumber pin);

protected:
  auto doStart() -> bool override;
  auto doRead() -> void override;
};

}


#endif //RGBLIB_NATIVEIRRECEIVER_H
