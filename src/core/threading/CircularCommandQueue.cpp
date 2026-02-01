#include "CircularCommandQueue.h"
#include "Assertions.h"

namespace rgb {

CircularCommandQueue::CircularCommandQueue()
	: data(), back(SIZE), front(SIZE), empty(true), full(false), mu(), cond()
{
	// initialized data
	for (int i = 0; i < SIZE; i++){
		this->data[i] = nullptr;
	}
}

void CircularCommandQueue::push(ThreadCommand* command) {
  std::unique_lock<std::mutex> locker(mu);
  ASSERT(this->front != this->back || this->empty, "CircularCommandQueue full");

  this->data[this->back.getIndex()] = command;
  this->back++;
  this->empty = false;
  if (this->front == this->back) {
    this->full = true;
  }

  locker.unlock();
  cond.notify_one();
}

ThreadCommand* CircularCommandQueue::pop(){
  std::unique_lock<std::mutex> locker(mu);

  while (empty) {
    cond.wait(locker);
  }

  ASSERT(this->front != this->back || this->full, "CircularCommandQueue empty");

  auto command = this->data[this->front.getIndex()];
  this->data[this->front.getIndex()] = nullptr;
  this->front++;
  this->full = false;
  if (this->front == this->back) {
    this->empty = true;
  }

  ASSERT(command != nullptr, "Command is null");

  return command;
}

bool CircularCommandQueue::isEmpty() {
	std::lock_guard<std::mutex> locker(mu);
	return empty;
}

void CircularCommandQueue::wait() {
	std::unique_lock<std::mutex> locker(mu);
	cond.wait(locker, [&]() { return !empty; });
}

void CircularCommandQueue::notify() {
	std::lock_guard<std::mutex> lock(mu);
	cond.notify_one();
}

}