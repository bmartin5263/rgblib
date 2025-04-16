//
// Created by Brandon on 4/14/25.
//
// https://www.reedbeta.com/blog/python-like-enumerate-in-cpp17/

#ifndef RGBLIB_ENUMERATE_H
#define RGBLIB_ENUMERATE_H

#include <tuple>

namespace rgb {

template <typename T,
  typename TIter = decltype(std::begin(std::declval<T>())),
  typename = decltype(std::end(std::declval<T>()))>
constexpr auto enumerate(T && iterable)
{
  struct iterator
  {
    size_t i;
    TIter iter;
    bool operator != (const iterator & other) const { return iter != other.iter; }
    void operator ++ () { ++i; ++iter; }
    auto operator * () const { return std::tie(i, *iter); }
  };
  struct iterable_wrapper
  {
    T iterable;
    auto begin() { return iterator{ 0, std::begin(iterable) }; }
    auto end() { return iterator{ 0, std::end(iterable) }; }
  };
  return iterable_wrapper{ std::forward<T>(iterable) };
}

}

#endif //RGBLIB_ENUMERATE_H
