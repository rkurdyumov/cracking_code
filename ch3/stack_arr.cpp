#include <iostream>
#include <assert.h>
#include "stack_arr.h"

Stack::Stack(int maxsize): max_size(maxsize), top(-1)
{
    data = new int[max_size];
}

Stack::Stack(const Stack &stack)
{
    data = new int[stack.max_size];
    for (int i = 0; i <= stack.top; ++i)
        data[i] = stack.data[i];
    top = stack.top;
    max_size = stack.max_size;
}

Stack::~Stack()
{
    delete[] data;
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
    return top == -1;
}

bool Stack::IsFull() const
{
    return top == max_size - 1;
}

void Stack::Pop()
{
    assert(!IsEmpty());
    --top;
}

void Stack::Push(int value)
{
    if (IsFull())
        Grow();
    data[++top] = value;
}

int & Stack::Top()
{
    assert(!IsEmpty());
    return data[top];
}

const int & Stack::Top() const
{
    assert(!IsEmpty());
    return data[top];
}

void Stack::Grow()
{
    max_size *= 2;
    int *new_data = new(std::nothrow) int[max_size];
    assert(new_data != nullptr);
    for (int i = 0; i <= top; ++i)
        new_data[i] = data[i]; // slow but simple
    delete[] data;
    data = new_data;
}

void Stack::Print(std::ostream &out) const
{
    out << "top-->";
    for (int i = 0; i <= top; ++i)
        out << data[i] << "-->";
    out << "bottom";
}



