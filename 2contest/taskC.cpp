#include <deque>
#include <iostream>
#include <queue>

class Qdequeue {
  std::deque<int> deque_;
  int deque_size_ = 0;
  std::queue<int> queue_;
  int queue_size_ = 0;

  void Resize() {
    if (deque_size_ > queue_size_) {
      queue_.push(deque_.front());
      deque_.pop_front();
      queue_size_++;
      deque_size_--;
    }
  }

 public:
  void Med(int num) {
    deque_.push_front(num);
    deque_size_++;
    Resize();
  }

  void Back(int num) {
    deque_.push_back(num);
    deque_size_++;
    Resize();
  }

  int Extract() {
    int ans;
    ans = queue_.front();
    queue_.pop();
    queue_size_--;
    Resize();
    return ans;
  }
};

int main() {
  int requests;
  std::cin >> requests;
  char oper;
  int elem;
  Qdequeue struc;
  for (int i = 0; i < requests; ++i) {
    std::cin >> oper;
    if (oper == '+') {
      std::cin >> elem;
      struc.Back(elem);
    } else if (oper == '*') {
      std::cin >> elem;
      struc.Med(elem);
    } else if (oper == '-') {
      std::cout << struc.Extract() << '\n';
    }
  }
  return 0;
}
