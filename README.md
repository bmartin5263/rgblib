# RGBLib

## TODO
- [ ] Resiliency - able to automatically recover subsystems if connection issues

## Debugging Tools

### Logs
Macros such as `INFO()` and `ERROR()` can be used to print logs to the Serial output. The library makes
use of these macros for reporting issues at runtime

| Logging Macro      | Description                                                                                |
|--------------------|--------------------------------------------------------------------------------------------|
| `PRINTF(msg, ...)` | Print a log message without any header/timestamp. Always enabled, intended for real output |
| `TRACE(msg, ...)`  | Print a log message with level _Trace_. Intended for low-level or repeated messages        |
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