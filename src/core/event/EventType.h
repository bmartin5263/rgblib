//
// Created by Brandon on 10/22/25.
//

#ifndef RGBLIB_EVENTTYPE_H
#define RGBLIB_EVENTTYPE_H

#include <cstddef>
#include <variant>
#include <optional>
#include "Types.h"
#include "SystemEvents.h"

namespace rgb {

template<typename Variant, typename ... Extra>
struct extend_variant;

template<typename ... Ts, typename ... Extra>
struct extend_variant<std::variant<Ts...>, Extra...> {
  using type = std::variant<Ts..., Extra...>; // Used by extend_variant_t
};

template<typename Variant, typename... Extra>
using extend_variant_t = typename extend_variant<Variant, Extra...>::type;

// Enforces 'EventConcept' constraints when creating the variant
template<typename... Events>
using EventVariant = std::variant<Events...>;

template<typename T, typename Variant>
struct EventIndex;

template<typename T, typename... Ts>
struct EventIndex<T, std::variant<Ts...>> {
  static constexpr size_t value = []() {
    size_t i = 0;
    (void)((!std::is_same_v<T, Ts> && (++i, true)) && ...);
    return i;
  }();
};

template<typename T, typename Variant>
constexpr size_t EventIndex_v = EventIndex<T, Variant>::value;

template<typename Target, typename Source>
constexpr auto narrow_variant(const Source& source) -> std::optional<Target> {
  return std::visit([](const auto& value) -> std::optional<Target> {
    using T = std::decay_t<decltype(value)>;
    if constexpr (std::is_constructible_v<Target, T>) {
      return value;
    } else {
      return std::nullopt;
    }
  }, source);
}


using SystemEvent = EventVariant<
  NullEvent,
  WakeEvent,
  SleepEvent,
  OBDIIConnected,
  OBDIIDisconnected,
  CarEngineStarted,
  CarEngineStopped,
  IRButtonPressed
>;

template<typename ...UserEvents>
using Event = extend_variant_t<SystemEvent, UserEvents...>;

}
#endif //RGBLIB_EVENTTYPE_H
