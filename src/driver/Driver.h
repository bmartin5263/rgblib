//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_DRIVER_H
#define RGBLIB_DRIVER_H

class LEDChain;
class Driver {
public:
  virtual auto draw(LEDChain& chain) -> void = 0;

private:

};


#endif //RGBLIB_DRIVER_H
