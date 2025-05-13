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
/**
 * @class MemoryPool
 * @brief A simple memory pool for efficient allocation and deallocation of objects.
 *
 * @tparam T The type of object the memory pool will allocate.
 */
class MemoryPool {
private:
    std::vector<T*> blocks; /**
     * @brief A container that holds pointers to allocated memory blocks.
     *
     * The `blocks` vector is used to store pointers to memory blocks that have
     * been allocated for use within the memory pool. Each element in the vector
     * is a pointer to a block of memory managed by the memory pool.
     *
     * - The memory blocks are dynamically allocated and added to this vector
     *   during the memory pool's operation.
     * - The destructor of the memory pool releases all allocated memory blocks
     *   stored in this vector to prevent memory leaks.
     * - This vector ensures that all allocated blocks have a central location
     *   for proper management and cleanup.
     */
    std::vector<T*> array_blocks; /**
     * A stack used to manage a list of preallocated memory chunks for reuse.
     *
     * The `freeList` stores pointers to individual memory blocks that have been
     * deallocated and are available for reuse. It is part of the memory pooling
     * mechanism to minimize dynamic memory allocation overhead by recycling
     * previously allocated memory. The memory blocks in `freeList` are manually
     * constructed and destructed, and no automatic initialization is performed.
     *
     * Key operations:
     * - Memory blocks are pushed onto the stack when deallocated.
     * - Memory blocks are popped from the stack when a new allocation is requested.
     *
     * This ensures efficient reuse of memory within the pool and helps
     * eliminate memory fragmentation while maintaining high performance.
     */
    /**
     *
     */
    std::stack<T*> freeList;
    /**
     * @brief Represents the size of memory blocks that are allocated by the MemoryPool.
     *
     * The `blockSize` variable defines the number of elements in a block allocated
     * by the `MemoryPool`. Its value can dynamically change during the lifespan
     * of the `MemoryPool`, particularly during block allocation when the size
     * may be adjusted to accommodate increasing memory requirements.
     *
     * The initial value of `blockSize` is set upon `MemoryPool` construction based
     * on the `initialSize` parameter.
     */
    size_t blockSize;

    /**
     * Constructs a MemoryPool object with an initial block size.
     * Allocates the memory block of the specified initial size and prepares it for use.
     *
     * @param initialSize The initial size of the memory block to allocate.
     *                    This determines the number of objects the pool can initially accommodate.
     * @return None. This is a constructor and does not return a value.
     */
public:
    MemoryPool(size_t initialSize) : blockSize(initialSize) {
        allocateBlock(blockSize);
    }

    /**
     * Destructor for the MemoryPool class.
     *
     * Cleans up all allocated memory managed by the memory pool to prevent memory leaks.
     * This includes:
     * - Deleting all blocks managed in the `blocks` vector, which were allocated using `new[]`.
     * - Deallocating all blocks managed in the `array_blocks` vector, which were allocated using `::operator new`.
     */
    ~MemoryPool() {
        for (T* block : blocks) {
            delete[] block;
        }
        for (T* block : array_blocks) {
            ::operator delete(block);
        }
    }

    /**
     * @param count The number of objects to allocate. Must be 1. Default value is 1.
     * @return A pointer to the allocated memory for type T.
     * @throws std::bad_alloc If the `count` parameter is not equal to 1.
     */
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

    /**
     * Deallocates a single instance of type T by invoking its destructor and
     * returning it to the memory pool.
     *
     * @param ptr A pointer to the instance of type T to deallocate.
     * @param count The number of instances to deallocate. Must be 1; otherwise,
     *        an exception of type std::invalid_argument is thrown.
     *
     * @throws std::invalid_argument if count is not 1.
     */
    void deallocate(T* ptr, size_t count = 1) {
        if (count != 1) {
            throw std::invalid_argument("Single deallocate expects count=1");
        }
        ptr->~T();
        freeList.push(ptr);
    }

    /**
     * Allocates an array of uninitialized memory capable of holding `count`
     * elements of type `T`. The memory is not initialized and no constructors
     * are called for the elements in the array.
     *
     * @param count The number of elements to allocate memory for.
     * @return A pointer to the allocated uninitialized memory block.
     */
    T* allocateArray(size_t count) {
        T* block = static_cast<T*>(::operator new(sizeof(T) * count));
        array_blocks.push_back(block);
        return block; // Raw memory, no construction
    }

    /**
     * Deallocates a previously allocated array of objects.
     *
     * The method searches for the pointer in the `array_blocks` vector. If found,
     * it deallocates the memory using the `::operator delete` and removes the
     * pointer from the vector. If the pointer is not found in the `array_blocks`,
     * an `std::invalid_argument` exception is thrown.
     *
     * @param ptr A pointer to the block of memory that was allocated for the array.
     * @param count The number of elements in the array. This parameter is not used
     *              in the method logic but is required for the method signature.
     * @throws std::invalid_argument If the pointer is not found in `array_blocks`.
     */
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

    /**
     * Constructs an object of type T at the specified memory address using the given value.
     *
     * @tparam T The type of the object to construct.
     * @param ptr A pointer to the memory location where the object should be constructed.
     * @param value A constant reference to the value used to construct the object.
     */
    void constructAt(T* ptr, const T& value) {
        new (ptr) T(value);
    }

    /**
     * Destroys the object of type T located at the specified memory location.
     *
     * @param ptr A pointer to the memory location where the object of type T
     *            has been constructed. It must be a valid pointer to a properly
     *            constructed object of type T.
     */
    void destroyAt(T* ptr) {
        ptr->~T();
    }

    /**
     * Allocates a block of memory containing elements of type T.
     * Adds the allocated block to the internal `blocks` container and
     * populates the `freeList` with pointers to the elements in the block.
     *
     * @param size The number of elements of type T to allocate within the block.
     */
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
