#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
    public:
        Queue(int maxsize = 10);
        Queue(const Queue &queue);
        ~Queue();
        Queue & operator=(Queue other);
        friend std::ostream & operator<<(std::ostream &out, const Queue &queue);

        bool IsEmpty() const;
        bool IsFull() const;
        void Dequeue();
        void Enqueue(int value);

        int & Front();
        const int & Front() const;
        
    protected:
        int *data;
        int max_size;
        int front; // array index for front element
        int count; // number of elements

    private:
        void swap(Queue &other);
        void Grow();
        virtual void Print(std::ostream &out) const;
};

#endif
