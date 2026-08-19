//
// Created by Brandon on 8/17/26.
//

#include "NativeDisplay.h"

#if defined(RGB_NATIVE)

#include <cmath>
#include <optional>

#include "Util.h"
#include "Log.h"
#include "Application.h"
#include "Clock.h"
#include "IRButtonType.h"

namespace {
auto mapToIRButtonType(const SDL_Keysym& keysym) -> std::optional<IRButtonType> {
  auto shifted = (keysym.mod & KMOD_SHIFT) != 0;
  switch (keysym.sym) {
    case SDLK_0:
      return std::make_optional(IRButtonType::BUTTON_0);
    case SDLK_1:
      return std::make_optional(IRButtonType::BUTTON_1);
    case SDLK_2:
      return std::make_optional(IRButtonType::BUTTON_2);
    case SDLK_3:
      return std::make_optional(shifted ? IRButtonType::BUTTON_HASH : IRButtonType::BUTTON_3);
    case SDLK_4:
      return std::make_optional(IRButtonType::BUTTON_4);
    case SDLK_5:
      return std::make_optional(IRButtonType::BUTTON_5);
    case SDLK_6:
      return std::make_optional(IRButtonType::BUTTON_6);
    case SDLK_7:
      return std::make_optional(IRButtonType::BUTTON_7);
    case SDLK_8:
      return std::make_optional(shifted ? IRButtonType::BUTTON_STAR : IRButtonType::BUTTON_8);
    case SDLK_9:
      return std::make_optional(IRButtonType::BUTTON_9);
    case SDLK_k:
      return std::make_optional(IRButtonType::BUTTON_OK);
    case SDLK_DOWN:
      return std::make_optional(IRButtonType::BUTTON_DOWN);
    case SDLK_UP:
      return std::make_optional(IRButtonType::BUTTON_UP);
    case SDLK_LEFT:
      return std::make_optional(IRButtonType::BUTTON_LEFT);
    case SDLK_RIGHT:
      return std::make_optional(IRButtonType::BUTTON_RIGHT);
    case SDLK_HASH:
      return std::make_optional(IRButtonType::BUTTON_HASH);
    case SDLK_ASTERISK:
      return std::make_optional(IRButtonType::BUTTON_STAR);
    default:
      return std::nullopt;
  }
}
}

namespace rgb {

static constexpr auto PIXEL_SIZE = 10;
static constexpr auto PIXEL_GAP = 2;
static constexpr auto WINDOW_MARGIN = 20;
static constexpr auto MAX_ROW_PIXELS = 130;
static constexpr auto MIN_ROW_PIXELS = 40; // keeps narrow matrices from forcing a thin, tall window
static constexpr auto STRIP_GAP = 6; // extra space between rows/columns, beyond wrapped rows of the same strip/matrix
static constexpr auto MAX_CONTENT_WIDTH_PIXELS = MAX_ROW_PIXELS * (PIXEL_SIZE + PIXEL_GAP);

// [0, 50] input covers the first half of displayed brightness, [51, 255] the second half.
static constexpr auto LOG_CURVE_INPUT_FLOOR = 50.0f;
static constexpr auto LOG_CURVE_OUTPUT_FLOOR = 127.0f;
// Displayed brightness for the dimmest nonzero channel, so it stays visible against black.
static constexpr auto LOG_CURVE_MIN_VISIBLE = 50.0f;
// Higher values steepen the curve's rise near zero, spreading low channel values further apart.
static constexpr auto LOG_CURVE_STEEPNESS = 15.0f;

namespace {
// Logarithmic brightness curve for on-screen debug visibility only.
auto LogarithmicBrightness(u8 channel) -> u8 {
  if (channel == 0) {
    return 0;
  }
  auto curveNorm = std::log1p(LOG_CURVE_STEEPNESS);
  if (static_cast<float>(channel) <= LOG_CURVE_INPUT_FLOOR) {
    auto t = static_cast<float>(channel) / LOG_CURVE_INPUT_FLOOR;
    auto curved = std::log1p(t * LOG_CURVE_STEEPNESS) / curveNorm;
    return static_cast<u8>(LOG_CURVE_MIN_VISIBLE + curved * (LOG_CURVE_OUTPUT_FLOOR - LOG_CURVE_MIN_VISIBLE));
  }
  auto t = (static_cast<float>(channel) - LOG_CURVE_INPUT_FLOOR) / (255.0f - LOG_CURVE_INPUT_FLOOR);
  auto curved = std::log1p(t * LOG_CURVE_STEEPNESS) / curveNorm;
  return static_cast<u8>(LOG_CURVE_OUTPUT_FLOOR + curved * (255.0f - LOG_CURVE_OUTPUT_FLOOR));
}

// Renderables wider than their available columns wrap onto additional visual rows.
constexpr auto RowsFor(u16 pixelCount, uint columns) -> int {
  return static_cast<int>((pixelCount + columns - 1) / columns);
}

constexpr auto EffectiveColumns(const NativeRenderable& renderable) -> uint {
  return Min(renderable.columns(), static_cast<uint>(MAX_ROW_PIXELS));
}

// Screen-pixel pitch (size + gap) between adjacent columns/rows for this renderable,
// scaled down for visually smaller devices like fiber strands.
constexpr auto ItemPitch(const NativeRenderable& renderable) -> int {
  return static_cast<int>((PIXEL_SIZE + PIXEL_GAP) * renderable.pixelScale());
}

constexpr auto ItemSquareSize(const NativeRenderable& renderable) -> int {
  return static_cast<int>(PIXEL_SIZE * renderable.pixelScale());
}

// Packs matrices left to right into lines, wrapping onto a new line once a line runs out of width.
auto PackMatrixLines(const std::vector<NativeRenderable*>& matrices) -> std::vector<std::vector<NativeRenderable*>> {
  std::vector<std::vector<NativeRenderable*>> lines;
  auto currentLineWidth = 0;
  for (auto* matrix : matrices) {
    auto matrixWidth = static_cast<int>(EffectiveColumns(*matrix)) * (PIXEL_SIZE + PIXEL_GAP);
    if (lines.empty() || currentLineWidth + STRIP_GAP + matrixWidth > MAX_CONTENT_WIDTH_PIXELS) {
      lines.emplace_back();
      currentLineWidth = 0;
    }
    if (!lines.back().empty()) {
      currentLineWidth += STRIP_GAP;
    }
    lines.back().push_back(matrix);
    currentLineWidth += matrixWidth;
  }
  return lines;
}
}

auto NativeDisplay::Instance() -> NativeDisplay& {
  static NativeDisplay instance;
  return instance;
}

auto NativeDisplay::registerStrip(NativeRenderable& strip) -> void {
  mStrips.push_back(&strip);
}

auto NativeDisplay::registerMatrix(NativeRenderable& matrix) -> void {
  mMatrices.push_back(&matrix);
}

auto NativeDisplay::ensureWindow() -> void {
  if (mWindow) {
    return;
  }

  mMatrixLines = PackMatrixLines(mMatrices);

  auto widestRowPixels = MIN_ROW_PIXELS * (PIXEL_SIZE + PIXEL_GAP);
  auto totalHeightPixels = 0;
  for (auto* strip : mStrips) {
    auto columns = EffectiveColumns(*strip);
    auto pitch = ItemPitch(*strip);
    widestRowPixels = Max(widestRowPixels, static_cast<int>(columns) * pitch);
    totalHeightPixels += RowsFor(strip->pixelCount(), columns) * pitch;
  }
  for (const auto& line : mMatrixLines) {
    auto lineWidthPixels = 0;
    auto lineHeightPixels = 0;
    for (auto* matrix : line) {
      auto columns = EffectiveColumns(*matrix);
      auto pitch = ItemPitch(*matrix);
      if (lineWidthPixels > 0) {
        lineWidthPixels += STRIP_GAP;
      }
      lineWidthPixels += static_cast<int>(columns) * pitch;
      lineHeightPixels = Max(lineHeightPixels, RowsFor(matrix->pixelCount(), columns) * pitch);
    }
    widestRowPixels = Max(widestRowPixels, lineWidthPixels);
    totalHeightPixels += lineHeightPixels;
  }

  auto sectionCount = static_cast<int>(mStrips.size() + mMatrixLines.size());
  auto sectionGaps = sectionCount == 0 ? 0 : sectionCount - 1;
  auto width = widestRowPixels + WINDOW_MARGIN * 2;
  auto height = totalHeightPixels + sectionGaps * STRIP_GAP + WINDOW_MARGIN * 2;
  mWindow.reset(SDL_CreateWindow(
    "RGB Native Preview",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    width, height,
    SDL_WINDOW_SHOWN
  ));
  mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED));
  INFO("Opened native display window (%i x %i pixels)", width, height);
}

auto NativeDisplay::present() -> void {
  ensureWindow();

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        // Automatically fires when single-window app window closes
        std::exit(0);
      case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(mWindow.get())) {
          std::exit(0);
        }
        break;
      case SDL_KEYDOWN:
        if (mKeyEventsEnabled) {
          if (auto irButton = mapToIRButtonType(event.key.keysym); irButton && event.key.repeat == 0) {
            Application::PublishSystemEvent(IRButtonPressed{{Clock::Now()}, irButton.value()});
          }
        }
    }
  }

  SDL_SetRenderDrawColor(mRenderer.get(), 0, 0, 0, 255);
  SDL_RenderClear(mRenderer.get());

  auto visualOffsetPixels = 0;
  auto sectionIndex = 0;
  auto drawItem = [&](NativeRenderable* item, int xOffsetPixels, int rowOffsetPixels) {
    auto count = item->pixelCount();
    auto columns = EffectiveColumns(*item);
    auto pitch = ItemPitch(*item);
    auto squareSize = ItemSquareSize(*item);
    for (u16 i = 0; i < count; ++i) {
      auto pixel = item->renderedPixel(i);
      auto col = i % columns;
      auto subRow = i / columns;
      SDL_Rect rect {
        WINDOW_MARGIN + xOffsetPixels + static_cast<int>(col) * pitch,
        WINDOW_MARGIN + rowOffsetPixels + static_cast<int>(subRow) * pitch + sectionIndex * STRIP_GAP,
        squareSize,
        squareSize
      };
      SDL_SetRenderDrawColor(
        mRenderer.get(),
        LogarithmicBrightness(FloatToByte(pixel.r)),
        LogarithmicBrightness(FloatToByte(pixel.g)),
        LogarithmicBrightness(FloatToByte(pixel.b)),
        255
      );
      SDL_RenderFillRect(mRenderer.get(), &rect);
    }
  };

  for (auto* strip : mStrips) {
    drawItem(strip, 0, visualOffsetPixels);
    visualOffsetPixels += RowsFor(strip->pixelCount(), EffectiveColumns(*strip)) * ItemPitch(*strip);
    ++sectionIndex;
  }
  for (const auto& line : mMatrixLines) {
    auto xOffsetPixels = 0;
    auto lineHeightPixels = 0;
    for (auto* matrix : line) {
      drawItem(matrix, xOffsetPixels, visualOffsetPixels);
      auto columns = EffectiveColumns(*matrix);
      xOffsetPixels += static_cast<int>(columns) * ItemPitch(*matrix) + STRIP_GAP;
      lineHeightPixels = Max(lineHeightPixels, RowsFor(matrix->pixelCount(), columns) * ItemPitch(*matrix));
    }
    visualOffsetPixels += lineHeightPixels;
    ++sectionIndex;
  }

  SDL_RenderPresent(mRenderer.get());
}

}

#endif //defined(RGB_NATIVE)
