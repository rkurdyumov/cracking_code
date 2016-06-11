#include <iostream>
#include <assert.h>
#include "queue.h"

Queue::Queue(const Queue &queue) : Queue()
{
    for (const Node *n = queue.Begin(); n != queue.End(); n = n->next)
        Enqueue(n->data);
}

Queue::~Queue()
{
    while (!IsEmpty())
        Dequeue();
}

void Queue::swap(Queue &other)
{
    std::swap(front, other.front);
    std::swap(back, other.back);
}

// Use copy-and-swap idiom
Queue & Queue::operator=(Queue other)
{
    // Make deep local copy of other, swap contents, destroy old data
    swap(other);
    return *this;
}

std::ostream & operator<<(std::ostream &out, const Queue &queue)
{
    queue.Print(out);
    return out;
}

bool Queue::IsEmpty() const
{
    return front == nullptr;
}

void Queue::Dequeue()
{
    assert(!IsEmpty());
    Node *old_front = front;
    front = front->next;
    delete old_front;
    if (IsEmpty())
        back = nullptr;
}

void Queue::Enqueue(int value)
{
    Node *new_node = new Node;
    new_node->data = value;
    new_node->next = nullptr;
    if (IsEmpty())
        front = new_node;
    else
        back->next = new_node;
    back = new_node;
}

int & Queue::Front()
{
    assert(!IsEmpty());
    return front->data;
}

const int & Queue::Front() const
{
    assert(!IsEmpty());
    return front->data;
}

Queue::Node * Queue::Begin() { return front; }

Queue::Node * Queue::End() { return nullptr; }

const Queue::Node * Queue::Begin() const { return front; }

const Queue::Node * Queue::End() const { return nullptr; }

void Queue::Print(std::ostream &out) const
{
    out << "front-->";
    for (const Node *n = Begin(); n != End(); n = n->next)
        out << n->data << "-->";
    out << "back";
}
