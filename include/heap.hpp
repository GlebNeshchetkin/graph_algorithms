#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <functional>
#include <stdexcept>

template<typename T, typename Compare = std::less<T>>
class Heap {
private:
    std::vector<T> data;
    Compare comp;

    void siftUp(size_t i) {
        while (i > 0) {
            size_t parent = (i - 1) / 2;

            if (!comp(data[i], data[parent]))
                break;

            std::swap(data[i], data[parent]);
            i = parent;
        }
    }

    void siftDown(size_t i) {
        size_t n = data.size();

        while (true) {
            size_t left = 2 * i + 1;
            size_t right = 2 * i + 2;
            size_t best = i;

            if (left < n && comp(data[left], data[best]))
                best = left;

            if (right < n && comp(data[right], data[best]))
                best = right;

            if (best == i)
                break;

            std::swap(data[i], data[best]);
            i = best;
        }
    }

public:
    Heap() = default;

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }

    const T& top() const {
        if (data.empty())
            throw std::out_of_range("Heap is empty");
        return data.front();
    }

    void push(const T& value) {
        data.push_back(value);
        siftUp(data.size() - 1);
    }

    void pop() {
        if (data.empty())
            return;

        data.front() = data.back();
        data.pop_back();

        if (!data.empty())
            siftDown(0);
    }

    void clear() {
        data.clear();
    }
};

#endif