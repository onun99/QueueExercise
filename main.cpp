#include <iostream>
#include "Queue.h"

int main() {

    Queue<int> q(3); // Initialize Queu with size 3

    q.Push(1);
    q.Push(2);
    q.Push(3);

    std::cout << q.Pop() << std::endl;
    std::cout << q.Pop() << std::endl;
    std::cout << q.Count() << std::endl;
    std::cout << q.Size() << std::endl;

    return(0);
}