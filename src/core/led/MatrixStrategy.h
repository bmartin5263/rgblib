//
// Created by Brandon on 4/19/26.
//

#ifndef RGBLIB_MATRIXSTRATEGY_H
#define RGBLIB_MATRIXSTRATEGY_H

#include "Types.h"

namespace rgb {

/**
 * CRTP base for multi-matrix mapping strategies.
 *
 * A strategy translates an effective 2D coordinate on the combined
 * multi-matrix grid into the linear LED wire position for the physical
 * LED chain. Derived strategies must provide:
 *
 *   static auto compute(
 *     uint column, uint row,
 *     uint columns, uint rows,
 *     uint matrixColumns, uint matrixRows
 *   ) -> uint;
 *
 * Parameter meaning:
 *   - column, row        : effective coordinate on the multi-matrix grid
 *   - columns, rows      : dimensions of a single matrix
 *   - matrixColumns      : number of matrices arranged along the column axis
 *   - matrixRows         : number of matrices arranged along the row axis
 */
template <typename Derived>
struct MatrixStrategy {
  static auto indexOf(
    uint column,
    uint row,
    uint columns,
    uint rows,
    uint matrixColumns,
    uint matrixRows
  ) -> uint {
    return Derived::compute(column, row, columns, rows, matrixColumns, matrixRows);
  }
};

/**
 * Flattens an effective 2D coordinate into a linear pixel index for a
 * multi-matrix arrangement where each individual matrix is filled row-by-row
 * left-to-right, and matrices are chained by advancing down a column before
 * moving to the next column of matrices.
 */
struct PixelRowMatrixColumn : MatrixStrategy<PixelRowMatrixColumn> {
  static auto compute(
    uint column,
    uint row,
    uint columns,
    uint rows,
    [[maybe_unused]] uint matrixColumns,
    uint matrixRows
  ) -> uint {
    auto matrixColumn = column / columns;
    auto matrixRow = row / rows;
    auto localColumn = column % columns;
    auto localRow = row % rows;
    auto matrixIndex = matrixColumn * matrixRows + matrixRow;
    auto result = matrixIndex * rows * columns + localRow * columns + localColumn;
    return result;
  }
};

}

#endif //RGBLIB_MATRIXSTRATEGY_H
