#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <mutex>
#include <array>
#include <utility>
#include <cstddef>

namespace rgb {

template <typename T, size_t SIZE>
class CircularQueue {
public:
	static_assert((SIZE & (SIZE - 1)) == 0 && SIZE > 0);

	auto push(T value) -> bool;
  auto pop(T& result) -> bool;
	auto isEmpty() const -> bool;

private:
	auto lockedIsEmpty() const -> bool;
	static auto increment(size_t& index) -> void {
		index++;
		index = index & (SIZE - 1);
	}

	std::array<T, SIZE> data{};
	size_t back{};
	size_t front{};
	bool full{};
	mutable std::mutex mu{};
};

template<typename T, size_t SIZE>
auto CircularQueue<T, SIZE>::push(T value) -> bool {
	std::lock_guard guard{mu};
	if (full) {
		return false;
	}

	data[back] = std::move(value);
	increment(back);

	if (front == back) {
		full = true;
	}

	return true;
}

template<typename T, size_t SIZE>
auto CircularQueue<T, SIZE>::pop(T& result) -> bool {
	std::lock_guard guard{mu};
	if (lockedIsEmpty()) {
		return false;
	}

	result = std::move(data[front]);
	increment(front);
	full = false;

	return true;
}

template<typename T, size_t SIZE>
auto CircularQueue<T, SIZE>::isEmpty() const -> bool {
	std::lock_guard guard{mu};
	return lockedIsEmpty();
}

template<typename T, size_t SIZE>
auto CircularQueue<T, SIZE>::lockedIsEmpty() const -> bool {
	return front == back && !full;
}
}

#endif

