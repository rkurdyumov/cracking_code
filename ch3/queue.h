#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
    public:
        struct Node {
            int data;
            Node *next = nullptr;
        };

        Queue();
        Queue(const Queue &queue);
        ~Queue();
        Queue & operator=(Queue other);
        friend std::ostream & operator<<(std::ostream &out, const Queue &queue);

        bool IsEmpty() const;
        void Dequeue();
        void Enqueue(int value);

        int & Front();
        const int & Front() const;
        
    protected:
        Node *front;
        Node *back;

    private:
        Node * Begin();
        Node * End();
        const Node * Begin() const;
        const Node * End() const;
        void swap(Queue &other);
        virtual void Print(std::ostream &out) const;
};

#endif
