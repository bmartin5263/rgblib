# RGBLib
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/bdon/library/rgblib.svg)](https://registry.platformio.org/libraries/bdon/rgblib)

C++ framework for complex LED-based Applications running on Arduino Nano ESP32

Features:
- Allocation-free after initialization, memory pools used for entities that are created/destroyed repeatedly during runtime
- Strongly-typed extensible event system
- Built-in effects with extensibility through shader functions
- Over-the-Air update support enabled with `RGB_OTA` flag
- Printf-style logging using enabled with `RGB_DEBUG` flag

## Example

```cpp
#include "UserApplication.h"
#include "FastLEDStrip.h"

class BlueFillApplication : public rgb::UserApplication<> {
  rgb::FastLEDStrip<40, D5, rgb::RgbwSupport::ENABLE> ledStrip{};
protected:
  auto configure(Configurer& app) -> void override { app.addLEDs(ledStrip); }
  auto draw() -> void override { ledStrip.fill(rgb::Color::BLUE()); }
};
```

## Basics

### UserApplication

To create an application, define a subclass of `UserApplication` and implement the pure virtual method `auto configure(Configurer& app) -> void`.
This method is used to register various LEDs, sensors, event handlers, and other application properties before runtime begins.

In addition, the following methods may optionally be overridden:

| Method Name                 | Purpose                                                                                              |
|-----------------------------|------------------------------------------------------------------------------------------------------|
| `auto initialize() -> void` | For starting effects/timers/animations. Runs right before main loop starts                           |
| `auto update() -> void`     | Called once per-frame before drawing any pixels, used for updating the state of the application      |
| `auto draw() -> void`       | Called once per-frame **before** Effects/Animations run, used for manually drawing individual pixels |
| `auto postDraw() -> void`   | Called once per-frame **after** Effects/Animations run, used for manually drawing individual pixels  |


### Pixels & LEDs

The framework distinguishes between **Pixels**, which are just color data, from `LEDs`, which are the physical components that light up.
Pixel-related classes, like `PixelList` and `PixelGrid`, deal with reading/writing raw color data.
LED-related classes, like `FastLEDStrip` and `FastLEDGrid`, deal with interfacing with the actual hardware.

The rendering system doesn't care about hardware so it uses the pixel-related classes.
`UserApplication::addLEDs()` needs the actual LED-related class.

### Configuration

| Macro                | Usage                                                                     | Default                          |
|----------------------|---------------------------------------------------------------------------|----------------------------------|
| `RGB_ARDUINO`        | Uses Arduino implementation of hardware abstractions                      | `0` (disabled)                   |
| `RGB_ARDUINO_NANO`   | Uses Arduino ESP32 implementation of hardware abstractions                | `0` (disabled)                   |
| `RGB_DEBUG`          | Enables debugging features like printf-style logging and monitoring       | `0` (disabled)                   |
| `RGB_LOG_LEVEL`      | Log verbosity: `0`=none, `1`=Error, `2`=Info, `3`=Trace                   | `2` if `RGB_DEBUG` set, else `0` |
| `RGB_OTA`            | Enables Over-the-Air firmware updates and WiFi connectivity               | `0` (disabled)                   |
| `RGB_WIFI_SSID`      | WiFi network SSID used for OTA connectivity                               | `""` (empty)                     |
| `RGB_WIFI_PASSWORD`  | WiFi network password used for OTA connectivity                           | `""` (empty)                     |
| `RGB_MAX_ANIMATIONS` | Maximum number of concurrently active animations in the `Animations` pool | `5`                              |
| `RGB_MAX_EFFECTS`    | Maximum number of concurrently active effects in the `Effects` pool       | `5`                              |
| `RGB_MAX_TIMERS`     | Maximum number of concurrently active timers in the `Timer` pool          | `5`                              |
| `RGB_IIC_SDA`        | GPIO pin used for the I2C SDA line                                        | `SDA`                            |
| `RGB_IIC_SCL`        | GPIO pin used for the I2C SCL line                                        | `SCL`                            |
| `RGB_SPI_CS`         | GPIO pin used for the SPI chip-select line                                | `A0`                             |
| `RGB_SPI_MOSI`       | GPIO pin used for the SPI MOSI line                                       | `A1`                             |
| `RGB_SPI_SCK`        | GPIO pin used for the SPI clock line                                      | `A2`                             |
| `RGB_SPI_MISO`       | GPIO pin used for the SPI MISO line                                       | `A3`                             |

## Features

### Animations

Animations let you define a sequence of steps to run where each step is composed of a callback to execute and a duration for how long to keep calling it for.

```c++
auto animation = ArrayAnimation{ std::array {
  AnimationFrame{Duration::Seconds(1), [](auto& ctx) { strip.fill(Color::RED() * (1.0f - ctx.percentComplete)); }},
  AnimationFrame{Duration::Seconds(1)}, // Does Nothing
  AnimationFrame{Duration::Seconds(1), [](auto& ctx) { strip.fill(Color::GREEN() * (1.0f - ctx.percentComplete)); }},
  AnimationFrame{Duration::Seconds(1)}, // Does Nothing
  AnimationFrame{Duration::Seconds(1), [](auto& ctx) { strip.fill(Color::BLUE() * (1.0f - ctx.percentComplete)); }},
  AnimationFrame{Duration::Seconds(1)}, // Does Nothing
}};

auto handle = Animations::start(animation, true /* loop */ ));
```

### Effects
Effects are one of the ways to color pixels.

The primary way to customize the coloring behavior of Effects is through a **Shader**.
A shader is a function that is invoked for each "activated" pixel.
It takes in the pixel's current color and a set of parameters that vary depending on the effect and returns a new color for that pixel

Different effects activate pixels in different ways, for example a fill effect will activate all pixels uniformly and has no concept of cycles. Its only shader parameter is the pixel's position.
In contrast, a Chase effect activates only a subset of Pixels on a given strip based on the position of activated segment.
It's Shader has more information about what cycle the effect is in, what position within the segment the pixel is, its overall position in the strip, etc.

### Gradients

Gradients are a smooth blending of 2 or more colors that have a `sample(position)` method that returns a color linearly interpolated between the base colors.
`Gradient` is the interface used by other parts of the system, while `ArrayGradient` is an implementation using a `std::array` as a backing storage.
`MirroredGradient` is a helper that can be used to create a gradient that wraps its colors back around.

Gradients are composed of an ordered list of `GradientStops`. Each stop has a `float position` and a `Color color`;
Position must be between `0` and `1` and each stop must have a position greater than the one before it.
If position is not specified for all the stops, they are defaulted to be evenly spaced apart.

```c++
auto sunset = ArrayGradient(std::array {
  GradientStop{0.0f, Color::BLUE()},
  GradientStop{0.5f, Color::RED()},
  GradientStop{1.0f, Color::ORANGE()},
});

auto ice = MirroredGradient(std::array {
  GradientStop{Color::CYAN()},              // position defaulted to 0.0f
  GradientStop{Color::BLUE()},              // position defaulted to 1 / 3
  GradientStop{Color::PURPLE()},            // position defaulted to 2 / 3
  GradientStop{Color::MAGENTA()},           // position defaulted to 0.0f
});
```

### Timers

## Debugging Tools

### Built-in LED

Use `Debug::SetBlinker(color, predicate)` to 

| Color  | Default Meaning                           |
|--------|-------------------------------------------|
| Red    | Debug Fault Triggered                     |
| Yellow | (rgbcar uses for Vehicle Logging Running) |
| Green  | (rgbcar uses for Vehicle Connected)       |
| Cyan   |                                           |
| Blue   | Connected to WiFi                         |
| Purple |                                           |

### Logs
Macros such as `INFO()` and `ERROR()` can be used to print logs to the Serial output. The library makes
use of these macros for reporting issues at runtime

| Logging Macro      | Description                                                                                |
|--------------------|--------------------------------------------------------------------------------------------|
| `TRACE(msg, ...)`  | Print a log message with level _Trace_. Intended for low-level or frequent messages        |
| `INFO(msg, ...)`   | Print a log message with level _Info_. Intended for high-level messages                    |
| `ERROR(msg, ...)`  | Print a log message with level _Error_. Intended for abnormal events                       |

| Configuration Macro | Description                                                                 |
|---------------------|-----------------------------------------------------------------------------|
| `RGB_DEBUG`         | Sets `RGB_LOG_LEVEL` to `1`. Meant to do other debug-related things as well |
| `RGB_LOG_LEVEL`     | `0=ERROR`, `1=INFO`, `2=TRACE`. Defaults to `0`                             |

## Terminology

### LED vs Pixel vs RGBW
- **LED** is the physical component that lights up
- **Pixel** is an abstract representation to usually 1 LED
- **RGB/W** represent the 3/4 possible color channels for an LED. Not all LEDs have W.
  - App represents them as `float` value between `[0-1]`, but device expects `unsigned char` value (`[0-255]`)

## TODO 

(in no particular order)

- Effects should have a delay until they start again, so we don't _need_ DeadPixelLists to pad the endings