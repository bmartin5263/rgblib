//
// Created by Brandon on 8/17/26.
//

#include "NativeDisplay.h"

#if defined(RGB_NATIVE)

#include "Util.h"
#include "Log.h"

namespace rgb {

static constexpr auto PIXEL_SIZE = 10;
static constexpr auto PIXEL_GAP = 2;
static constexpr auto WINDOW_MARGIN = 20;
static constexpr auto MAX_ROW_PIXELS = 130;
static constexpr auto STRIP_GAP = 6; // extra space between strips, beyond wrapped rows of the same strip

namespace {
// Strips longer than MAX_ROW_PIXELS wrap onto additional visual rows.
constexpr auto RowsFor(u16 pixelCount) -> int {
  return (pixelCount + MAX_ROW_PIXELS - 1) / MAX_ROW_PIXELS;
}
}

auto NativeDisplay::Instance() -> NativeDisplay& {
  static NativeDisplay instance;
  return instance;
}

auto NativeDisplay::registerStrip(NativeRenderable& strip) -> void {
  mRows.push_back(&strip);
}

auto NativeDisplay::ensureWindow() -> void {
  if (mWindow) {
    return;
  }

  u16 widestRow = 0;
  auto totalRows = 0;
  for (auto* strip : mRows) {
    auto count = strip->pixelCount();
    widestRow = Max(widestRow, Min(count, static_cast<u16>(MAX_ROW_PIXELS)));
    totalRows += RowsFor(count);
  }

  auto stripGaps = mRows.empty() ? 0 : static_cast<int>(mRows.size()) - 1;
  auto width = static_cast<int>(widestRow) * (PIXEL_SIZE + PIXEL_GAP) + WINDOW_MARGIN * 2;
  auto height = totalRows * (PIXEL_SIZE + PIXEL_GAP) + stripGaps * STRIP_GAP + WINDOW_MARGIN * 2;
  mWindow.reset(SDL_CreateWindow(
    "RGB Native Preview",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    width, height,
    SDL_WINDOW_SHOWN
  ));
  mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED));
  INFO("Opened native display window (%i rows, %i pixels wide)", totalRows, static_cast<int>(widestRow));
}

auto NativeDisplay::present() -> void {
  ensureWindow();

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      std::exit(0);
    }
  }

  SDL_SetRenderDrawColor(mRenderer.get(), 0, 0, 0, 255);
  SDL_RenderClear(mRenderer.get());

  auto visualRow = 0;
  auto stripIndex = 0;
  for (auto* strip : mRows) {
    auto count = strip->pixelCount();
    for (auto i = 0; i < count; ++i) {
      auto pixel = strip->renderedPixel(i);
      auto col = i % MAX_ROW_PIXELS;
      auto subRow = i / MAX_ROW_PIXELS;
      SDL_Rect rect {
        WINDOW_MARGIN + col * (PIXEL_SIZE + PIXEL_GAP),
        WINDOW_MARGIN + (visualRow + subRow) * (PIXEL_SIZE + PIXEL_GAP) + stripIndex * STRIP_GAP,
        PIXEL_SIZE,
        PIXEL_SIZE
      };
      SDL_SetRenderDrawColor(mRenderer.get(), FloatToByte(pixel.r), FloatToByte(pixel.g), FloatToByte(pixel.b), 255);
      SDL_RenderFillRect(mRenderer.get(), &rect);
    }
    visualRow += RowsFor(count);
    ++stripIndex;
  }

  SDL_RenderPresent(mRenderer.get());
}

}

#endif //defined(RGB_NATIVE)
