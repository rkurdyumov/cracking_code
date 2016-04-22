#include <iostream>
#include <assert.h>
#include "stack.h"

Stack::Stack(): top(nullptr)
{
}

Stack::Stack(const Stack &stack) : Stack()
{
    for (const Node *n = stack.Begin(); n != stack.End(); n = n->next)
        Push(n->data);
    Reverse(); // Pushing reverses initial list, so reverse it back
}

Stack::~Stack()
{
    while (!IsEmpty())
        Pop();
}

void Stack::swap(Stack &other)
{
    std::swap(top, other.top);
}

// Use copy-and-swap idiom
Stack & Stack::operator=(Stack other)
{
    // Make deep local copy of other, swap contents, destroy old data
    swap(other);
    return *this;
}

std::ostream & operator<<(std::ostream &out, const Stack &stack)
{
    stack.Print(out);
    return out;
}

bool Stack::IsEmpty() const
{
    return top == nullptr;
}

void Stack::Pop()
{
    assert(!IsEmpty());
    Node *old_top = top;
    top = top->next;
    delete old_top;
}

void Stack::Push(int data)
{
    Node *new_node = new Node;
    new_node->data = data;
    new_node->next = top;
    top = new_node;
}

int & Stack::Top()
{
    assert(!IsEmpty());
    return top->data;
}

const int & Stack::Top() const
{
    assert(!IsEmpty());
    return top->data;
}

Stack::Node * Stack::Begin() { return top; }

Stack::Node * Stack::End() { return nullptr; }

const Stack::Node * Stack::Begin() const { return top; }

const Stack::Node * Stack::End() const { return nullptr; }

void Stack::Reverse()
{
    Node *prev = nullptr;
    Node *curr = Begin();
    while (curr != End())
    {
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    top = prev;
}

void Stack::Print(std::ostream &out) const
{
    out << "top-->";
    for (const Node *n = Begin(); n != End(); n = n->next)
        out << n->data << "-->";
    out << "bottom";
}



