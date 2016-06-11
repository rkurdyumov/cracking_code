#include <iostream>
#include <assert.h>
#include "queue_arr.h"

Queue::Queue(size_t maxsize): max_size(maxsize), front(-1), count(0)
{
    assert(max_size > 0);
    data = new int[max_size];
}

Queue::Queue(const Queue & queue) 
{
    data = new int[queue.max_size];
    front = queue.front;
    count = queue.count;
    max_size = queue.max_size;
    for (size_t i = 0; i < count; ++i)
    {
        int index = (front + i)%max_size;
        data[index] = queue.data[index]; 
    }        
}

Queue::~Queue()
{
    delete[] data;
}

void Queue::swap(Queue & other)
{
    std::swap(data, other.data);
    std::swap(max_size, other.max_size);
    std::swap(front, other.front);
    std::swap(count, other.count);
}

// Use copy-and-swap idiom
Queue & Queue::operator=(Queue other)
{
    // Make deep local copy of other, swap contents, destroy old data
    swap(other);
    return *this;
}

std::ostream & operator<<(std::ostream & out, const Queue & queue)
{
    queue.Print(out);
    return out;
}

bool Queue::IsEmpty() const
{
    return count == 0;
}

bool Queue::IsFull() const
{
    return count == max_size;
}

void Queue::Dequeue()
{
    assert(!IsEmpty());
    --count;
    ++front;
    front %= max_size;
    if (IsEmpty())
        front = -1;
}

void Queue::Enqueue(int value)
{
    if (IsFull())
        Grow();
    if (IsEmpty())
        front = 0;
    data[(front+count)%max_size] = value;
    count++;
}

int & Queue::Front()
{
    assert(!IsEmpty());
    return data[front];
}

const int & Queue::Front() const
{
    assert(!IsEmpty());
    return data[front];
}

void Queue::Grow()
{
    size_t old_max_size = max_size;
    max_size *= 2;
    int * new_data = new int[max_size];
    for (size_t i = 0; i < count; ++i)
    {
        int index = (front + i)%old_max_size;
        new_data[index] = data[index]; 
    }
    delete[] data;
    data = new_data;
}

void Queue::Print(std::ostream & out) const
{
    out << "front-->";
    for (size_t i = 0; i < count; ++i)
    {
        int index = (front + i)%max_size;
        out << data[index] << "-->";
    }
    out << "back";
}



