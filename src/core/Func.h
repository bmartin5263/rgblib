//
// Created by Brandon on 5/27/25.
//

#ifndef RGBLIB_FUNC_H
#define RGBLIB_FUNC_H

#define SG14_INPLACE_FUNCTION_THROW(x) std::abort()
#include "inplace_function.h"

template<typename Sig>
using Function = stdext::inplace_function<Sig, 32>;

using Runnable = Function<void()>;

template <typename T>
using Consumer = Function<void(T)>;

template <typename T>
using Supplier = Function<T()>;

using Predicate = Supplier<bool>;

static constexpr auto DoNothing() {};

#endif //RGBLIB_FUNC_H
