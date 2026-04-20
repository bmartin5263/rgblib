//
// Created by Brandon on 4/19/26.
//

#ifndef RGBLIB_PIXELROWMATRIXCOLUMN_H
#define RGBLIB_PIXELROWMATRIXCOLUMN_H

#include "Types.h"
#include "Log.h"

namespace rgb {

/**
 * Flattens an effective 2D coordinate into a linear pixel index for a
 * multi-matrix arrangement where each individual matrix is filled row-by-row
 * left-to-right, and matrices are chained by advancing down a column before
 * moving to the next column of matrices.
 */
struct PixelRowMatrixColumn {
  static auto indexOf(
    uint column,
    uint row,
    uint columns, // per-matrix
    uint rows,    // per-matrix
    uint matrixColumns,
    uint matrixRows
  ) -> uint {
    const auto matrixColumn = column / columns;
    const auto matrixRow = row / rows;
    const auto localColumn = column % columns;
    const auto localRow = row % rows;
    const auto matrixIndex = matrixColumn * matrixRows + matrixRow;
    auto result = matrixIndex * rows * columns + localRow * columns + localColumn;
    INFO("(%i, %i) -> %i", column, row, result);
    return result;
  }
};

}

#endif //RGBLIB_PIXELROWMATRIXCOLUMN_H
