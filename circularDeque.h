//
// Created by Joshua Yoon on 5/9/25.
//

#ifndef CIRCULARDEQUE_H
#define CIRCULARDEQUE_H

#include <iostream>

template <typename T>
class circularDeque {
private:
    T* array;
    int capacity;
    int front;


public:
    circularDeque(int capacity);
    ~circularDeque();
    int size;

    bool isEmpty() const;
    void insertFront(T value);
    void insertBack(T value);
    void popFront();
    void popBack();
    T getFront() const;
    T getBack() const;
    void print() const;
};

// Implementation

template <typename T>
circularDeque<T>::circularDeque(int capacity)
    : capacity(capacity), front(0), size(0)
{
    array = new T[capacity];
}

template <typename T>
circularDeque<T>::~circularDeque() {
    delete[] array;
}

template <typename T>
bool circularDeque<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
void circularDeque<T>::insertFront(T value) {
    if (size == capacity) return;
    front = (front - 1 + capacity) % capacity;
    array[front] = value;
    size++;
}

template <typename T>
void circularDeque<T>::insertBack(T value) {
    if (size == capacity) return;
    int back = (front + size) % capacity;
    array[back] = value;
    size++;
}

template <typename T>
void circularDeque<T>::popFront() {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    front = (front + 1) % capacity;
    size--;
}

template <typename T>
void circularDeque<T>::popBack() {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    size--;
}

template <typename T>
T circularDeque<T>::getFront() const {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    return array[front];
}

template <typename T>
T circularDeque<T>::getBack() const {
    if (isEmpty()) throw std::runtime_error("Deque is empty");
    return array[(front + size - 1 + capacity) % capacity];
}

template <typename T>
void circularDeque<T>::print() const {
    for (int i = 0; i < size; ++i) {
        std::cout << array[(front + i) % capacity] << ' ';
    }
    std::cout << '\n';
}

#endif // CIRCULARDEQUE_H
