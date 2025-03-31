#ifndef CIRCULAR_DATA_H
#define CIRCULAR_DATA_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include "CircularIndex.h"

namespace rgb {

class ThreadCommand;
class CircularBuffer {
public:
	static constexpr int SIZE = 32;

	CircularBuffer();
	CircularBuffer(const CircularBuffer&) = delete;
	CircularBuffer(CircularBuffer &&) = delete;
	CircularBuffer& operator = (const CircularBuffer &) = delete;
	CircularBuffer& operator = (const CircularBuffer &&) = delete;
	~CircularBuffer() = default;

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

