//
// Created by Brandon on 1/8/25.
//

#ifndef RGBLIB_FILLEFFECT_H
#define RGBLIB_FILLEFFECT_H

class LEDChain;
class ColorGenerator;
class FillEffect {
public:
  auto draw(LEDChain& chain, ColorGenerator& colorGenerator) -> void;

private:


};


#endif //RGBLIB_FILLEFFECT_H
