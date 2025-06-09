//
// Created by Brandon on 6/8/25.
//

#ifndef RGBLIB_CIRCULARBUFFER_H
#define RGBLIB_CIRCULARBUFFER_H

#include <array>

template<typename T>
struct CircularBufferIterator {
  T* current;
  T* lastElement;
  T* listStart;
  T* listEnd;

  CircularBufferIterator(T* current, T* lastElement, T* listStart, T* listEnd)
    : current(current), lastElement(lastElement), listStart(listStart), listEnd(listEnd) {}

  CircularBufferIterator(T* current, T* listStart, T* listEnd)
    : current(current), lastElement(current), listStart(listStart), listEnd(listEnd) {}

  auto operator++() -> CircularBufferIterator<T>& {
    ++current;
    if (current == listEnd) {
      current = listStart;
    }
    if (current == lastElement) {
      current = listEnd;
    }
    return *this;
  }

  auto operator++(int) -> CircularBufferIterator {
    CircularBufferIterator tmp(*this);
    operator++();
    return tmp;
  }

  auto operator*() -> T& {
    return *current;
  }

  auto operator*() const -> const T& {
    return *current;
  }

  friend bool operator==(const CircularBufferIterator& lhs, const CircularBufferIterator& rhs) {
    auto result = lhs.current == rhs.current
                  && lhs.lastElement == rhs.lastElement
                  && lhs.listEnd == rhs.listEnd
                  && lhs.listStart == rhs.listStart;
    return result;
  }

  friend bool operator!=(const CircularBufferIterator& lhs, const CircularBufferIterator& rhs) {
    auto result = !(lhs == rhs);
    return result;
  }
};

template <typename T, size_t N>
struct CircularBuffer {

  constexpr auto push(T item) {
    data[next] = item;
    next = (next + 1) % this->size();
  }

  constexpr auto size() {
    return N;
  }

  constexpr auto operator[](size_t index) -> T& {
    return data[index];
  }

  constexpr auto operator[](size_t index) const -> const T& {
    return data[index];
  }

  constexpr auto begin() -> CircularBufferIterator<T> {
    return {&data[next], &data[next], std::begin(data), std::end(data)};
  }

  constexpr auto end() -> CircularBufferIterator<T> {
    return {std::end(data), &data[next], std::begin(data), std::end(data)};
  }

  std::array<T, N> data{};
  size_t next{};
};

#endif //RGBLIB_CIRCULARBUFFER_H
