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
  auto operator=(Handle&& rhs) noexcept -> Handle& { opt = std::move(rhs.opt); }

  auto operator*() noexcept -> T& {
    return const_cast<T&>(static_cast<const Handle<T, D>*>(this)->operator*());
  }

  auto operator*() const noexcept -> const T& {
    return opt.value();
  }

  auto get() noexcept -> T& {
    return opt.value();
  }

  auto isSet() -> bool {
    return opt.has_value();
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

  Handle(const Handle& rhs) = delete;
  auto operator=(const Handle& rhs) -> Handle& = delete;

  ~Handle() {
    Log.info("~Handle();");
    if (opt) {
      D()(*opt);
    }
  }
};

}


#endif //RGBLIB_HANDLE_H
