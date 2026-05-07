//
// Created by Brandon on 5/6/26.
//

#ifndef RGBLIB_IICIMPLEMENTATION_H
#define RGBLIB_IICIMPLEMENTATION_H

#if defined(RGB_ARDUINO)
#include "IICArduino.h"
namespace rgb::priv { class IICImpl : public IICArduino {}; };
#else
#error IIC Not Available
#endif

#endif //RGBLIB_IICIMPLEMENTATION_H
