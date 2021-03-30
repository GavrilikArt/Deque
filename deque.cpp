//
// Created by apple on 3/22/21.
//

#include "deque.h"

void Deque::emptyBlocks() {
  for (int i = 0; i < numOfBlocks; i++) {
    delete ptrsToBlocks[i];
  }
  delete [] ptrsToBlocks;
}

void Deque::changeLength() {
  this -> capacity = size / SIZEOFBLOCK * SIZEOFBLOCK * 2;
  size_t old_total_blocks = numOfBlocks;
  this -> numOfBlocks = capacity / SIZEOFBLOCK;
  Chunk** new_block_ptrs = new Chunk*[numOfBlocks];

  int index = 0;
  while (beginBlock != endBlock) {
    new_block_ptrs[index] = ptrsToBlocks[beginBlock];
    beginBlock++;
    if (beginBlock == old_total_blocks) {
      beginBlock = 0;
    }
    index++;
  }
  new_block_ptrs[index] = ptrsToBlocks[beginBlock];
  beginBlock = 0;
  endBlock = index;
  index++;
  delete[] ptrsToBlocks;
  while (index != numOfBlocks) {
    new_block_ptrs[index] = new Chunk();
    index++;
  }

  ptrsToBlocks = new_block_ptrs;
}

Deque::Deque() {
  this -> size = 0;
  this -> capacity = SIZEOFBLOCK * 4;
  this -> ptrsToBlocks = new Chunk*[4];
  this -> numOfBlocks = 4;
  for (int i = 0; i < numOfBlocks; i++) {
    ptrsToBlocks[i] = new Chunk();
  }

  this -> beginBlock  = 0;
  this -> endBlock  = 0;
  this -> begin_ = 0;
  this -> end_ = 0;
}

Deque::Deque(size_t size) {
  int number_of_blocks = size / SIZEOFBLOCK + 4;
  this -> size = 0;
  this -> capacity = number_of_blocks * SIZEOFBLOCK;
  this -> ptrsToBlocks = new Chunk*[number_of_blocks];
  this -> numOfBlocks = number_of_blocks;

  for (int i = 0; i < number_of_blocks; i++) {
    ptrsToBlocks[i] = new Chunk();
  }

  for (int i = 0; i < size; i++) {
    push_back(0);
  }
}

Deque::Deque(const std::initializer_list<int> &list) : Deque() {
  for (auto &current : list) {
    push_back(current);
  }
}

Deque::~Deque() {
  emptyBlocks();
}

Deque::Deque(const Deque &other) {
  this -> size = other.size;
  this -> capacity = other.capacity;

  this -> beginBlock = other.beginBlock;
  this -> endBlock = other.endBlock;
  this -> begin_ = other.begin_;
  this -> end_ = other.end_;

  this -> numOfBlocks = other.numOfBlocks;
  this -> ptrsToBlocks = new Chunk*[numOfBlocks];
  for (int i = 0; i < numOfBlocks; i++) {
    ptrsToBlocks[i] = other.ptrsToBlocks[i];
  }
}

Deque &Deque::operator=(const Deque &other) {
  this -> size = other.size;
  this -> capacity = other.capacity;
  this -> beginBlock = other.beginBlock;
  this -> endBlock = other.endBlock;
  this -> begin_ = other.begin_;
  this -> end_ = other.end_;

  this -> numOfBlocks = other.numOfBlocks;
  this -> ptrsToBlocks = new Chunk*[numOfBlocks];
  for (int i = 0; i < numOfBlocks; i++) {
    ptrsToBlocks[i] = other.ptrsToBlocks[i];
  }
  return *this;
}

void Deque::resize(int new_size) {
  while (size < new_size) {
    if (size == capacity || (beginBlock == endBlock && size > SIZEOFBLOCK)) {
      changeLength();
    }
    push_back(0);
  }
  while (size > new_size) {
    if (numOfBlocks > 4 && size * 3 < capacity) {
      changeLength();
    }
    pop_back();
  }
}

void Deque::push_back(int value) {
  if (size + 1 == capacity) {
    changeLength();
  }
  int next_block = endBlock;
  int next_end = end_ + 1;
  if (next_end == SIZEOFBLOCK) {
    next_block++;
    next_end = 0;

    if (next_block == numOfBlocks) {
      next_block = 0;
    }
    if (next_block == beginBlock) {
      changeLength();
      next_block = endBlock + 1;
    }
  }

  (*ptrsToBlocks[endBlock]).array[end_] = value;
  endBlock = next_block;
  end_ = next_end;
  size++;
}

void Deque::pop_back() {
  if (this -> size == 0) {
    std::cout << "Non-existent index\n";
  }
  else {
    size--;
    end_--;
    if (end_ == -1) {
      endBlock--;
      if (endBlock == -1) {
        endBlock = numOfBlocks;
        end_ = SIZEOFBLOCK - 1;
      }
    }
    if (numOfBlocks > 4 && size * 3 < capacity) {
      changeLength();
    }
  }
}

void Deque::push_front(int value) {
  if (size + 1 == capacity) {
    changeLength();
  }
  if (begin_ == 0) {
    int prev_block = beginBlock;
    prev_block--;
    if (prev_block == -1) {
      prev_block = numOfBlocks - 1;
    }
    if (prev_block == endBlock) {
      changeLength();
      prev_block = numOfBlocks - 1;
    }
    beginBlock = prev_block;
    begin_ = SIZEOFBLOCK - 1;
  } else {
    begin_--;
  }
  (*ptrsToBlocks[beginBlock]).array[begin_] = value;
  size++;
}

void Deque::pop_front() {
  if (this -> size == 0) {
    std::cout << "Non-existent index\n";
  }
  else {
    size--;
    begin_++;
    if (begin_ == SIZEOFBLOCK) {
      beginBlock++;
      if (beginBlock == numOfBlocks) {
        beginBlock = 0;
        begin_ = 0;
      }
    }
    if (numOfBlocks > 4 && size * 3 < capacity) {
      changeLength();
    }
  }
}

void Deque::clear() {
  emptyBlocks();
  Deque();
}

int Deque::length() {
  return this -> size;
}

bool Deque::empty() {
  return this -> size == 0 ? true : false;
}
