#include <deque>
#include <iostream>
#include <queue>

void Resize(std::deque<int>& deque, int& deque_size, std::queue<int>& queue,
            int& queue_size) {
  if (deque_size > queue_size) {
    queue.push(deque.front());
    deque.pop_front();
    queue_size++;
    deque_size--;
  }
}

void Med(std::deque<int>& deque, int& deque_size, std::queue<int>& queue,
         int& queue_size, int num) {
  deque.push_front(num);
  deque_size++;
  Resize(deque, deque_size, queue, queue_size);
}

void Back(std::deque<int>& deque, int& deque_size, std::queue<int>& queue,
          int& queue_size, int num) {
  deque.push_back(num);
  deque_size++;
  Resize(deque, deque_size, queue, queue_size);
}

void Extract(std::deque<int>& deque, int& deque_size, std::queue<int>& queue,
             int& queue_size) {
  std::cout << queue.front() << '\n';
  queue.pop();
  queue_size--;
  Resize(deque, deque_size, queue, queue_size);
}

int main() {
  std::queue<int> queue;
  std::deque<int> deque;
  int requests;
  std::cin >> requests;
  char oper;
  int elem;
  int queue_size = 0;
  int deque_size = 0;
  for (int i = 0; i < requests; i++) {
    std::cin >> oper;
    if (oper == '+') {
      std::cin >> elem;
      Back(deque, deque_size, queue, queue_size, elem);
    } else if (oper == '*') {
      std::cin >> elem;
      Med(deque, deque_size, queue, queue_size, elem);
    } else if (oper == '-') {
      Extract(deque, deque_size, queue, queue_size);
    }
  }
  return 0;
}
