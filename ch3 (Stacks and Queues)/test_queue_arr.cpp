#include <iostream>
#include "queue_arr.h"

int main()
{
    Queue queue(2); // force queue to dynamically resize
    for (int i = 0; i < 5; ++i)
        queue.Enqueue(i);

    std::cout << "queue: " << queue << std::endl;

    Queue copy(queue);
    std::cout << "copy: " << copy << std::endl;

    int data = queue.Front();
    queue.Dequeue();
    std::cout << "queue.Dequeue(): [" << data << "] " <<  queue << std::endl;

    queue.Enqueue(4);
    std::cout << "queue.Enqueue(4): " << queue << std::endl;

    while(!queue.IsEmpty())
    {
        queue.Dequeue();
        std::cout << "queue.Dequeue(): " << queue << std::endl;

    }

    return 0;
}
