
#define CATCH_CONFIG_MAIN  // Catch2 provides the main()
#include <catch2/catch_all.hpp>
#include <thread>
#include "Queue.h"

TEST_CASE("Queue Basic Operations", "[Queue]") {
    Queue<int> q(3);

    SECTION("Initial count is zero") {
        REQUIRE(q.Count() == 0);
    }

    SECTION("Push and Pop Increase and Decrease Count") {
        q.Push(5);
        REQUIRE(q.Count() == 1);
        int value = q.Pop();
        REQUIRE(value == 5);
        REQUIRE(q.Count() == 0);
    }
    
    SECTION("Full Queue drops oldest") {
        q.Push(1);
        q.Push(2);
        q.Push(3);
        q.Push(4); 
        REQUIRE(q.Count() == 3);
        int value = q.Pop();
        REQUIRE(value == 2); 
    }
    
    SECTION("PopWithTimeout throws exception when empty") {
        // When the queue is empty, PopWithTimeout should throw a timeout exception.
        REQUIRE_THROWS_AS(q.PopWithTimeout(100), std::runtime_error);
    }
}


void consumer(Queue<int>& q, std::vector<int> &consumed){
    for (int i = 0; i < 4; i++) {
            consumed.push_back(q.Pop());
    }
}

void producer(Queue<int>& q){
    for (int i = 1; i <= 5; i++) {
            q.Push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
        }
}


TEST_CASE("Single Producer Single Consumer", "[Queue]") {
    Queue<int> q(5); // Queue with capacity 5
    std::vector<int> consumed; // Stores values popped by the consumer
    

    std::thread prod(producer, std::ref(q)); 
    std::thread cons(consumer, std::ref(q), std::ref(consumed));

    prod.join();
    cons.join();

    SECTION("Final Count is 1") {
        REQUIRE(q.Count() == 1);
    }
    
    SECTION("FIFO Behavior"){
        REQUIRE(consumed == std::vector<int>{1, 2, 3, 4}); // FIFO behavior check
    }
}