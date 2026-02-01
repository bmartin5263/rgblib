//
// Created by Brandon on 10/25/25.
//

#ifndef RGBLIB_SENSOR_H
#define RGBLIB_SENSOR_H


namespace rgb {

class Sensor {
public:
  Sensor() = default;
  virtual ~Sensor() = default;
  Sensor(const Sensor& rhs) = default;
  Sensor(Sensor&& rhs) noexcept = default;
  Sensor& operator=(const Sensor& rhs) = default;
  Sensor& operator=(Sensor&& rhs) noexcept = default;

  auto start() -> bool;
  auto read() -> void;
protected:
  virtual auto doStart() -> bool = 0;
  virtual auto doRead() -> void = 0;

private:

};

}


#endif //RGBLIB_SENSOR_H
