#ifndef STACK_H
#define STACK_H

class Stack
{
    public:
        struct Node {
            int data;
            Node *next = nullptr;
        };

        Stack();
        Stack(const Stack &stack);
        ~Stack();
        Stack & operator=(Stack other);
        friend std::ostream & operator<<(std::ostream &out, const Stack &stack);

        bool IsEmpty() const;
        void Pop();
        void Push(int data);

        int & Top();
        const int & Top() const;
        
    protected:
        Node *top;

    private:
        Node * Begin();
        Node * End();
        const Node * Begin() const;
        const Node * End() const;
        void swap(Stack &other);
        void Reverse();
        virtual void Print(std::ostream &out) const;
};

#endif
