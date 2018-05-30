#ifndef STACK_H
#define STACK_H

class Stack
{
    public:
        Stack(int maxsize = 10);
        Stack(const Stack &stack);
        ~Stack();
        Stack & operator=(Stack other);
        friend std::ostream & operator<<(std::ostream &out, const Stack &stack);

        bool IsEmpty() const;
        bool IsFull() const;
        void Pop();
        void Push(int value);

        int & Top();
        const int & Top() const;

    protected:
        int *data;
        int max_size;
        int top; // array index for top element

    private:
        void swap(Stack &other);
        void Grow();
        virtual void Print(std::ostream &out) const;
};

#endif
