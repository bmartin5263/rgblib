//
// Created by Brandon on 5/27/25.
//

#ifndef RGBLIB_FUNC_H
#define RGBLIB_FUNC_H

#include <functional>

using Runnable = std::function<void()>;

template <typename T>
using Consumer = std::function<void(T)>;

template <typename T>
using Supplier = std::function<T(void)>;

using Predicate = Supplier<bool>;

#endif //RGBLIB_FUNC_H
