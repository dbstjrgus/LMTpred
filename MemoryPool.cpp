//
// Created by Joshua Yoon on 5/13/25.
//

#include <stack>
#include <stdexcept>
#include <vector>

#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include <vector>
#include <stack>
#include <stdexcept>

template <typename T>
class MemoryPool {
private:
    std::vector<T*> blocks; // Stores single-element blocks
    std::vector<T*> array_blocks; // Stores array blocks
    std::stack<T*> freeList;
    size_t blockSize;

public:
    MemoryPool(size_t initialSize) : blockSize(initialSize) {
        allocateBlock(blockSize);
    }

    ~MemoryPool() {
        for (T* block : blocks) {
            delete[] block;
        }
        for (T* block : array_blocks) {
            ::operator delete(block);
        }
    }

    // Allocate a single T (for future use, not used by deque)
    T* allocate(size_t count = 1) {
        if (count != 1) {
            throw std::bad_alloc();
        }
        if (freeList.empty()) {
            allocateBlock(blockSize * 2);
        }
        T* ptr = freeList.top();
        freeList.pop();
        return ptr; // Note: No construction here; caller must construct
    }

    // Deallocate a single T
    void deallocate(T* ptr, size_t count = 1) {
        if (count != 1) {
            throw std::invalid_argument("Single deallocate expects count=1");
        }
        ptr->~T();
        freeList.push(ptr);
    }

    // Allocate an array of T (for deque)
    T* allocateArray(size_t count) {
        T* block = static_cast<T*>(::operator new(sizeof(T) * count));
        array_blocks.push_back(block);
        return block; // Raw memory, no construction
    }

    // Deallocate an array of T
    void deallocateArray(T* ptr, size_t count) {
        for (auto it = array_blocks.begin(); it != array_blocks.end(); ++it) {
            if (*it == ptr) {
                ::operator delete(ptr);
                array_blocks.erase(it);
                return;
            }
        }
        throw std::invalid_argument("Pointer not found in array_blocks");
    }

    void constructAt(T* ptr, const T& value) {
        new (ptr) T(value);
    }

    void destroyAt(T* ptr) {
        ptr->~T();
    }

private:
    void allocateBlock(size_t size) {
        T* newBlock = new T[size];
        blocks.push_back(newBlock);
        for (size_t i = 0; i < size; ++i) {
            freeList.push(&newBlock[i]);
        }
        blockSize = size;
    }
};

#endif // MEMORYPOOL_H
