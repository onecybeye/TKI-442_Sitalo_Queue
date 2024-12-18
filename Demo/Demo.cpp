#include "Queue.h"
#include <iostream>

using namespace queue;

int main() {
    Queue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    std::cout << "Первый элемент: " << q.front() << std::endl; // 10
    std::cout << "Очередь: " << q << std::endl;               // 10 20 30

    q.dequeue();
    std::cout << "После удаления первого элемента: " << q << std::endl; // 20 30

    return 0;
}
