#include <gtest/gtest.h>

#include <thread>
#include <vector>

#include "CircularQueue.h"

using rgb::CircularQueue;

constexpr int QUEUE_SIZE = 32;
using IntQueue = CircularQueue<int, QUEUE_SIZE>;

TEST(CircularQueueTest, StartsEmpty) {
  IntQueue queue;
  int out{};

  EXPECT_TRUE(queue.isEmpty());
  EXPECT_FALSE(queue.pop(out));
}

TEST(CircularQueueTest, PopsInFifoOrder) {
  IntQueue queue;
  int out{};

  EXPECT_TRUE(queue.push(1));
  EXPECT_TRUE(queue.push(2));
  EXPECT_TRUE(queue.push(3));
  EXPECT_FALSE(queue.isEmpty());

  EXPECT_TRUE(queue.pop(out));
  EXPECT_EQ(out, 1);
  EXPECT_TRUE(queue.pop(out));
  EXPECT_EQ(out, 2);
  EXPECT_TRUE(queue.pop(out));
  EXPECT_EQ(out, 3);
  EXPECT_TRUE(queue.isEmpty());
  EXPECT_FALSE(queue.pop(out));
}

TEST(CircularQueueTest, RejectsPushWhenFull) {
  IntQueue queue;

  for (int i = 0; i < QUEUE_SIZE; i++) {
    EXPECT_TRUE(queue.push(i));
  }

  EXPECT_FALSE(queue.push(999));
  EXPECT_FALSE(queue.isEmpty());
}

TEST(CircularQueueTest, DrainsCompletelyFullQueue) {
  IntQueue queue;
  int out{};

  for (int i = 0; i < QUEUE_SIZE; i++) {
    ASSERT_TRUE(queue.push(i));
  }

  for (int i = 0; i < QUEUE_SIZE; i++) {
    ASSERT_TRUE(queue.pop(out)) << "failed at element " << i;
    EXPECT_EQ(out, i);
  }

  EXPECT_TRUE(queue.isEmpty());
  EXPECT_FALSE(queue.pop(out));
}

TEST(CircularQueueTest, AcceptsPushAfterPopFromFull) {
  IntQueue queue;
  int out{};

  for (int i = 0; i < QUEUE_SIZE; i++) {
    ASSERT_TRUE(queue.push(i));
  }

  ASSERT_TRUE(queue.pop(out));
  EXPECT_EQ(out, 0);
  EXPECT_TRUE(queue.push(100));
  EXPECT_FALSE(queue.push(101));
}

TEST(CircularQueueTest, WrapsAroundIndices) {
  IntQueue queue;
  int out{};

  for (int i = 0; i < QUEUE_SIZE * 3; i++) {
    ASSERT_TRUE(queue.push(i));
    ASSERT_TRUE(queue.pop(out));
    EXPECT_EQ(out, i);
  }

  EXPECT_TRUE(queue.isEmpty());
}

TEST(CircularQueueTest, PreservesOrderAcrossWrapWithPartialFill) {
  IntQueue queue;
  int out{};
  int next_push = 0;
  int next_pop = 0;

  for (int round = 0; round < 10; round++) {
    for (int i = 0; i < 7; i++) {
      ASSERT_TRUE(queue.push(next_push++));
    }
    for (int i = 0; i < 5; i++) {
      ASSERT_TRUE(queue.pop(out));
      EXPECT_EQ(out, next_pop++);
    }
  }

  while (queue.pop(out)) {
    EXPECT_EQ(out, next_pop++);
  }

  EXPECT_EQ(next_pop, next_push);
}

TEST(CircularQueueTest, SingleProducerSingleConsumerKeepsOrder) {
  constexpr int COUNT = 10000;
  IntQueue queue;
  std::vector<int> received;
  received.reserve(COUNT);

  std::thread producer{[&queue] {
    for (int i = 0; i < COUNT; i++) {
      while (!queue.push(i)) {
        std::this_thread::yield();
      }
    }
  }};

  std::thread consumer{[&queue, &received] {
    int out{};
    while (static_cast<int>(received.size()) < COUNT) {
      if (queue.pop(out)) {
        received.push_back(out);
      } else {
        std::this_thread::yield();
      }
    }
  }};

  producer.join();
  consumer.join();

  ASSERT_EQ(received.size(), static_cast<std::size_t>(COUNT));
  for (int i = 0; i < COUNT; i++) {
    ASSERT_EQ(received[i], i);
  }
  EXPECT_TRUE(queue.isEmpty());
}
