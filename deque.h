#include <iostream>
//
// Created by apple on 3/10/21.
//

#ifndef SWEATYDEQUE_DEQUE_H
#define SWEATYDEQUE_DEQUE_H

#include <iostream>
#include <iterator>
#include <vector>
#include <initializer_list>

class Iterator;

class Deque {
private:
    class Chunk {
    public:
        int* arr;

        Chunk() {
          arr = new int[SIZEOFBLOCK];
        }
        ~Chunk() {
          delete[] arr;
        }
    };
    const static int SIZEOFBLOCK = 2;
    int beginBlock;
    int endBlock;
    int begin_;
    int end_;
    size_t size;
    size_t capacity;
    size_t numOfBlocks;
    Chunk** ptrsToBlocks;
    void emptyBlocks();
    void changeLength();

public:
    class Iterator : std::iterator<std::random_access_iterator_tag, int> {
    private:
        Deque* dequePointer;
        int index;
    public:
        Iterator() {
          dequePointer = nullptr;
        }
        Iterator(Deque* deque_pointer, int index) {
          this -> dequePointer = deque_pointer;
          this -> index = index;
        }
        int operator*() {
          int x = (*dequePointer)[index];
          return x;
        }
        bool operator==(const Iterator& other) const {
          return this -> index == other.index;
        }
        bool operator!=(const Iterator& other) const {
          return !(this -> index == other.index);
        }
        bool operator<(const Iterator& other) const {
          return this -> index < other.index;
        }
        bool operator>(const Iterator& other) const {
          return this -> index > other.index;
        }
        bool operator<=(const Iterator& other) const {
          return this -> index <= other.index;
        }
        bool operator>=(const Iterator& other) const {
          return this -> index >= other.index;
        }
        Iterator& operator--(int) {
          auto old = new Iterator(dequePointer, index);
          index++;
          return *old;
        }
        Iterator& operator--() {
          index--;
          return *this;
        }
        Iterator& operator++() {
          index++;
          return *this;
        }
        Iterator& operator++(int) {
          auto old = new Iterator(dequePointer, index);
          index++;
          return *old;
        }
        Iterator& operator+=(int x) {
          index += x;
          return *this;
        }
        Iterator& operator-=(int x) {
          index -= x;
          return *this;
        }
        Iterator& operator-(int x) {
          auto iterator = new Iterator(dequePointer, index);
          iterator -> index -= x;
          return *iterator;
        }
        Iterator& operator+(int x) {
          auto iterator = new Iterator(dequePointer, index);
          iterator -> index += x;
          return *iterator;
        }
        Iterator& operator=(Iterator& x) {
          this -> dequePointer = x.dequePointer;
          this -> index = x.index;
          return *this;
        }
        void swap(Iterator& x, Iterator& y) {
          std::swap(x.dequePointer, y.dequePointer);
          std::swap(x.index, y.index);
        }
        int operator-(Iterator& x) {
          auto y = *this;
          int answer = 0;
          if (x > y) swap(x, y);
          while (x != y) {
            x++;
            answer++;
          }
          return answer;
        }
    };

    Deque();
    Deque(size_t size);
    Deque(const std::initializer_list<int> &list);
    ~Deque();

    Deque(const Deque& other);
    Deque& operator =(const Deque& other);
    int& operator[](int index) {
      if (begin_ + index < SIZEOFBLOCK) {
        return (*ptrsToBlocks[beginBlock]).arr[begin_ + index];
      }
      int k = SIZEOFBLOCK - begin_;
      index -= k;
      int curr = beginBlock + (index + SIZEOFBLOCK) / SIZEOFBLOCK;
      index -= index / SIZEOFBLOCK * SIZEOFBLOCK;
      if (curr >= numOfBlocks) {
        curr -= numOfBlocks;
      }
      return (*ptrsToBlocks[curr]).arr[index];
    }

    void resize(int new_size);

    void push_back(int value);

    void pop_back();

    void push_front(int value);

    void pop_front();

    void clear();
    bool empty();
    int length();
    Iterator begin() {
      return Iterator(this, 0);
    }
    Iterator end() {
      return Iterator(this, size);
    }
};

#endif //SWEATYDEQUE_DEQUE_H
