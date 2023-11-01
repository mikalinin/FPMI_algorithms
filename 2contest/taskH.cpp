#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Elem {
  int val;
  int pair_ind;
};

std::vector<Elem> max_heap(1);
int max_heap_size = 0;
std::vector<Elem> min_heap(1);
int min_heap_size = 0;

void SiftUpMaxHeap(int index) {
  if (index == 1) {
    min_heap[max_heap[index].pair_ind].pair_ind = index;
    return;
  }
  int new_ind = index / 2;
  if (max_heap[index].val > max_heap[new_ind].val) {
    std::swap(min_heap[max_heap[index].pair_ind].pair_ind,
              min_heap[max_heap[new_ind].pair_ind].pair_ind);
    std::swap(max_heap[index], max_heap[new_ind]);
    SiftUpMaxHeap(new_ind);
  }
}

void SiftUpMinHeap(int index) {
  if (index == 1) {
    max_heap[min_heap[index].pair_ind].pair_ind = index;
    return;
  }
  int new_ind = index / 2;
  if (min_heap[index].val < min_heap[new_ind].val) {
    std::swap(max_heap[min_heap[index].pair_ind].pair_ind,
              max_heap[min_heap[new_ind].pair_ind].pair_ind);
    std::swap(min_heap[index], min_heap[new_ind]);
    SiftUpMinHeap(new_ind);
  }
}

void SiftDownMaxHeap(int index) {
  if (2 * index > max_heap_size) {
    min_heap[max_heap[index].pair_ind].pair_ind = index;
    return;
  }
  long new_ind = 2 * index;
  if (2 * index + 1 <= max_heap_size &&
      max_heap[2 * index + 1].val > max_heap[2 * index].val) {
    new_ind = 2 * index + 1;
  }
  if (max_heap[new_ind].val > max_heap[index].val) {
    std::swap(min_heap[max_heap[index].pair_ind].pair_ind,
              min_heap[max_heap[new_ind].pair_ind].pair_ind);
    std::swap(max_heap[index], max_heap[new_ind]);
    SiftDownMaxHeap(new_ind);
  }
}

void SiftDownMinHeap(int index) {
  if (2 * index > min_heap_size) {
    max_heap[min_heap[index].pair_ind].pair_ind = index;
    return;
  }
  long new_ind = 2 * index;
  if (2 * index + 1 <= min_heap_size &&
      min_heap[2 * index + 1].val < min_heap[2 * index].val) {
    new_ind = 2 * index + 1;
  }
  if (min_heap[new_ind].val < min_heap[index].val) {
    std::swap(max_heap[min_heap[index].pair_ind].pair_ind,
              max_heap[min_heap[new_ind].pair_ind].pair_ind);
    std::swap(min_heap[index], min_heap[new_ind]);
    SiftDownMinHeap(new_ind);
  }
}

int GetMax() { return max_heap[1].val; }

int GetMin() { return min_heap[1].val; }

void Insert(int value) {
  min_heap_size++;
  max_heap_size++;
  min_heap.push_back(Elem(value, min_heap_size));
  max_heap.push_back(Elem(value, max_heap_size));
  SiftUpMinHeap(min_heap_size);
  SiftUpMaxHeap(max_heap_size);
  std::cout << "ok" << '\n';
}

void ExtractMax() {
  if (max_heap_size == 0) {
    std::cout << "error" << '\n';
  } else {
    std::cout << max_heap[1].val << '\n';
    int ind = max_heap[1].pair_ind;
    int ind2 = min_heap[max_heap[1].pair_ind].pair_ind;
    int ind3 = min_heap[min_heap_size].pair_ind;
    std::swap(max_heap[ind2].pair_ind, max_heap[ind3].pair_ind);
    std::swap(min_heap[ind], min_heap[min_heap_size]);
    int ind1 = max_heap[1].pair_ind;
    ind2 = max_heap[max_heap_size].pair_ind;
    std::swap(min_heap[ind1].pair_ind, min_heap[ind2].pair_ind);
    std::swap(max_heap[1], max_heap[max_heap_size]);
    min_heap.pop_back();
    min_heap_size--;
    max_heap.pop_back();
    max_heap_size -= 1;
    SiftUpMinHeap(ind);
    SiftDownMaxHeap(1);
  }
}

void ExtractMin() {
  if (min_heap_size == 0) {
    std::cout << "error" << '\n';
  } else {
    std::cout << min_heap[1].val << '\n';
    int ind1 = max_heap[min_heap[1].pair_ind].pair_ind;
    int ind2 = max_heap[max_heap_size].pair_ind;
    int ind3 = min_heap[1].pair_ind;
    std::swap(min_heap[ind1].pair_ind, min_heap[ind2].pair_ind);
    std::swap(max_heap[ind3], max_heap[max_heap_size]);
    ind1 = min_heap[1].pair_ind;
    ind2 = min_heap[min_heap_size].pair_ind;
    std::swap(max_heap[ind1].pair_ind, max_heap[ind2].pair_ind);
    std::swap(min_heap[1], min_heap[min_heap_size]);
    max_heap.pop_back();
    max_heap_size--;
    min_heap.pop_back();
    min_heap_size -= 1;
    SiftUpMaxHeap(ind3);
    SiftDownMinHeap(1);
  }
}

int Size() { return min_heap_size; }

void Clear() {
  max_heap.clear();
  max_heap.push_back(Elem(0, 0));
  min_heap.clear();
  min_heap.push_back(Elem(0, 0));
  min_heap_size = 0;
  max_heap_size = 0;
  std::cout << "ok" << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int num;
  std::string query;
  std::cin >> num;
  for (int i = 0; i < num; i++) {
    std::cin >> query;
    if (query == "insert") {
      int val;
      std::cin >> val;
      Insert(val);
    } else if (query == "extract_min") {
      ExtractMin();
    } else if (query == "extract_max") {
      ExtractMax();
    } else if (query == "get_min") {
      if (min_heap_size == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << GetMin() << '\n';
      }
    } else if (query == "get_max") {
      if (max_heap_size == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << GetMax() << '\n';
      }
    } else if (query == "size") {
      std::cout << Size() << '\n';
    } else if (query == "clear") {
      Clear();
    }
  }
  return 0;
}
