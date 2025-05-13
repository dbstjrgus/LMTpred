//
// Created by Joshua Yoon on 5/9/25.
//

#ifndef CIRCULARDEQUE_H
#define CIRCULARDEQUE_H

#include <iostream>
template <typename T> class circularDeque {
private:
    T* array;
    int  capacity, front;
public:
    int size;
    circularDeque(int capacity);
    bool isEmpty() const;
    void insertFront(T value);
    void insertBack(T value);
    void popFront();
    void popBack();
    T getFront();
    T getBack();
    void print();
};

#define TEMP template <typename T>
#define CLASS circularDeque<T>



TEMP
CLASS::circularDeque(int capacity) : size(0), front(0), array(new T[capacity]), capacity(capacity) {} // ok apperently this calls the constructor of T

TEMP
bool CLASS::isEmpty() const {return size == 0;}

TEMP
void CLASS::insertFront(T value) {
    if (size == capacity) {
        return;
    }
    front = (front - 1 + capacity) % capacity;
    array[front] = value;
    size++;
}

TEMP
void CLASS::insertBack(T value) {
    if (size == capacity) {
        return;
    }
    int back = (front + size) % capacity;
    array[back] = value;
    size++;
}

TEMP
void CLASS::popBack() {
    if (size == 0) { throw std::runtime_error("deque is empty"); }
    size--;
    int back = (front + size -1 ) % capacity;
    std::cout << array[back] << std::endl;
}

TEMP
void CLASS::popFront() {
    if (size == 0) { throw std::runtime_error("deque is empty"); }
    T val = array[front];
    front = (front + 1) % capacity;
    size--;
    std::cout << val << std::endl;
}

TEMP
T CLASS::getBack() {
    return array[(front+size-1) % capacity];
}

TEMP
T CLASS::getFront() {
    return array[front];
}

TEMP
void CLASS::print() {
    for (int i = 0; i < size; ++i) {
        std::cout << array[(front + i) % capacity] << " ";
    }
    std::cout << std::endl;
}

#endif //CIRCULARDEQUE_H
