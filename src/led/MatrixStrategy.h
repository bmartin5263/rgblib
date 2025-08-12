//
// Created by Brandon on 8/10/25.
//

#ifndef RGBLIB_MATRIXSTRATEGY_H
#define RGBLIB_MATRIXSTRATEGY_H

#include "Types.h"

namespace rgb {

struct MatrixContext {
  u16 ledCols;
  u16 ledRows;
  u16 ledsPerMatrix;
  u16 matrixCols;
  u16 matrixRows;
//  u16 shiftVertical;
//  u16 shiftHorizontal;
  u16 pixelNum;
  u16 pixelCol;
  u16 pixelRow;
//  bool flipVertical;
//  bool flipHorizontal;
};

using MatrixStrategy = u16(*)(const MatrixContext&);

/*
 * Pixel Addressing Order (3x3):
 *   0 1 2
 *   3 4 5
 *   6 7 8
 *
 *
 * Multi Matrix Addressing Order (abstract):
 *            0 1 2              3 4 5
 *            6 7 8              9 10 11
 *
 *            12 13 14              14 15
 *            16 17              14 15
 *
 *            16 17              18 19
 *            20 21              22 23
 *
 * Multi Matrix Addressing Order:
 * [0]  0 1     [3]  12 13
 *            2 3                14 15
 *
 * [1]  4 5     [4]  16 17
 *            6 7                18 19
 *
 * [2]  8 9     [5]  20 21
 *            10 11              22 23
 */
struct PixelRowMatrixColumn {
  auto mapPixelNumberToLedNumber(const MatrixContext& context) -> u16 {
    // Config
    const auto matrixColsPerCircuit = context.matrixCols; // 2
    const auto matrixRowsPerCircuit = context.matrixRows; // 3
    const auto ledColsPerMatrix = context.ledCols;       // 3
    const auto ledRowsPerMatrix = context.ledRows;       // 2

    // auto pixelNum = 24;
    auto col = context.pixelCol; // 0
    auto row = context.pixelRow; // 4 (ledNum=12, matrixNum=2, matrixRow=2, matrixCol=0)

    auto matrixRow = matrixColsPerCircuit * ledColsPerMatrix;
    auto matrixCol = 0;

    auto matrixNum = (matrixColsPerCircuit * matrixCol) + matrixRow;

    return 0;
  }
};

/*
 * Pixel Addressing Arrangement:
 *   0 1 2
 *   3 4 5
 *   6 7 8
 *
 *
 * Matrix Wiring Order:
 *   0 1   4 5
 *   2 3   6 7
 *
 *   8  9   12 13
 *   10 11  14 15
 */
struct PixelRowMatrixRow {
  auto mapPixelNumberToLedNumber(const MatrixContext& context) -> u16 {
    auto matrixNum = context.pixelNum / context.ledsPerMatrix;
    auto subpixelNum = context.pixelNum % context.ledsPerMatrix;
    return (context.ledsPerMatrix * matrixNum) + subpixelNum;
  }
};


/*
 * Pixel Addressing Arrangement:
 *   0 1 2
 *   5 4 3
 *   6 7 8
 *
 *
 * Matrix Wiring Order:
 *   0 1   8 9
 *   3 2   11 10
 *
 *   4 5   12 13
 *   7 6   15 14
 */
struct PixelZigRowMatrixColumn {
  auto mapPixelNumberToLedNumber(const MatrixContext& context) -> u16 {

  }
};

/*
 * Pixel Addressing Arrangement:
 *   0 5 6
 *   1 4 7
 *   2 3 8
 *
 * Matrix Wiring Order:
 *   0 3   4 7
 *   1 2   5 6
 *
 *   8 11   12 15
 *   9 10   13 14
 */
struct PixelZigColumnMatrixRow {
  auto mapPixelNumberToLedNumber(const MatrixContext& context) -> u16 {

  }
};

}

#endif //RGBLIB_MATRIXSTRATEGY_H
