#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class Heap
{
public:
    Heap() {}

    void push(T value)
    {
        heap.push_back(value);
        percolate_up(heap.size() - 1);
    }

    T top() const
    {
        return heap.front();
    }
    bool empty()
    {
        return heap.empty();
    }

    void pop()
    {
        std::pop_heap(heap.begin(), heap.end());
        heap.pop_back();
    }

    void increase_key(size_t index, T new_value)
    {
        if (index >= heap.size())
        {
            return; // Index out of range
        }

        if (new_value < heap[index])
        {
            return; // New value is smaller than current value
        }

        heap[index] = new_value;
        percolate_up(index);
    }

private:
    std::vector<T> heap;

    void percolate_up(size_t index)
    {
        while (index > 0)
        {
            size_t parent = (index - 1) / 2;
            if (heap[index] <= heap[parent])
            {
                break; // Heap property is satisfied
            }
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
    }
};

int main()
{
    Heap<int> heap;
    heap.push(1);
    heap.push(2);
    heap.push(3);
    heap.push(4);
    heap.push(5);

    heap.increase_key(2, 6);

    while (!heap.empty())
    {
        std::cout << heap.top() << std::endl;
        heap.pop();
    }

    return 0;
}