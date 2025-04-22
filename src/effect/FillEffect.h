//
// Created by Brandon on 4/14/25.
//

#ifndef RGBLIB_FILLEFFECT_H
#define RGBLIB_FILLEFFECT_H

#include "Color.h"

namespace rgb {

struct FillEffectShaderParameters {
  Timestamp now;
  u16 length;
  u16 position;

  normal relativePosition() const {
    return position / static_cast<float>(length);
  }
};

using FillEffectShader = std::function<void(Color&, const FillEffectShaderParameters&)>;

constexpr auto defaultShader(Color& pixel, const FillEffectShaderParameters&) -> void {
  pixel = Color::CYAN(.01);
}

class LEDChain;
class FillEffect {
public:
  auto draw(LEDChain& chain) -> void;

  FillEffectShader shader{defaultShader};
private:

};

}


#endif //RGBLIB_FILLEFFECT_H
