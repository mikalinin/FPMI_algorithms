#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Pair {
  long long value;
  long long query;
};

void SiftUp(std::vector<Pair>& heap, long long value,
            std::vector<int>& query_mas) {
  while (value != 1) {
    if (heap[value].value < heap[value / 2].value) {
      query_mas[heap[value].query] = value / 2;
      query_mas[heap[value / 2].query] = value;
      std::swap(heap[value], heap[value / 2]);
      value /= 2;
    } else {
      break;
    }
  }
}

void SiftDown(std::vector<Pair>& heap, long long value, int& size,
              std::vector<int>& query_mas) {
  while (2 * value <= size) {
    long long new_ind = 2 * value;
    if (2 * value + 1 <= size &&
        heap[2 * value + 1].value < heap[2 * value].value) {
      new_ind = 2 * value + 1;
    }
    if (heap[new_ind].value < heap[value].value) {
      query_mas[heap[new_ind].query] = value;
      query_mas[heap[value].query] = new_ind;
      std::swap(heap[new_ind], heap[value]);
      value = new_ind;
    } else {
      break;
    }
  }
}

long long GetMin(std::vector<Pair> heap) { return heap[1].value; }

void DecreaseKey(std::vector<Pair>& heap, long long query, long long delta,
                 std::vector<int>& query_mas) {
  heap[query_mas[query]].value -= delta;
  SiftUp(heap, query_mas[query], query_mas);
}

void Insert(std::vector<Pair>& heap, long long value, int& size,
            long long query, std::vector<int>& query_mas) {
  heap.push_back(Pair(value, query));
  size += 1;
  query_mas[query] = size;
  SiftUp(heap, size, query_mas);
}

void ExtractMin(std::vector<Pair>& heap, int& size,
                std::vector<int>& query_mas) {
  heap[1] = heap[size];
  query_mas[heap[size].query] = 1;
  heap.pop_back();
  size -= 1;
  SiftDown(heap, 1, size, query_mas);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  const int kMaxind = 1000000;
  int size = 0;
  std::vector<Pair> heap(1);
  std::vector<int> query_mas(kMaxind);
  heap[0] = Pair(0, 0);
  std::string query;
  long long query_num;
  std::cin >> query_num;
  for (long long i = 1; i <= query_num; i++) {
    std::cin >> query;
    if (query == "insert") {
      long long num;
      std::cin >> num;
      Insert(heap, num, size, i, query_mas);
    } else if (query == "getMin") {
      std::cout << GetMin(heap) << "\n";
    } else if (query == "extractMin") {
      ExtractMin(heap, size, query_mas);
    } else if (query == "decreaseKey") {
      long long ind;
      long long delta;
      std::cin >> ind >> delta;
      DecreaseKey(heap, ind, delta, query_mas);
    }
  }
  return 0;
}
