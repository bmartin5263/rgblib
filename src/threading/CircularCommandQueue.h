#ifndef CIRCULAR_DATA_H
#define CIRCULAR_DATA_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include "CircularIndex.h"

namespace rgb {

class ThreadCommand;
class CircularCommandQueue {
public:
	static constexpr int SIZE = 32;

	CircularCommandQueue();
	CircularCommandQueue(const CircularCommandQueue&) = delete;
	CircularCommandQueue(CircularCommandQueue &&) = delete;
	CircularCommandQueue& operator = (const CircularCommandQueue &) = delete;
	CircularCommandQueue& operator = (const CircularCommandQueue &&) = delete;
	~CircularCommandQueue() = default;

	void push(ThreadCommand* command);
  ThreadCommand* pop();
	bool isEmpty();

	void notify();
	void wait();

private:

	ThreadCommand* data[SIZE];
	CircularIndex back;
	CircularIndex front;
	bool empty;
	bool full;
	std::mutex mu;
	std::condition_variable cond;

};

}

#endif

