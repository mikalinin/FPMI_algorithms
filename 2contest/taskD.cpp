#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

class Minqueue {
  struct Pair {
    int elem;
    int min;
  };
  std::stack<Pair> stack1_;
  std::stack<Pair> stack2_;

public:
  void Enquery(int num) {
    if (stack1_.size() == 0) {
      stack1_.push(Pair(num, num));
    } else {
      int last_min = stack1_.top().min;
      stack1_.push(Pair(num, std::min(num, last_min)));
    }
  }

  int Dequeue() {
    int ans = 0;
    if (stack2_.size() == 0) {
      while (stack1_.size() > 0) {
        int elem = stack1_.top().elem;
        stack1_.pop();
        int min = 0;
        if (stack2_.size() == 0) {
          min = elem;
        } else {
          min = std::min(elem, stack2_.top().min);
        }
        stack2_.push(Pair(elem, min));
      }
      ans = stack2_.top().elem;
      stack2_.pop();
    } else {
      ans = stack2_.top().elem;
      stack2_.pop();
    }
    return ans;
  }

  int Front() {
    int ans = 0;
    if (stack2_.size() == 0) {
      while (stack1_.size() > 0) {
        int elem = stack1_.top().elem;
        stack1_.pop();
        int min = 0;
        if (stack2_.size() == 0) {
          min = elem;
        } else {
          min = std::min(elem, stack2_.top().min);
        }
        stack2_.push(Pair(elem, min));
      }
      ans = stack2_.top().elem;
    } else {
      ans = stack2_.top().elem;
    }
    return ans;
  }

  int Min() {
    int ans = 0;
    if (stack2_.size() == 0) {
      ans = stack1_.top().min;
    } else if (stack1_.size() == 0) {
      ans = stack2_.top().min;
    } else {
      ans = std::min(stack1_.top().min, stack2_.top().min);
    }
    return ans;
  }

  int Size() const { return stack1_.size() + stack2_.size(); }

  void Clear() {
    std::stack<Pair>().swap(stack1_);
    std::stack<Pair>().swap(stack2_);
  }

  bool IsVoid() const { return stack1_.size() == 0 && stack2_.size() == 0; }
};

int main() {
  std::string query;
  int query_num;
  Minqueue queue;
  std::cin >> query_num;
  for (int i = 0; i < query_num; i++) {
    std::cin >> query;
    if (query == "enqueue") {
      int num;
      std::cin >> num;
      queue.Enquery(num);
      std::cout << "ok"
                << "\n";
    } else if (query == "dequeue") {
      if (queue.IsVoid()) {
        std::cout << "error"
                  << "\n";
      } else {
        std::cout << queue.Dequeue() << "\n";
      }
    } else if (query == "front") {
      if (queue.IsVoid()) {
        std::cout << "error"
                  << "\n";
      } else {
        std::cout << queue.Front() << "\n";
      }
    } else if (query == "size") {
      std::cout << queue.Size() << "\n";
    } else if (query == "clear") {
      queue.Clear();
      std::cout << "ok"
                << "\n";
    } else if (query == "min") {
      if (queue.IsVoid()) {
        std::cout << "error"
                  << "\n";
      } else {
        std::cout << queue.Min() << "\n";
      }
    }
  }
  return 0;
}
