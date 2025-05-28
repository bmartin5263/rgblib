//
// Created by Brandon on 5/27/25.
//

#ifndef RGBLIB_PICKLIST_H
#define RGBLIB_PICKLIST_H

#include <array>

template <typename T, size_t N>
class PickList {
public:
  PickList(std::array<T, N> arr): data{std::move(arr)} {}

  auto next() -> void {
    selection = (selection + 1) % N;
  }

  auto prev() -> void {
    selection = (selection - 1) % N;
  }

  auto getSelected() -> T& {
    return data[selection];
  }

private:
  std::array<T, N> data;
  int selection{0};
};

#endif //RGBLIB_PICKLIST_H
