#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Minmax {
  struct Elem {
    int val;
    int pair_ind;
  };
  std::vector<Elem> max_heap_;
  int max_heap_size_ = 0;
  std::vector<Elem> min_heap_;
  int min_heap_size_ = 0;

 public:
  Minmax() {
    max_heap_.push_back(Elem(0, 0));
    min_heap_.push_back(Elem(0, 0));
  }

  void SiftUpMaxHeap(int index) {
    if (index == 1) {
      min_heap_[max_heap_[index].pair_ind].pair_ind = index;
      return;
    }
    int new_ind = index / 2;
    if (max_heap_[index].val > max_heap_[new_ind].val) {
      std::swap(min_heap_[max_heap_[index].pair_ind].pair_ind,
                min_heap_[max_heap_[new_ind].pair_ind].pair_ind);
      std::swap(max_heap_[index], max_heap_[new_ind]);
      SiftUpMaxHeap(new_ind);
    }
  }

  void SiftUpMinHeap(int index) {
    if (index == 1) {
      max_heap_[min_heap_[index].pair_ind].pair_ind = index;
      return;
    }
    int new_ind = index / 2;
    if (min_heap_[index].val < min_heap_[new_ind].val) {
      std::swap(max_heap_[min_heap_[index].pair_ind].pair_ind,
                max_heap_[min_heap_[new_ind].pair_ind].pair_ind);
      std::swap(min_heap_[index], min_heap_[new_ind]);
      SiftUpMinHeap(new_ind);
    }
  }

  void SiftDownMaxHeap(int index) {
    if (2 * index > max_heap_size_) {
      min_heap_[max_heap_[index].pair_ind].pair_ind = index;
      return;
    }
    long new_ind = 2 * index;
    if (2 * index + 1 <= max_heap_size_ &&
        max_heap_[2 * index + 1].val > max_heap_[2 * index].val) {
      new_ind = 2 * index + 1;
    }
    if (max_heap_[new_ind].val > max_heap_[index].val) {
      std::swap(min_heap_[max_heap_[index].pair_ind].pair_ind,
                min_heap_[max_heap_[new_ind].pair_ind].pair_ind);
      std::swap(max_heap_[index], max_heap_[new_ind]);
      SiftDownMaxHeap(new_ind);
    }
  }

  void SiftDownMinHeap(int index) {
    if (2 * index > min_heap_size_) {
      max_heap_[min_heap_[index].pair_ind].pair_ind = index;
      return;
    }
    long new_ind = 2 * index;
    if (2 * index + 1 <= min_heap_size_ &&
        min_heap_[2 * index + 1].val < min_heap_[2 * index].val) {
      new_ind = 2 * index + 1;
    }
    if (min_heap_[new_ind].val < min_heap_[index].val) {
      std::swap(max_heap_[min_heap_[index].pair_ind].pair_ind,
                max_heap_[min_heap_[new_ind].pair_ind].pair_ind);
      std::swap(min_heap_[index], min_heap_[new_ind]);
      SiftDownMinHeap(new_ind);
    }
  }

  int GetMax() { return max_heap_[1].val; }

  int GetMin() { return min_heap_[1].val; }

  void Insert(int value) {
    ++min_heap_size_;
    ++max_heap_size_;
    min_heap_.push_back(Elem(value, min_heap_size_));
    max_heap_.push_back(Elem(value, max_heap_size_));
    SiftUpMinHeap(min_heap_size_);
    SiftUpMaxHeap(max_heap_size_);
  }

  int ExtractMax() {
    int ans = max_heap_[1].val;
    int ind = max_heap_[1].pair_ind;
    int ind2 = min_heap_[max_heap_[1].pair_ind].pair_ind;
    int ind3 = min_heap_[min_heap_size_].pair_ind;
    std::swap(max_heap_[ind2].pair_ind, max_heap_[ind3].pair_ind);
    std::swap(min_heap_[ind], min_heap_[min_heap_size_]);
    int ind1 = max_heap_[1].pair_ind;
    ind2 = max_heap_[max_heap_size_].pair_ind;
    std::swap(min_heap_[ind1].pair_ind, min_heap_[ind2].pair_ind);
    std::swap(max_heap_[1], max_heap_[max_heap_size_]);
    min_heap_.pop_back();
    --min_heap_size_;
    max_heap_.pop_back();
    --max_heap_size_;
    SiftUpMinHeap(ind);
    SiftDownMaxHeap(1);
    return ans;
  }

  int ExtractMin() {
    int ans = min_heap_[1].val;
    int ind1 = max_heap_[min_heap_[1].pair_ind].pair_ind;
    int ind2 = max_heap_[max_heap_size_].pair_ind;
    int ind3 = min_heap_[1].pair_ind;
    std::swap(min_heap_[ind1].pair_ind, min_heap_[ind2].pair_ind);
    std::swap(max_heap_[ind3], max_heap_[max_heap_size_]);
    ind1 = min_heap_[1].pair_ind;
    ind2 = min_heap_[min_heap_size_].pair_ind;
    std::swap(max_heap_[ind1].pair_ind, max_heap_[ind2].pair_ind);
    std::swap(min_heap_[1], min_heap_[min_heap_size_]);
    max_heap_.pop_back();
    --max_heap_size_;
    min_heap_.pop_back();
    --min_heap_size_;
    SiftUpMaxHeap(ind3);
    SiftDownMinHeap(1);
    return ans;
  }

  int Size() const { return min_heap_size_; }

  void Clear() {
    max_heap_.clear();
    max_heap_.push_back(Elem(0, 0));
    min_heap_.clear();
    min_heap_.push_back(Elem(0, 0));
    min_heap_size_ = 0;
    max_heap_size_ = 0;
  }

  int GetMinHeapSize() const { return min_heap_size_; }

  int GetMaxHeapSize() const { return max_heap_size_; }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int num;
  std::string query;
  std::cin >> num;
  Minmax heap;
  for (int i = 0; i < num; i++) {
    std::cin >> query;
    if (query == "insert") {
      int val;
      std::cin >> val;
      heap.Insert(val);
      std::cout << "ok" << '\n';
    } else if (query == "extract_min") {
      if (heap.GetMinHeapSize() == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << heap.ExtractMin() << '\n';
      }
    } else if (query == "extract_max") {
      if (heap.GetMaxHeapSize() == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << heap.ExtractMax() << '\n';
      }
    } else if (query == "get_min") {
      if (heap.GetMinHeapSize() == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << heap.GetMin() << '\n';
      }
    } else if (query == "get_max") {
      if (heap.GetMaxHeapSize() == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << heap.GetMax() << '\n';
      }
    } else if (query == "size") {
      std::cout << heap.Size() << '\n';
    } else if (query == "clear") {
      heap.Clear();
      std::cout << "ok" << '\n';
    }
  }
  return 0;
}
