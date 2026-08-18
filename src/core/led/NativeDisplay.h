//
// Created by Brandon on 8/17/26.
//

#ifndef RGBLIB_NATIVEDISPLAY_H
#define RGBLIB_NATIVEDISPLAY_H

#if defined(RGB_NATIVE)

#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include "NativeRenderable.h"

namespace rgb {

struct SDLWindowDeleter {
  auto operator()(SDL_Window* window) const -> void { SDL_DestroyWindow(window); }
};

struct SDLRendererDeleter {
  auto operator()(SDL_Renderer* renderer) const -> void { SDL_DestroyRenderer(renderer); }
};

struct SDLVideoGuard {
  SDLVideoGuard() { SDL_Init(SDL_INIT_VIDEO); }
  ~SDLVideoGuard() { SDL_Quit(); }

  SDLVideoGuard(const SDLVideoGuard& rhs) = delete;
  SDLVideoGuard(SDLVideoGuard&& rhs) noexcept = delete;
  SDLVideoGuard& operator=(const SDLVideoGuard& rhs) = delete;
  SDLVideoGuard& operator=(SDLVideoGuard&& rhs) noexcept = delete;
};

/**
 * Shared SDL window that renders every registered NativeLEDStrip, one
 * horizontal row per strip, pulling each strip's pixel data directly at
 * present() time.
 */
class NativeDisplay {
public:
  static auto Setup() -> void { Instance(); }
  static auto Register(NativeRenderable& strip) -> void { Instance().registerStrip(strip); }
  static auto Present() -> void { Instance().present(); }

  NativeDisplay(const NativeDisplay& rhs) = delete;
  NativeDisplay(NativeDisplay&& rhs) noexcept = delete;
  NativeDisplay& operator=(const NativeDisplay& rhs) = delete;
  NativeDisplay& operator=(NativeDisplay&& rhs) noexcept = delete;

private:
  NativeDisplay() = default;
  ~NativeDisplay() = default;

  static auto Instance() -> NativeDisplay&;

  auto registerStrip(NativeRenderable& strip) -> void;
  auto present() -> void;

  // Window created lazily so it can be properly sized to the LED load
  auto ensureWindow() -> void;

  // Order matters for mVideo, mWindow, mRenderer: they are declared in reverse-destruction order
  SDLVideoGuard mVideo;
  std::unique_ptr<SDL_Window, SDLWindowDeleter> mWindow;
  std::unique_ptr<SDL_Renderer, SDLRendererDeleter> mRenderer;
  std::vector<NativeRenderable*> mRows{};
};

}

#endif //defined(RGB_NATIVE)

#endif //RGBLIB_NATIVEDISPLAY_H
