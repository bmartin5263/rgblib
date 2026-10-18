//
// Created by Brandon on 5/27/25.
//

#ifndef RGBLIB_FUNC_H
#define RGBLIB_FUNC_H

#if RGB_INPLACE_FUNCTION
#define SG14_INPLACE_FUNCTION_THROW(x) std::abort()
#include "inplace_function.h"
#else
#include <functional>
#endif

#ifndef RGB_FUNCTION_SIZE
#define RGB_FUNCTION_SIZE 32
#endif

namespace rgb {

#if RGB_INPLACE_FUNCTION
template<typename Sig>
using Function = stdext::inplace_function<Sig, RGB_FUNCTION_SIZE>;
#else
template<typename Sig>
using Function = std::function<Sig>;
#endif

using Runnable = Function<void()>;

template <typename T>
using Consumer = Function<void(T)>;

template <typename T>
using Supplier = Function<T()>;

using Predicate = Supplier<bool>;

static constexpr auto DoNothing() {};

}

#endif //RGBLIB_FUNC_H
