#ifndef LINKED_LIST_H
#define LINKED_LIST_H


class LinkedList
{
    public:
        struct Node
        {   
            int data;
            Node *next = nullptr;
        };

        LinkedList();
        LinkedList(const LinkedList &list);
        virtual ~LinkedList(); // in case we destroy polymorphic object
        LinkedList & operator=(LinkedList other);
        LinkedList & operator+=(const LinkedList &rhs);
        friend LinkedList operator+(const LinkedList &lhs, const LinkedList &rhs);
        friend std::ostream& operator<< (std::ostream &out, const LinkedList &list);

        bool IsEmpty() const;
        void Append(int value);    // add to end
        void PushFront(int value); // add to beginning
        void PopFront();           // remove first element
        void InsertAfter(Node *n, int data);
        void DeleteAfter(Node *n);
        void Reverse();
        
        int & Front();
        const int & Front() const;
        Node * Begin();
        Node * End();
        const Node * Begin() const;
        const Node * End() const;

    protected:       
        // Protected so that derived class can modify these directly
        Node *head;
        Node *tail; // allows O(1) append

    private:
        void swap(LinkedList &other);
        virtual void Print(std::ostream &out) const; // allow different derived Prints
};

#endif
