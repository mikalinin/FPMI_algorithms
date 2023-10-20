#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

struct Pair {
  int elem;
  int min;
};

void Enquery(std::stack<Pair>& stack1, int& stack1_size, int num) {
  if (stack1_size == 0) {
    stack1.push(Pair(num, num));
    stack1_size++;
  } else {
    int last_min = stack1.top().min;
    stack1.push(Pair(num, std::min(num, last_min)));
    stack1_size++;
  }
}

void Dequeue(std::stack<Pair>& stack1, int& stack1_size,
             std::stack<Pair>& stack2, int& stack2_size) {
  if (stack1_size == 0 && stack2_size == 0) {
    std::cout << "error"
              << "\n";
  } else if (stack2_size == 0) {
    while (stack1_size > 0) {
      int elem = stack1.top().elem;
      stack1.pop();
      stack1_size--;
      int min = 0;
      if (stack2_size == 0) {
        min = elem;
      } else {
        min = std::min(elem, stack2.top().min);
      }
      stack2.push(Pair(elem, min));
      stack2_size++;
    }
    std::cout << stack2.top().elem << '\n';
    stack2.pop();
    stack2_size--;
  } else {
    std::cout << stack2.top().elem << '\n';
    stack2.pop();
    stack2_size--;
  }
}

void Front(std::stack<Pair>& stack1, int& stack1_size, std::stack<Pair>& stack2,
           int& stack2_size) {
  if (stack1_size == 0 && stack2_size == 0) {
    std::cout << "error"
              << "\n";
  } else if (stack2_size == 0) {
    while (stack1_size > 0) {
      int elem = stack1.top().elem;
      stack1.pop();
      stack1_size--;
      int min = 0;
      if (stack2_size == 0) {
        min = elem;
      } else {
        min = std::min(elem, stack2.top().min);
      }
      stack2.push(Pair(elem, min));
      stack2_size++;
    }
    std::cout << stack2.top().elem << '\n';
  } else {
    std::cout << stack2.top().elem << '\n';
  }
}

void Min(std::stack<Pair>& stack1, int& stack1_size, std::stack<Pair>& stack2,
         int& stack2_size) {
  if (stack1_size == 0 && stack2_size == 0) {
    std::cout << "error"
              << "\n";
  } else if (stack2_size == 0) {
    std::cout << stack1.top().min << "\n";
  } else if (stack1_size == 0) {
    std::cout << stack2.top().min << "\n";
  } else {
    std::cout << std::min(stack1.top().min, stack2.top().min) << "\n";
  }
}

int main() {
  std::string query;
  std::stack<Pair> stack1;
  std::stack<Pair> stack2;
  int stack1_size = 0;
  int stack2_size = 0;
  int query_num;
  std::cin >> query_num;
  for (int i = 0; i < query_num; i++) {
    std::cin >> query;
    if (query == "enqueue") {
      int num;
      std::cin >> num;
      Enquery(stack1, stack1_size, num);
      std::cout << "ok"
                << "\n";
    } else if (query == "dequeue") {
      Dequeue(stack1, stack1_size, stack2, stack2_size);
    } else if (query == "front") {
      Front(stack1, stack1_size, stack2, stack2_size);
    } else if (query == "size") {
      std::cout << stack1_size + stack2_size << "\n";
    } else if (query == "clear") {
      std::stack<int> stack1;
      std::stack<int> stack2;
      stack1_size = 0;
      stack2_size = 0;
      std::cout << "ok"
                << "\n";
    } else if (query == "min") {
      Min(stack1, stack1_size, stack2, stack2_size);
    }
  }
  return 0;
}
