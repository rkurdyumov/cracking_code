#include <iostream>
#include <assert.h>
#include "linked_list.h"

LinkedList::LinkedList(const LinkedList &list): LinkedList() // call base constructor
{
    for (const Node *n = list.Begin(); n != list.End(); n = n->next)
        Append(n->data);
}

LinkedList::~LinkedList()
{
    while (!IsEmpty())
        PopFront();
}

void LinkedList::swap(LinkedList &other) 
{
    using std::swap;
    swap(head, other.head);
    swap(tail, other.tail);
}

// Operator '=': use copy-and-swap idiom
LinkedList & LinkedList::operator=(LinkedList other)
{
    // Compiler makes a deep local copy of other
    // Swap contents, destroy local other list with old data
    swap(other);
    return *this;
}

LinkedList & LinkedList::operator+=(const LinkedList &rhs)
{
    if (rhs.IsEmpty()) return *this;

    LinkedList addition(rhs); // make deep copy of passed in list
    if (IsEmpty())
        head = addition.head;
    else
        tail->next = addition.head;
    tail = addition.tail;
    
    // Destroy addition but not dynamic memory it points to
    addition.head = addition.tail = nullptr;
    
    return *this;
}

LinkedList operator+(const LinkedList &lhs, const LinkedList &rhs)
{
    LinkedList result(lhs); // make deep local copy 
    result += rhs;
    return result;
}

std::ostream& operator<<(std::ostream &out, const LinkedList &list)
{
    list.Print(out);
    return out;
}

bool LinkedList::IsEmpty() const
{
    return head == nullptr;
}

void LinkedList::Append(int data)
{
    Node * new_node = new(std::nothrow) Node;
    assert(new_node != nullptr);
    
    new_node->data = data;
    if (IsEmpty())
    { 
        head = tail = new_node;
        return;
    }
    tail->next = new_node;
    tail = new_node;
}

void LinkedList::PushFront(int data)
{
    Node * new_node = new(std::nothrow) Node;
    assert(new_node != nullptr);
    
    new_node->data = data;
    new_node->next = head;
    head = new_node;
    if (tail == nullptr)
        tail = head;
}

void LinkedList::PopFront()
{
    assert(!IsEmpty());
    Node * old_head = head;
    head = old_head->next;
    delete old_head;
}

void LinkedList::InsertAfter(Node * n, int data)
{
    assert(n != nullptr);
    if (n == tail)
    {
        Append(data);
        return;
    }

    Node * new_node = new(std::nothrow) Node;
    assert(new_node != nullptr);

    new_node->data = data;
    new_node->next = n->next;
    n->next = new_node;
}

void LinkedList::DeleteAfter(Node * n)
{
    assert(n != nullptr);
    if (n == tail) return;
    if (n->next == tail) tail = n;
    delete n->next;
}


void LinkedList::Reverse()
{
    tail = head;
    
    Node * prev = nullptr;
    Node * curr = head;
    while (curr != nullptr)
    {
        Node * next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

int & LinkedList::Front()
{
    assert(!IsEmpty());
    return head->data;
}

const int & LinkedList::Front() const
{
    assert(!IsEmpty());
    return head->data;
}

LinkedList::Node * LinkedList::Begin() { return head; }

LinkedList::Node * LinkedList::End() { return nullptr; }

const LinkedList::Node * LinkedList::Begin() const { return head; }

const LinkedList::Node * LinkedList::End() const {return nullptr; }

void LinkedList::Print(std::ostream & out) const
{
    for (const Node *n = Begin(); n != End(); n = n->next)
        out << n->data << "-->";
    out << "end";
}

