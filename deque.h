#include <iostream>
//
// Created by apple on 3/10/21.
//

#ifndef SWEATYDEQUE_DEQUE_H
#define SWEATYDEQUE_DEQUE_H

class Deque {
private:
    class Chunk {

    public:
        Chunk** first;
        Chunk** last;
        int* array;

        Chunk(Chunk& other) {
          first = other.first;
          last = other.last;
          array = other.array;
        }

        Chunk() {
          array = new int[BLOCK_SIZE];
          first = nullptr;
          last = nullptr;
        }
        ~Chunk() {
          delete[] array;
        }
        bool isFirst() {
          return last != nullptr;
        }
        bool isLast() {
          return first != nullptr;
        }
    };
    const static int BLOCK_SIZE = 2;
    int beginBlock;
    int endBlock;
    int begin_;
    int end_;
    Chunk** pointersToBlocks;
    size_t size;
    size_t capacity;
    size_t numOfBlocks
    ;
    void clear_blocks();
    void change_length();

public:
    class Iterator : std::iterator<std::random_access_iterator_tag, int> {
        friend Deque;
    private:
        Deque* deque;
        Chunk** pointer;
        int index_in_block;
    public:
        Iterator() {
          pointer = nullptr;
          index_in_block = 0;
          deque = nullptr;
        }
        // one:
        Iterator(Deque* deque, Chunk* value, int index_in_block)
        {
          this -> deque = deque;
          this -> pointer = &value;
          this -> index_in_block = index_in_block;
        }

        int operator*() {
          return *deque->pointersToBlocks[];
        }

        bool operator==(const Iterator& other) const {
          return this->index_in_block == other.index_in_block;
        }
        bool operator!=(const Iterator& other) const {
          return !(this -> pointer == other.pointer && this -> index_in_block == other.index_in_block);
        }
        Iterator& operator--(int) {
          auto old = this;
          index_in_block--;
          if (index_in_block == -1) {
            Chunk* block_ptr = *pointer;
            if (block_ptr -> isFirst()) {
              pointer = block_ptr -> last;
            } else {
              block_ptr--;
              pointer = &block_ptr;
            }
            index_in_block = BLOCK_SIZE - 1;
          }
          return *old;
        }
        Iterator& operator--() {
          index_in_block--;
          if (index_in_block == -1) {
            Chunk* block_ptr = *pointer;
            if (block_ptr -> isFirst()) {
              pointer = block_ptr -> last;
            } else {
              block_ptr--;
              pointer = &block_ptr;
            }
            index_in_block = BLOCK_SIZE - 1;
          }
          return *this;
        }
        Iterator& operator++() {
          index_in_block++;
          if (index_in_block == BLOCK_SIZE) {
            Chunk* block_ptr = *pointer;
            if (block_ptr -> isLast()) {
              pointer = block_ptr -> first;
            } else {
              std::cout << "before increment: " << block_ptr << "\n";
              block_ptr++;
              std::cout << "after increment: " << block_ptr << "\n";
              pointer = &block_ptr;
              std::cout << "pointer is "<< *pointer << std::endl;
            }
            index_in_block = 0;
          }
          return *this;
        }
        Iterator& operator++(int) {
          auto old = this;
          index_in_block++;
          if (index_in_block == BLOCK_SIZE) {
            Chunk* block_ptr = *pointer;
            if (block_ptr -> isLast()) {
              pointer = block_ptr -> first;
            } else {
              block_ptr++;
              pointer = &block_ptr;
            }
            index_in_block = 0;
          }
          return *old;
        }

        Iterator& operator+=(int x) {
          while (x > 0) {
            x--;
            index_in_block++;
            if (index_in_block == BLOCK_SIZE) {
              Chunk* block_ptr = *pointer;
              if (block_ptr -> isLast()) {
                pointer = block_ptr -> first;
              } else {
                block_ptr++;
                pointer = &block_ptr;
              }
              index_in_block = 0;
            }
          }

          return *this;
        }

        Iterator& operator-=(int x) {
          while (x > 0) {
            x--;
            index_in_block--;
            if (index_in_block == -1) {
              Chunk* block_ptr = *pointer;
              if (block_ptr -> isFirst()) {
                pointer = block_ptr -> last;
              } else {
                block_ptr--;
                pointer = &block_ptr;
              }
              index_in_block = BLOCK_SIZE - 1;
            }
          }

          return *this;
        }

        bool operator>(const Iterator& rhs) const
        {
          return this->index_in_block > rhs.index_in_block;
        }
        bool operator<(const Iterator& rhs) const
        {
          return this->index_in_block < rhs.index_in_block;
        }
        bool operator<=(const Iterator& rhs) const
        {
          return this->index_in_block <= rhs.index_in_block;
        }
        bool operator>=(const Iterator& rhs) const
        {
          return this->index_in_block >= rhs.index_in_block;
        }

        Iterator& operator-(int x) {
          Chunk* block_ptr = *pointer;
          Iterator* copy = this;
          copy -= x;
          return *copy;
        }

        Iterator& operator+(int x) {
          Chunk* block_ptr = *pointer;
          Iterator* copy = this;
          copy += x;
          return *copy;
        }

        Iterator& operator=(Iterator& x) {
          this -> pointer = x.pointer;
          this -> index_in_block = x.index_in_block;
          return *this;
        }

        void swap(Iterator& x, Iterator& y) {
          std::swap(x.pointer, y.pointer);
          std::swap(x.index_in_block, y.index_in_block);
        }

    };

    Deque();
    Deque(size_t size);
    Deque(const std::initializer_list<int> &list);
    ~Deque() {
      clear_blocks();
    }
    Deque(const Deque& other);
    Deque& operator = (const Deque& other);
    void resize(int new_size);

    void pushBack(int value);

    void popBack();

    void pushFront(int value);

    void popFront();

    void clear();

    bool empty() {
      return this -> size == 0 ? true : false;
    }
    int length() {
      return this -> size;
    }

    Iterator begin() {
      std::cout << "Second block_ptr: " << pointersToBlocks[1] << std::endl;
      std::cout << *Iterator(this, pointersToBlocks[beginBlock], &this->pointersToBlocks[beginBlock]->array[begin_]) << "\n";
      auto x = Iterator(this, pointersToBlocks[beginBlock], &this->pointersToBlocks[beginBlock]->array[begin_]);
      return x;
    }

    Iterator end() {
      //std::cout << *Iterator(pointersToBlocks[endBlock], end_);
      auto x = Iterator(this, pointersToBlocks[beginBlock], &this->pointersToBlocks[endBlock]->array[end_]);
      return x;
    }
};

void Deque::clear() {
  clear_blocks();
  Deque();
}

void Deque::change_length() {
  this -> capacity = size / BLOCK_SIZE * BLOCK_SIZE * 2;
  this -> numOfBlocks
  = capacity / BLOCK_SIZE;
  size_t old_total_blocks = numOfBlocks
          ;
  Chunk** new_block_ptrs = new Chunk*[numOfBlocks
                                      ];

  int index = 0;
  while (beginBlock != endBlock) {
    new_block_ptrs[index] = pointersToBlocks[beginBlock];
    beginBlock++;
    if (beginBlock == old_total_blocks) {
      beginBlock = 0;
    }
    index++;
  }
  new_block_ptrs[index] = pointersToBlocks[beginBlock];
  beginBlock = 0;
  endBlock = index - 1;
  delete[] pointersToBlocks;
  while (index != numOfBlocks
  ) {
    new_block_ptrs[index] = new Chunk();
    index++;
  }

  pointersToBlocks = new_block_ptrs;
  pointersToBlocks[numOfBlocks
  - 1] -> first = &pointersToBlocks[0];
  pointersToBlocks[0] -> last = &pointersToBlocks[numOfBlocks
                                                  - 1];
}

void Deque::clear_blocks() {
  for (int i = 0; i < numOfBlocks
  ; i++) {
    delete pointersToBlocks[i];
  }

  delete [] pointersToBlocks;
}

Deque::Deque() {
  this -> size = 0;
  this -> capacity = BLOCK_SIZE * 4;
  this -> pointersToBlocks = new Chunk*[4];
  this -> numOfBlocks
  = 4;
  for (int i = 0; i < numOfBlocks
  ; i++) {
    pointersToBlocks[i] = new Chunk();
  }
  pointersToBlocks[3] -> first = &pointersToBlocks[0];
  pointersToBlocks[0] -> last = &pointersToBlocks[3];

  this -> beginBlock  = 0;
  this -> endBlock  = 0;
  this -> begin_ = 0;
  this -> end_ = 0;
}

Deque::Deque(size_t size) {
  int number_of_blocks = size / BLOCK_SIZE + 4;
  this -> size = 0;
  this -> capacity =  number_of_blocks * BLOCK_SIZE;
  this -> pointersToBlocks = new Chunk*[number_of_blocks];
  this -> numOfBlocks
  = number_of_blocks;

  for (int i = 0; i < number_of_blocks; i++) {
    pointersToBlocks[i] = new Chunk();
  }
  pointersToBlocks[number_of_blocks - 1] -> first = &pointersToBlocks[0];
  pointersToBlocks[0] -> last = &pointersToBlocks[number_of_blocks - 1];

  for (int i = 0; i < size; i++) {
    pushBack
            (0);
  }
}

Deque::Deque(const std::initializer_list<int> &list) : Deque() {
  for (auto &current : list) {
    pushBack
            (current);
  }
}

Deque::Deque(const Deque &other) {
  this -> size = other.size;
  this -> capacity = other.capacity;

  this -> beginBlock = other.beginBlock;
  this -> endBlock = other.endBlock;
  this -> begin_ = other.begin_;
  this -> end_ = other.end_;

  this -> numOfBlocks
  = other.numOfBlocks
          ;
  this -> pointersToBlocks = new Chunk*[numOfBlocks
                                        ];
  for (int i = 0; i < numOfBlocks
  ; i++) {
    pointersToBlocks[i] = other.pointersToBlocks[i];
  }
}

Deque &Deque::operator=(const Deque &other) {
  this -> size = other.size;
  this -> capacity = other.capacity;
  this -> beginBlock = other.beginBlock;
  this -> endBlock = other.endBlock;
  this -> begin_ = other.begin_;
  this -> end_ = other.end_;

  this -> numOfBlocks
  = other.numOfBlocks
          ;
  this -> pointersToBlocks = new Chunk*[numOfBlocks
                                        ];
  for (int i = 0; i < numOfBlocks
  ; i++) {
    pointersToBlocks[i] = other.pointersToBlocks[i];
  }
  return *this;
}

void Deque::resize(int new_size) {
  while (size < new_size) {
    if (size == capacity || (beginBlock == endBlock && size > BLOCK_SIZE)) {
      change_length();
    }
    pushBack
            (0);
  }
  while (size > new_size) {
    if (numOfBlocks
    > 4 && size * 3 < capacity) {
      change_length();
    }
    popBack();
  }
}

void Deque::pushBack(int value) {
  if (size + 1 == capacity) {
    change_length();
  }
  int next_block = endBlock;
  int next_end = end_ + 1;
  if (next_end == BLOCK_SIZE) {
    next_block++;
    next_end = 0;

    if (next_block == numOfBlocks
    ) {
      next_block = 0;
    }
    if (next_block == beginBlock) {
      change_length();
      next_block = endBlock + 1;
    }
  }

  (*pointersToBlocks[endBlock]).array[end_] = value;
  endBlock = next_block;
  end_ = next_end;
  size++;
}

void Deque::popBack() {
  if (this -> size == 0) {
    std::cout << "Non-existent index\n";
  }
  else {
    size--;
    end_--;
    if (end_ == -1) {
      endBlock--;
      if (endBlock == -1) {
        endBlock = numOfBlocks
                ;
        end_ = BLOCK_SIZE - 1;
      }
    }
    if (numOfBlocks
    > 4 && size * 3 < capacity) {
      change_length();
    }
  }
}

void Deque::pushFront(int value) {
  if (size + 1 == capacity) {
    change_length();
  }
  if (begin_ == 0) {
    int prev_block = beginBlock;
    prev_block--;
    if (prev_block == -1) {
      prev_block = numOfBlocks
              - 1;
    }
    if (prev_block == endBlock) {
      change_length();
      prev_block = numOfBlocks
              - 1;
    }
    beginBlock = prev_block;
  }
  begin_--;
  (*pointersToBlocks[beginBlock]).array[begin_] = value;
  size++;
}

void Deque::popFront() {
  if (this -> size == 0) {
    std::cout << "Non-existent index\n";
  }
  else {
    size--;
    begin_++;
    if (begin_ == BLOCK_SIZE) {
      beginBlock++;
      if (beginBlock == numOfBlocks
      ) {
        beginBlock = 0;
        begin_ = 0;
      }
    }
    if (numOfBlocks
    > 4 && size * 3 < capacity) {
      change_length();
    }
  }
}


#endif //SWEATYDEQUE_DEQUE_H
