
#define CATCH_CONFIG_MAIN  // Catch2 provides the main()
#include <catch2/catch_all.hpp>
#include "Queue.h"

TEST_CASE("Queue Basic Operations", "[Queue]") {
    Queue<int> q(3);

    SECTION("Initial count is zero") {
        REQUIRE(q.Count() == 0);
    }

    SECTION("Push and Pop Increase and Decrease Count") {
        q.Push(42);
        REQUIRE(q.Count() == 1);
        int value = q.Pop();
        REQUIRE(value == 42);
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