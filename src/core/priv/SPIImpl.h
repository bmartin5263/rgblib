//
// Created by Brandon on 5/6/26.
//

#ifndef RGBLIB_SPIIMPLEMENTATION_H
#define RGBLIB_SPIIMPLEMENTATION_H

#if defined(RGB_ARDUINO)
#include "SPIArduino.h"
namespace rgb::priv { class SPIImpl : public SPIArduino {}; };
#else
#error SPI Not Available
#endif

#endif //RGBLIB_SPIIMPLEMENTATION_H
