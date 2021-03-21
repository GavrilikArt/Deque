#include <iostream>
#include <iterator>
#include <vector>
#include <initializer_list>

//class Deque {
//    private:
//        class Block {
//
//            public:
//                Block** first;
//                Block** last;
//                int* array;
//
//                Block(Block& other) {
//                  first = other.first;
//                  last = other.last;
//                  array = other.array;
//                }
//
//                Block() {
//                    array = new int[BLOCK_SIZE];
//                    first = nullptr;
//                    last = nullptr;
//                }
//                ~Block() {
//                    delete[] array;
//                }
//                bool isFirst() {
//                    return last != nullptr;
//                }
//                bool isLast() {
//                    return first != nullptr;
//                }
//        };
//        const static int BLOCK_SIZE = 2;
//        int block_begin_;
//        int block_end_;
//        int begin_;
//        int end_;
//        Block** block_ptrs;
//        size_t size;
//        size_t capacity;
//        size_t total_blocks;
//        void clear_blocks(){
//            for (int i = 0; i < total_blocks; i++) {
//                delete block_ptrs[i];
//            }
//
//            delete [] block_ptrs;
//        }
//        void change_length() {
//            this -> capacity = size / BLOCK_SIZE * BLOCK_SIZE * 2;
//            this -> total_blocks = capacity / BLOCK_SIZE;
//            size_t old_total_blocks = total_blocks;
//            Block** new_block_ptrs = new Block*[total_blocks];
//
//            int index = 0;
//            while (block_begin_ != block_end_) {
//                new_block_ptrs[index] = block_ptrs[block_begin_];
//                block_begin_++;
//                if (block_begin_ == old_total_blocks) {
//                    block_begin_ = 0;
//                }
//                index++;
//            }
//            new_block_ptrs[index] = block_ptrs[block_begin_];
//            block_begin_ = 0;
//            block_end_ = index - 1;
//            delete[] block_ptrs;
//            while (index != total_blocks) {
//                new_block_ptrs[index] = new Block();
//                index++;
//            }
//
//            block_ptrs = new_block_ptrs;
//            block_ptrs[total_blocks - 1] -> first = &block_ptrs[0];
//            block_ptrs[0] -> last = &block_ptrs[total_blocks - 1];
//        }
//
//    public:
//        class Iterator : std::iterator<std::random_access_iterator_tag, int> {
//            friend Deque;
//            private:
//                Block** pointer;
//                int index_in_block;
//            public:
//                Iterator() {
//                    pointer = nullptr;
//                }
//                // one:
//                Iterator(Block* value, int index_in_block)
//                {
//                    this -> pointer = &value;
//                    this -> index_in_block = index_in_block;
//                }
//                int operator*() {
//                    Block* block_ptr = *pointer;
//                    std::cout << "Has to be the same as block_ptrs[1]: " << block_ptr << std::endl;
//                    int x = (*block_ptr).array[index_in_block];
//                    return x;
//                }
//                bool operator==(const Iterator& other) const {
//                    return this -> pointer == other.pointer && this -> index_in_block == other.index_in_block;
//                }
//                bool operator!=(const Iterator& other) const {
//                    return !(this -> pointer == other.pointer && this -> index_in_block == other.index_in_block);
//                }
//                /*bool operator<(const Iterator& other) const {
//                    Block* block_ptr = *pointer;
//                    Block* other_block_ptr = *other.pointer;
//
//                    if (block_ptr == other_block_ptr) {
//                        return index_in_block < other.index_in_block;
//                    }
//                    return pointer->index < other.pointer->index;
//                }
//                bool operator>(const Iterator& other) const {
//                    if (pointer->index == other.pointer->index) {
//                        return this -> pointer > other.pointer;
//                    }
//                    return pointer->index > other.pointer->index;
//                }
//                bool operator<=(const Iterator& other) const {
//                    if (pointer->index == other.pointer->index) {
//                        return this -> pointer <= other.pointer;
//                    }
//                    return pointer->index <= other.pointer->index;
//                }
//                bool operator>=(const Iterator& other) const {
//                    if (pointer->index == other.pointer->index) {
//                        return this -> pointer >= other.pointer;
//                    }
//                    return pointer->index >= other.pointer->index;
//                }*/
//                Iterator& operator--(int) {
//                    auto old = this;
//                    index_in_block--;
//                    if (index_in_block == -1) {
//                        Block* block_ptr = *pointer;
//                        if (block_ptr -> isFirst()) {
//                            pointer = block_ptr -> last;
//                        } else {
//                            block_ptr--;
//                            pointer = &block_ptr;
//                        }
//                        index_in_block = BLOCK_SIZE - 1;
//                    }
//                    return *old;
//                }
//                Iterator& operator--() {
//                    index_in_block--;
//                    if (index_in_block == -1) {
//                        Block* block_ptr = *pointer;
//                        if (block_ptr -> isFirst()) {
//                            pointer = block_ptr -> last;
//                        } else {
//                            block_ptr--;
//                            pointer = &block_ptr;
//                        }
//                        index_in_block = BLOCK_SIZE - 1;
//                    }
//                    return *this;
//                }
//                Iterator& operator++() {
//                    index_in_block++;
//                    if (index_in_block == BLOCK_SIZE) {
//                        Block* block_ptr = *pointer;
//                        if (block_ptr -> isLast()) {
//                            pointer = block_ptr -> first;
//                        } else {
//                            std::cout << "before increment: " << block_ptr << "\n";
//                            block_ptr++;
//                            std::cout << "after increment: " << block_ptr << "\n";
//                            pointer = &block_ptr;
//                            std::cout << "pointer is "<< *pointer << std::endl;
//                        }
//                        index_in_block = 0;
//                    }
//                    return *this;
//                }
//                Iterator& operator++(int) {
//                    auto old = this;
//                    index_in_block++;
//                    if (index_in_block == BLOCK_SIZE) {
//                        Block* block_ptr = *pointer;
//                        if (block_ptr -> isLast()) {
//                            pointer = block_ptr -> first;
//                        } else {
//                            block_ptr++;
//                            pointer = &block_ptr;
//                        }
//                        index_in_block = 0;
//                    }
//                    return *old;
//                }
//                Iterator& operator+=(int x) {
//                    while (x > 0) {
//                        x--;
//                        index_in_block++;
//                        if (index_in_block == BLOCK_SIZE) {
//                            Block* block_ptr = *pointer;
//                            if (block_ptr -> isLast()) {
//                                pointer = block_ptr -> first;
//                            } else {
//                                block_ptr++;
//                                pointer = &block_ptr;
//                            }
//                            index_in_block = 0;
//                        }
//                    }
//
//                    return *this;
//                }
//                Iterator& operator-=(int x) {
//                    while (x > 0) {
//                        x--;
//                        index_in_block--;
//                        if (index_in_block == -1) {
//                            Block* block_ptr = *pointer;
//                            if (block_ptr -> isFirst()) {
//                                pointer = block_ptr -> last;
//                            } else {
//                                block_ptr--;
//                                pointer = &block_ptr;
//                            }
//                            index_in_block = BLOCK_SIZE - 1;
//                        }
//                    }
//
//                    return *this;
//                }
//                Iterator& operator-(int x) {
//                    Block* block_ptr = *pointer;
//                    Iterator* copy = this;
//                    copy -= x;
//                    return *copy;
//                }
//                Iterator& operator+(int x) {
//                    Block* block_ptr = *pointer;
//                    Iterator* copy = this;
//                    copy += x;
//                    return *copy;
//                }
//                Iterator& operator=(Iterator& x) {
//                    this -> pointer = x.pointer;
//                    this -> index_in_block = x.index_in_block;
//                    return *this;
//                }
//                void swap(Iterator& x, Iterator& y) {
//                    std::swap(x.pointer, y.pointer);
//                    std::swap(x.index_in_block, y.index_in_block);
//                }
//               /* int operator-(Iterator& x) {
//                    auto y = *this;
//                    int answer = 0;
//                    if (x > y) swap(x, y);
//                    while (x != y) {
//                        x++;
//                        answer++;
//                    }
//                    return answer;
//                }*/
//        };
//
//        Deque() {
//            this -> size = 0;
//            this -> capacity = BLOCK_SIZE * 4;
//            this -> block_ptrs = new Block*[4];
//            this -> total_blocks = 4;
//            for (int i = 0; i < total_blocks; i++) {
//                block_ptrs[i] = new Block();
//            }
//            block_ptrs[3] -> first = &block_ptrs[0];
//            block_ptrs[0] -> last = &block_ptrs[3];
//
//            this -> block_begin_  = 0;
//            this -> block_end_  = 0;
//            this -> begin_ = 0;
//            this -> end_ = 0;
//        }
//        Deque(size_t size) {
//            int number_of_blocks = size / BLOCK_SIZE + 4;
//            this -> size = 0;
//            this -> capacity =  number_of_blocks * BLOCK_SIZE;
//            this -> block_ptrs = new Block*[number_of_blocks];
//            this -> total_blocks = number_of_blocks;
//
//            for (int i = 0; i < number_of_blocks; i++) {
//                block_ptrs[i] = new Block();
//            }
//            block_ptrs[number_of_blocks - 1] -> first = &block_ptrs[0];
//            block_ptrs[0] -> last = &block_ptrs[number_of_blocks - 1];
//
//            for (int i = 0; i < size; i++) {
//                push_back(0);
//            }
//        }
//        Deque(const std::initializer_list<int> &list) : Deque() {
//            for (auto &current : list) {
//                push_back(current);
//            }
//        }
//        ~Deque() {
//            clear_blocks();
//        }
//        Deque(const Deque& other) {
//            this -> size = other.size;
//            this -> capacity = other.capacity;
//
//            this -> block_begin_ = other.block_begin_;
//            this -> block_end_ = other.block_end_;
//            this -> begin_ = other.begin_;
//            this -> end_ = other.end_;
//
//            this -> total_blocks = other.total_blocks;
//            this -> block_ptrs = new Block*[total_blocks];
//            for (int i = 0; i < total_blocks; i++) {
//                block_ptrs[i] = other.block_ptrs[i];
//            }
//        }
//        Deque& operator = (const Deque& other) {
//            this -> size = other.size;
//            this -> capacity = other.capacity;
//            this -> block_begin_ = other.block_begin_;
//            this -> block_end_ = other.block_end_;
//            this -> begin_ = other.begin_;
//            this -> end_ = other.end_;
//
//            this -> total_blocks = other.total_blocks;
//            this -> block_ptrs = new Block*[total_blocks];
//            for (int i = 0; i < total_blocks; i++) {
//                block_ptrs[i] = other.block_ptrs[i];
//            }
//            return *this;
//        }
//
//
//        void resize(int new_size) {
//            while (size < new_size) {
//                if (size == capacity || (block_begin_ == block_end_ && size > BLOCK_SIZE)) {
//                    change_length();
//                }
//                push_back(0);
//            }
//            while (size > new_size) {
//                if (total_blocks > 4 && size * 3 < capacity) {
//                    change_length();
//                }
//                pop_back();
//            }
//        }
//
//        void push_back(int value) {
//            if (size + 1 == capacity) {
//                change_length();
//            }
//            int next_block = block_end_;
//            int next_end = end_ + 1;
//            if (next_end == BLOCK_SIZE) {
//                next_block++;
//                next_end = 0;
//
//                if (next_block == total_blocks) {
//                    next_block = 0;
//                }
//                if (next_block == block_begin_) {
//                    change_length();
//                    next_block = block_end_ + 1;
//                }
//            }
//
//            (*block_ptrs[block_end_]).array[end_] = value;
//            block_end_ = next_block;
//            end_ = next_end;
//            size++;
//        }
//
//        void pop_back() {
//            if (this -> size == 0) {
//                std::cout << "Non-existent index\n";
//            }
//            else {
//                size--;
//                end_--;
//                if (end_ == -1) {
//                    block_end_--;
//                    if (block_end_ == -1) {
//                        block_end_ = total_blocks;
//                        end_ = BLOCK_SIZE - 1;
//                    }
//                }
//                if (total_blocks > 4 && size * 3 < capacity) {
//                    change_length();
//                }
//            }
//        }
//
//        void push_front(int value) {
//            if (size + 1 == capacity) {
//                change_length();
//            }
//            if (begin_ == 0) {
//                int prev_block = block_begin_;
//                prev_block--;
//                if (prev_block == -1) {
//                    prev_block = total_blocks - 1;
//                }
//                if (prev_block == block_end_) {
//                    change_length();
//                    prev_block = total_blocks - 1;
//                }
//                block_begin_ = prev_block;
//            }
//            begin_--;
//            (*block_ptrs[block_begin_]).array[begin_] = value;
//            size++;
//        }
//
//        void pop_front() {
//            if (this -> size == 0) {
//                std::cout << "Non-existent index\n";
//            }
//            else {
//                size--;
//                begin_++;
//                if (begin_ == BLOCK_SIZE) {
//                    block_begin_++;
//                    if (block_begin_ == total_blocks) {
//                        block_begin_ = 0;
//                        begin_ = 0;
//                    }
//                }
//                if (total_blocks > 4 && size * 3 < capacity) {
//                    change_length();
//                }
//            }
//        }
//
//        void clear() {
//            clear_blocks();
//            Deque();
//        }
//        bool empty() {
//            return this -> size == 0 ? true : false;
//        }
//        int length() {
//            return this -> size;
//        }
//        Iterator begin() {
//            std::cout << "Second block_ptr: " << block_ptrs[1] << std::endl;
//            std::cout << *Iterator(block_ptrs[block_begin_], begin_) << "\n";
//            auto x = Iterator(block_ptrs[block_begin_], begin_);
//            return x;
//        }
//        Iterator end() {
//            //std::cout << *Iterator(block_ptrs[block_end_], end_);
//            auto x = Iterator(block_ptrs[block_end_], end_);
//            return x;
//        }
//};
#include "deque.h"

int main() {
    Deque Mydeque = {1, 2, 3};
    Deque::Iterator it;
    for (auto i : Mydeque) {
      std::cout << i << " ";
    }

    return 0;
}
