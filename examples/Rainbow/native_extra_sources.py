# library.json's "frameworks": "arduino" makes LDF drop rgblib's .cpp files
# under platform=native, so compile them directly here instead.
Import("env")

RGBLIB_SRC = "../../src"

env.BuildSources("$BUILD_DIR/rgblib_core", RGBLIB_SRC + "/core", "+<*.cpp>")
env.BuildSources("$BUILD_DIR/rgblib_animation", RGBLIB_SRC + "/core/animation", "+<*.cpp>")
env.BuildSources("$BUILD_DIR/rgblib_led", RGBLIB_SRC + "/core/led", "+<*.cpp>")
env.BuildSources("$BUILD_DIR/rgblib_pixel", RGBLIB_SRC + "/core/pixel", "+<*.cpp>")
env.BuildSources("$BUILD_DIR/rgblib_sensor", RGBLIB_SRC + "/core/sensor", "+<*.cpp>")
env.BuildSources("$BUILD_DIR/rgblib_threading", RGBLIB_SRC + "/core/threading", "+<*.cpp>")
env.BuildSources("$BUILD_DIR/rgblib_time", RGBLIB_SRC + "/core/time", "+<*.cpp>")
env.BuildSources("$BUILD_DIR/rgblib_effect", RGBLIB_SRC + "/effect", "+<*.cpp>")
env.BuildSources("$BUILD_DIR/rgblib_priv", RGBLIB_SRC + "/core/priv", "+<*.cpp>")
env.BuildSources("$BUILD_DIR/rgblib_network", RGBLIB_SRC + "/core/network", "+<*.cpp>")
