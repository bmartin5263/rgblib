```c++
StorageDevice sdCard{...};
PixelList debugLed{...};
Logging::Setup()
// Persistent Storage
    .SaveLogsTo(sdCard, filename="rgblib{}.log")
// Performance Tuning
    .BufferSize(20)                             // Store 20 messages before flushing
    .BufferFlushTimeout(Duration::Seconds(1))   // Automatically flush after 1 second
// Start the system
    .Start();

Debug::Setup()
    .IndicatorLED(debugLed)

INFO("Hello, World!");
INFO("Hello, %s", "World!");

ERROR("Something went wrong...");

FAIL("Unhandled Value");
ASSERT(x > 0, "Expected positive number");
```