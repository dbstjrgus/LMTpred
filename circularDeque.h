//
// Created by Joshua Yoon on 5/9/25.
//

#ifndef CIRCULARDEQUE_H
#define CIRCULARDEQUE_H

#include <iostream>

template <typename T>
/**
 * @class circularDeque
 * @brief A data structure representing a circular double-ended queue (deque).
 *
 * The circularDeque class implements a deque of fixed capacity where elements can
 * be added or removed from both the front and the rear ends in constant time.
 * It uses a circular buffer to efficiently handle wrapping around the buffer
 * when the end of the underlying array is reached.
 *
 * This data structure is useful in scenarios where a fixed-size queue is required,
 * and where operations at both ends are frequent and must be efficient.
 */
class circularDeque {
    /**
     * @brief Pointer to the array used for internal storage of elements within the circular deque.
     *
     * This dynamically allocated array serves as the underlying storage container
     * for the circular deque. The array operates based on circular indexing,
     * enabling efficient insert and removal operations at both the front and back of the deque.
     *
     * @note The size of the array is determined by the `capacity` variable.
     *       Memory for this array is allocated in the constructor and released in the destructor.
     */
private:
    T* array;
    /**
     * @brief Retrieves the maximum number of elements that a container can hold.
     *
     * This function provides information about the storage capacity of a container.
     * The capacity depends on the implementation and may vary for different types
     * of containers or different instances of the same container type.
     *
     * @return size_t The maximum number of elements the container can hold
     *                before needing to reallocate memory.
     */
    int capacity;
    /**
     * @brief Represents the front element in a data structure, such as a queue or deque.
     *
     * The `front` variable is used to access or reference the first element
     * of the data structure without removing it. Its exact definition and
     * functionality can vary depending on the context and the type of
     * data structure implemented.
     *
     * Typical use cases for this variable include retrieving the first
     * element for processing in FIFO (First-In-First-Out) data structures
     * or as a reference in iterators.
     */
    int front;

    /**
     * Represents the current number of elements in the circular deque.
     *
     * This variable tracks how many elements are currently stored in the
     * circular deque. It is incremented when an element is successfully
     * added to the deque and decremented when an element is removed.
     */
public:
    int size;

    /**
     * @class CircularDeque
     *
     * @brief A class that implements a circular deque (double-ended queue) with fixed capacity.
     *
     * This data structure allows insertion and deletion of elements from both
     * the front and rear of the deque in constant time. It operates in a circular
     * manner to utilize space efficiently.
     *
     * @tparam T The type of elements stored in the deque.
     */
    circularDeque(int capacity);

    /**
     * @brief Reverses the given string in place.
     *
     * This method takes a reference to a std::string and reverses
     * the order of its characters. The operation modifies the
     * input string directly and does not allocate additional memory
     * for the reversed string.
     *
     * @param str The string to be reversed.
     *
     * @note This function assumes the input string is encoded
     *       in a compatible format. Behavior is undefined for
     *       non-trivial encodings where a character may consist of
     *       multiple code units, such as variable-length encodings.
     */
    ~circularDeque();

    /**
     * Checks if the circular deque is empty.
     *
     * @return true if the deque is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * Inserts an element at the front of the circular deque.
     *
     * @param value The value to be inserted at the front of the deque.
     */
    void insertFront(T value);

    /**
     * Inserts an element at the back of the circular deque.
     * If the deque is at maximum capacity, the operation is ignored.
     *
     * @param value The element of type T to be inserted at the back of the deque.
     */
    void insertBack(T value);

    /**
     * Removes and returns the front element of a collection, if one exists.
     *
     * This method typically operates on collections such as lists, queues, or other
     * data structures that support a front element or a specific order.
     *
     * It should handle cases where the collection is empty by either returning
     * a default value or throwing an appropriate exception, depending on the implementation.
     *
     * @throws NoSuchElementException if the collection is empty and removal is not possible.
     * @return the element that was removed from the front of the collection.
     */
    void popFront();

    /**
     * Removes the last element from the container, effectively reducing the
     * size of the container by one.
     *
     * If the container is empty, the behavior is undefined.
     *
     * This function provides constant time complexity.
     */
    void popBack();

    /**
     * Retrieves the front element of a collection such as a queue or list without removing it.
     *
     * @return The front element of the collection.
     */
    T getFront() const;

    /**
     * Retrieves the element from the back of the deque without removing it.
     *
     * @return The element at the back of the deque.
     * @throws std::runtime_error if the deque is empty.
     */
    T getBack() const;

    /**
     * @brief Prints all elements of the circular deque in order from the front to the back.
     *
     * This method iterates through the elements of the circular deque, starting from the front,
     * and outputs them sequentially to the standard output stream. The order is maintained
     * by using modular arithmetic to account for wraparound in the deque's circular structure.
     *
     * The elements are separated by a space, and the output ends with a newline character.
     *
     * This operation has a time complexity of O(n), where n is the number of elements in the deque.
     *
     * @note The method assumes the deque is non-empty. If used on an empty deque, results may be undefined.
     */
    void print() const;
};

template <typename T>
/**
 * Creates a circular deque data structure that can perform operations
 * such as inserting, deleting, and accessing elements in a circular manner.
 *
 * @param capacity The maximum number of elements the circular deque can hold.
 * @return An instance of a circular deque with the specified capacity.
 */
circularDeque<T>::circularDeque(int capacity) : size(0), front(0), capacity(capacity) {
    array = new T[capacity]; // ✅ FIXED
}

template <typename T>
/**
 * @class MyClass
 * @brief A class that demonstrates a sample functionality.
 *
 * This class provides methods to perform basic operations
 * such as setting and retrieving a value.
 */
circularDeque<T>::~circularDeque() {
    delete[] array; // ✅ FIXED
}

template <typename T>
/**
 * Checks if the object is empty. The definition of "empty" depends on the
 * specific object's implementation and context. For collections or strings,
 * it usually means having no elements or characters.
 *
 * @return true if the object is empty, false otherwise.
 */
bool circularDeque<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
/**
 * Inserts an element at the front of a collection, such as a linked list or deque.
 *
 * @param element The element to be added to the front of the collection.
 */
void circularDeque<T>::insertFront(T value) {
    if (size == capacity) return;
    front = (front - 1 + capacity) % capacity;
    array[front] = value;
    size++;
}

template <typename T>
/**
 * Inserts the given value at the back of the circular deque.
 * If the deque is already full (size == capacity), the operation will not be performed.
 *
 * @param value The value to be inserted at the back of the deque.
 */
void circularDeque<T>::insertBack(T value) {
    if (size == capacity) return;
    int back = (front + size) % capacity;
    array[back] = value;
    size++;
}

template <typename T>
/**
 * @brief Removes the element at the front of the deque.
 *
 * Adjusts the front index to point to the next element in the circular buffer,
 * and decreases the size of the deque. If the deque is empty, an exception
 * is thrown.
 *
 * @throws std::runtime_error if the deque is empty.
 */
void circularDeque<T>::popFront() {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    front = (front + 1) % capacity;
    size--;
}

template <typename T>
/**
 * @brief Removes the last element from the container.
 *
 * This method decreases the size of the container by one, effectively
 * removing the last element. It does not return the removed element.
 *
 * @throw std::out_of_range Throws an exception if the container is empty
 *        and there is no element to pop.
 *
 * @note The method invalidates any references, pointers, or iterators pointing
 *       to the last element of the container.
 */
void circularDeque<T>::popBack() {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    size--;
}

template <typename T>
/**
 * Retrieves the front element of a collection or data structure without removing it.
 *
 * @return The front element of the collection or data structure.
 */
T circularDeque<T>::getFront() const {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    return array[front];
}

template <typename T>
/**
 * Retrieves a reference or copy to the last element in a container or data structure.
 *
 * This method provides access to the last element of a container. The behavior may vary depending on
 * the container type, such as returning a reference for modifiable containers or a copy for immutable ones.
 * If the container is empty, the behavior is typically undefined, and it may throw an exception or result in an error.
 *
 * @return The last element of the container or data structure.
 */
T circularDeque<T>::getBack() const {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    return array[(front + size - 1 + capacity) % capacity];
}

template <typename T>
/**
 * Prints the specified message to the standard output stream.
 *
 * This function takes a single string as input and writes
 * it to the standard output, typically the console. It is
 * intended for sending user-facing messages or debug information.
 *
 * @param message The string to be printed. Should not be null.
 *                A valid string must be provided.
 */
void circularDeque<T>::print() const {
    for (int i = 0; i < size; ++i) {
        std::cout << array[(front + i) % capacity] << ' ';
    }
    std::cout << '\n';
}

#endif // CIRCULARDEQUE_H
