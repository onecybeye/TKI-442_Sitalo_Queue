#include "pch.h"
#include "Queue.h"
#include <iostream>

namespace queue {

    // Конструктор с заданием начального размера
    Queue::Queue(int initialCapacity)
        : capacity(initialCapacity), frontIndex(0), rearIndex(-1), size(0) {
        data = new int[capacity];
    }

    // Деструктор для освобождения памяти
    Queue::~Queue() {
        delete[] data;
    }

    // Добавление элемента в конец очереди
    void Queue::enqueue(int value) {
        if (size == capacity) {
            resize(2 * capacity); // Удваиваем размер, если массив заполнен
        }
        rearIndex = (rearIndex + 1) % capacity;
        data[rearIndex] = value;
        size++;
    }

    // Извлечение элемента из начала очереди
    int Queue::dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Очередь пуста! Невозможно извлечь элемент.");
        }
        int value = data[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        size--;
        return value;
    }

    // Получение элемента из начала очереди без удаления
    int Queue::front() const {
        if (isEmpty()) {
            throw std::runtime_error("Очередь пуста! Невозможно получить элемент.");
        }
        return data[frontIndex];
    }

    // Проверка на пустоту очереди
    bool Queue::isEmpty() const {
        return size == 0;
    }

    // Получение текущего размера очереди
    int Queue::getSize() const {
        return size;
    }

    // Изменение размера массива
    void Queue::resize(int newCapacity) {
        int* newData = new int[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[(frontIndex + i) % capacity];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
        frontIndex = 0;
        rearIndex = size - 1;
    }

    // Перегрузка оператора << для вывода состояния очереди
    std::ostream& operator<<(std::ostream& os, const Queue& q) {
        for (int i = 0; i < q.size; ++i) {
            os << q.data[(q.frontIndex + i) % q.capacity];
            if (i != q.size - 1) {
                os << " ";
            }
        }
        return os;
    }
}
