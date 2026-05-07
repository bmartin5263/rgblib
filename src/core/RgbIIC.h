//
// Created by Brandon on 5/6/26.
//

#ifndef RGBLIB_IIC_H
#define RGBLIB_IIC_H

#include "IICImpl.h"

namespace rgb {

class IIC {
public:
  static auto Start() -> bool;
  static auto Stop() -> void;
  static auto IsStarted() -> bool;

  static constexpr auto SDAPin() -> PinNumber { return priv::IICImpl::sdaPin(); }
  static constexpr auto SCLPin() -> PinNumber { return priv::IICImpl::sclPin(); }

private:
  static auto Implementation() -> priv::IICImpl&;
  priv::IICImpl impl;
};

auto IIC::Implementation() -> priv::IICImpl& {
  static IIC instance;
  return instance.impl;
}

auto IIC::Start() -> bool {
  return Implementation().start();
}

auto IIC::Stop() -> void {
  Implementation().stop();
}

auto IIC::IsStarted() -> bool {
  return Implementation().isStarted();
}

}

#endif //RGBLIB_IIC_H
