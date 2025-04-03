//
// Created by Brandon on 3/30/25.
//

#ifndef RGBLIB_THREADPOOL_H
#define RGBLIB_THREADPOOL_H

#include <functional>
#include <thread>
#include "CircularBuffer.h"

namespace rgb {

class ThreadCommand;
class ThreadPool {
public:
  static auto Start() -> void { Instance().start(); }
  static auto SubmitTask(ThreadCommand& task) -> void { Instance().submitTask(task); };

private:
//  std::array<std::thread, 2> pool{};
  CircularBuffer commandBuffer{};

  static auto Instance() -> ThreadPool& {
    static ThreadPool instance;
    return instance;
  }

  auto start() -> void;
  auto submitTask(ThreadCommand& task) -> void;
};

}


#endif //RGBLIB_THREADPOOL_H
