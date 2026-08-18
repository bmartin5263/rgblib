//
// Created by Brandon on 8/17/26.
//

#ifndef RGBLIB_LEDMATRIX_SELECTOR_H
#define RGBLIB_LEDMATRIX_SELECTOR_H

#include "Types.h"
#include "RgbwSupport.h"
#include "MatrixStrategy.h"

#define MATRIX_TEMPLATE_DECLARATION template <  \
  uint COLUMNS, uint ROWS, uint PIN,             \
  RgbwSupport RGBW_SUPPORT = RgbwSupport::DISABLE, \
  uint MULTI_MATRIX_ROWS = 1, uint MULTI_MATRIX_COLS = 1, \
  typename MULTI_MATRIX_STRATEGY = PixelRowMatrixColumn \
>

#if defined(RGB_ARDUINO_ESP32)
#include "FastLEDMatrix.h"
namespace rgb {
MATRIX_TEMPLATE_DECLARATION
using LEDMatrix = FastLEDMatrix<COLUMNS, ROWS, PIN, RGBW_SUPPORT, MULTI_MATRIX_ROWS, MULTI_MATRIX_COLS, MULTI_MATRIX_STRATEGY>;
}
#elif defined(RGB_NATIVE)
#include "NativeLEDMatrix.h"
namespace rgb {
MATRIX_TEMPLATE_DECLARATION
using LEDMatrix = NativeLEDMatrix<COLUMNS, ROWS>;
}
#else
#error Unknown platform for LEDMatrix
#endif


#endif //RGBLIB_LEDMATRIX_SELECTOR_H
