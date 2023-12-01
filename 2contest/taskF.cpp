#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Heap {
  struct Pair {
    long long value;
    long long query;
  };
  std::vector<Pair> heap_;
  int size_ = 0;
  std::vector<int> query_mas_;

 public:
  Heap() {
    heap_.push_back(Pair(0, 0));
    const int kMaxind = 1000000;
    query_mas_.resize(kMaxind);
  }

  void SiftUp(long long value) {
    while (value != 1) {
      if (heap_[value].value >= heap_[value / 2].value) {
        break;
      }
      query_mas_[heap_[value].query] = value / 2;
      query_mas_[heap_[value / 2].query] = value;
      std::swap(heap_[value], heap_[value / 2]);
      value /= 2;
    }
  }

  void SiftDown(long long value) {
    while (2 * value <= size_) {
      long long new_ind = 2 * value;
      if (2 * value + 1 <= size_ &&
          heap_[2 * value + 1].value < heap_[2 * value].value) {
        new_ind = 2 * value + 1;
      }
      if (heap_[new_ind].value < heap_[value].value) {
        query_mas_[heap_[new_ind].query] = value;
        query_mas_[heap_[value].query] = new_ind;
        std::swap(heap_[new_ind], heap_[value]);
        value = new_ind;
      } else {
        break;
      }
    }
  }

  long long GetMin() { return heap_[1].value; }

  void DecreaseKey(long long query, long long delta) {
    heap_[query_mas_[query]].value -= delta;
    SiftUp(query_mas_[query]);
  }

  void Insert(long long value, long long query) {
    heap_.push_back(Pair(value, query));
    size_ += 1;
    query_mas_[query] = size_;
    SiftUp(size_);
  }

  void ExtractMin() {
    heap_[1] = heap_[size_];
    query_mas_[heap_[size_].query] = 1;
    heap_.pop_back();
    size_ -= 1;
    SiftDown(1);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  Heap heap;
  std::string query;
  long long query_num;
  std::cin >> query_num;
  for (long long i = 1; i <= query_num; ++i) {
    std::cin >> query;
    if (query == "insert") {
      long long num;
      std::cin >> num;
      heap.Insert(num, i);
    } else if (query == "getMin") {
      std::cout << heap.GetMin() << "\n";
    } else if (query == "extractMin") {
      heap.ExtractMin();
    } else if (query == "decreaseKey") {
      long long ind;
      long long delta;
      std::cin >> ind >> delta;
      heap.DecreaseKey(ind, delta);
    }
  }
  return 0;
}
