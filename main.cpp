#include <iostream>
#include <thread>
#include <chrono>
#include "Queue.h"

void producer(Queue<int>& q) {
    // Push three integers.
    for (int i = 1; i <= 3; ++i) {
        std::cout << "Producer: Pushing " << i << std::endl;
        q.Push(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void consumer(Queue<int>& q) {
    // Pop three integers.
    for (int i = 0; i < 3; ++i) {
        int value = q.PopWithTimeout(900);
        std::cout << "Consumer: Popped " << value << std::endl;
    }
}

int main() {

    Queue<int> q(3); // Initialize Queu with size 3

    // Start producer and consumer threads.
    //std::ref is used because std::thread copies its arguments when starting a new thread and the consumer/producer loop expect references
    std::thread prod(producer, std::ref(q)); 
    std::thread cons(consumer, std::ref(q));

    prod.join();
    cons.join();

    return(0);
}