//
// Created by Brandon on 2/19/25.
//

#ifndef RGBLIB_HANDLE_H
#define RGBLIB_HANDLE_H

#include <optional>
#include "Log.h"

namespace rgb {

template<typename T, typename D>
struct Handle {
  std::optional<T> opt;

  Handle() noexcept : opt() {}
  explicit Handle(T value) noexcept : opt(value) {}
  Handle(Handle&& rhs) noexcept { opt = std::move(rhs.opt); }
  Handle(const Handle& rhs) = delete;
  auto operator=(const Handle& rhs) -> Handle& = delete;

  auto operator=(Handle&& rhs) noexcept -> Handle&  {
    opt = std::move(rhs.opt);
    return *this;
  }

  auto operator*() noexcept -> T& { return opt.value(); }
  auto get() noexcept -> T& { return opt.value(); }
  auto isSet() -> bool { return opt.has_value(); }

  auto operator->() noexcept -> T* {
    if (opt) {
      return &opt.value();
    }
    return nullptr;
  }

  auto destroy() noexcept -> void {
    if (opt) {
      D()(*opt);
    }
    opt.reset();
  }

  auto reset(T newValue) noexcept -> void {
    destroy();
    opt = newValue;
  }

  ~Handle() {
    TRACE("~Handle();");
    if (opt) {
      D()(*opt);
    }
  }
};

}


#endif //RGBLIB_HANDLE_H
