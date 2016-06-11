#ifndef QUEUE_ARR_H
#define QUEUE_ARR_H

class Queue
{
    public:
        Queue(size_t maxsize = 10); // maxsize must be > 0
        Queue(const Queue & queue);
        virtual ~Queue();
        Queue & operator=(Queue other);
        friend std::ostream & operator<<(std::ostream & out, const Queue & queue);

        bool IsEmpty() const;
        bool IsFull() const;
        void Dequeue();
        void Enqueue(int value);

        int & Front();
        const int & Front() const;
        
    protected:
        int * data;
        size_t max_size;
        int front; // array index for front element
        size_t count; // number of elements

    private:
        void swap(Queue &other);
        void Grow();
        virtual void Print(std::ostream &out) const;
};

#endif
