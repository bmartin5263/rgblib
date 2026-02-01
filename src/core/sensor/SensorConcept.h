//
// Created by Brandon on 10/25/25.
//

#ifndef RGBLIB_SENSORCONCEPT_H
#define RGBLIB_SENSORCONCEPT_H

#include <concepts>

template<typename T>
concept SensorConcept = requires(T sensor) {
  { sensor.read() } -> std::same_as<int>;
  { sensor.start() } -> std::same_as<void>;
};

#endif //RGBLIB_SENSORCONCEPT_H
