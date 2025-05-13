//
// Created by Joshua Yoon on 5/13/25.
//

#include <stack>
#include <stdexcept>
#include <vector>

template <typename T>
class MemoryPool {
private:
    std::vector<T*> blocks;
    std::stack<T*> freeList;
    size_t blockSize;
public:
    MemoryPool(size_t totalElements) : blockSize(totalElements) {
        T* block = new T[blockSize];
        blocks.push_back(block);
        for (size_t i=0; i< blockSize; i++) {
            freeList.push(&block[i]);
        }
    }

    T* allocate(size_t count) {
        if (freeList.size() < count)
            throw std::bad_alloc();

        T* start = freeList.top();
        for (size_t i = 0; i < count; ++i) {
            freeList.pop();
            new (start + i) T();  // placement-new
        }
        return start;
    }

    void deallocate(T* ptr, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            (ptr + i)->~T();  // call destructor
            freeList.push(ptr + i);
        }
    }

    ~MemoryPool() {
        for (T* block : blocks) {
            delete[] block;
        }
    }
};
