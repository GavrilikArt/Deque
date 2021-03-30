#include "deque.h"
#include <iostream>
int main() {
  Deque d;
  d.push_front(2);
  d.push_front(3);
  d.push_front(4);
  for (int i : d) {
    std::cout << i << " ";
  }
  //...
}