//
// Created by Brandon on 8/17/26.
//

#include "NativeIRReceiver.h"

#if defined(RGB_NATIVE)

#include "NativeDisplay.h"

namespace rgb {

NativeIRReceiver::NativeIRReceiver(PinNumber pin) {
  (void)pin;
}

auto NativeIRReceiver::doStart() -> bool {
  NativeDisplay::EnableKeyEvents();
  return true;
}

auto NativeIRReceiver::doRead() -> void {
}

}

#endif //defined(RGB_NATIVE)
