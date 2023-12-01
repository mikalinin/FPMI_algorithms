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
  int stack1_size_ = 0;
  std::stack<Pair> stack2_;
  int stack2_size_ = 0;

 public:
  void Enquery(int num) {
    if (stack1_size_ == 0) {
      stack1_.push(Pair(num, num));
      ++stack1_size_;
    } else {
      int last_min = stack1_.top().min;
      stack1_.push(Pair(num, std::min(num, last_min)));
      ++stack1_size_;
    }
  }

  int Dequeue() {
    int ans = 0;
    if (stack2_size_ == 0) {
      while (stack1_size_ > 0) {
        int elem = stack1_.top().elem;
        stack1_.pop();
        --stack1_size_;
        int min = 0;
        if (stack2_size_ == 0) {
          min = elem;
        } else {
          min = std::min(elem, stack2_.top().min);
        }
        stack2_.push(Pair(elem, min));
        ++stack2_size_;
      }
      ans = stack2_.top().elem;
      stack2_.pop();
      --stack2_size_;
    } else {
      ans = stack2_.top().elem;
      stack2_.pop();
      --stack2_size_;
    }
    return ans;
  }

  int Front() {
    int ans = 0;
    if (stack2_size_ == 0) {
      while (stack1_size_ > 0) {
        int elem = stack1_.top().elem;
        stack1_.pop();
        --stack1_size_;
        int min = 0;
        if (stack2_size_ == 0) {
          min = elem;
        } else {
          min = std::min(elem, stack2_.top().min);
        }
        stack2_.push(Pair(elem, min));
        ++stack2_size_;
      }
      ans = stack2_.top().elem;
    } else {
      ans = stack2_.top().elem;
    }
    return ans;
  }

  int Min() {
    int ans = 0;
    if (stack2_size_ == 0) {
      ans = stack1_.top().min;
    } else if (stack1_size_ == 0) {
      ans = stack2_.top().min;
    } else {
      ans = std::min(stack1_.top().min, stack2_.top().min);
    }
    return ans;
  }

  int Size() const { return stack1_size_ + stack2_size_; }

  void Clear() {
    std::stack<Pair>().swap(stack1_);
    std::stack<Pair>().swap(stack2_);
    stack1_size_ = 0;
    stack2_size_ = 0;
  }

  bool IsVoid() const { return stack1_size_ == 0 && stack2_size_ == 0; }
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
