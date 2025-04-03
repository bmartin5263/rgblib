//
// Created by Brandon on 3/30/25.
//

#include "ThreadPool.h"
#include "Log.h"
#include "CircularBuffer.h"
#include "ThreadCommand.h"

namespace rgb {

auto ThreadPool::start() -> void {
  INFO("Starting ThreadPool");

//  for (auto i = 0; i < 1; ++i) {
//    auto t = std::thread([&](){
//      while (true) {
//        auto command = commandBuffer.pop();
//        if (command != nullptr) {
//          command->execute();
//        }
//      }
//    });
//    t.detach();
//  }
}

auto ThreadPool::submitTask(ThreadCommand& task) -> void {
  commandBuffer.push(&task);
}

}