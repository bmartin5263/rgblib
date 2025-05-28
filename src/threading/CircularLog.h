#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

namespace rgb {

template<typename T>
struct CircularLogIterator {
  T* current;
  T* lastElement;
  T* listStart;
  T* listEnd;

  CircularLogIterator(T* current, T* lastElement, T* listStart, T* listEnd)
    : current(current), lastElement(lastElement), listStart(listStart), listEnd(listEnd) {}

  CircularLogIterator(T* current, T* listStart, T* listEnd)
    : current(current), lastElement(current), listStart(listStart), listEnd(listEnd) {}

  auto operator++() -> CircularLogIterator<T>& {
    ++current;
    if (current == listEnd) {
      current = listStart;
    }
    if (current == lastElement) {
      current = listEnd;
    }
    return *this;
  }

  auto operator++(int) -> CircularLogIterator {
    CircularLogIterator tmp(*this);
    operator++();
    return tmp;
  }

  auto operator*() -> T& {
    return *current;
  }

  auto operator*() const -> const T& {
    return *current;
  }

  friend bool operator==(const CircularLogIterator& lhs, const CircularLogIterator& rhs) {
    auto result = lhs.current == rhs.current
                  && lhs.lastElement == rhs.lastElement
                  && lhs.listEnd == rhs.listEnd
                  && lhs.listStart == rhs.listStart;
    return result;
  }

  friend bool operator!=(const CircularLogIterator& lhs, const CircularLogIterator& rhs) {
    auto result = !(lhs == rhs);
    return result;
  }
};

template<typename Iter, typename T = typename Iter::value_type>
class CircularLog {
public:

  constexpr auto push(T item) {
    data[next] = item;
    next = (next + 1) % this->size();
  }

  constexpr auto operator[](size_t index) -> T& {
    return data[index];
  }

  constexpr auto operator[](size_t index) const -> const T& {
    return data[index];
  }

  constexpr auto begin() -> CircularLogIterator<T> {
    return {&data[next], &data[next], std::begin(data), std::end(data)};
  }

  constexpr auto end() -> CircularLogIterator<T> {
    return {std::end(data), &data[next], std::begin(data), std::end(data)};
  }

//  constexpr auto begin() -> T* {
//    return std::begin(data);
//  }
//
//  constexpr auto end() -> T* {
//    return std::end(data);
//  }

  [[nodiscard]] constexpr auto size() const -> size_t {
    return std::size(data);
  }

private:
  Iter data{};
  size_t next{0};

};

}

#endif

