#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

class Tree {
 public:
  std::vector<std::vector<long long>> tree;

  Tree(int size) { tree.resize(size); }

  void Build(int vershina, int tl, int tr, std::vector<long long>& arr,
             int num) {
    if (tl == tr) {
      if (tl < num) {
        tree[vershina].push_back(arr[tl]);
      }
      return;
    }
    int tm = (tl + tr) / 2;
    Build(2 * vershina, tl, tm, arr, num);
    Build(2 * vershina + 1, tm + 1, tr, arr, num);
    std::merge(tree[2 * vershina].begin(), tree[2 * vershina].end(),
               tree[2 * vershina + 1].begin(), tree[2 * vershina + 1].end(),
               std::back_inserter(tree[vershina]));
  }

  long long Get(int vershina, int tl, int tr, std::array<int, 4> query) {
    if (query[0] > tr || tl > query[1]) {
      return 0;
    }
    if (query[0] <= tl && tr <= query[1]) {
      int ind1 = std::upper_bound(tree[vershina].begin(), tree[vershina].end(),
                                  query[2] - 1) -
                 tree[vershina].begin();
      int ind2 = std::upper_bound(tree[vershina].begin(), tree[vershina].end(),
                                  query[3]) -
                 tree[vershina].begin();
      return std::abs(ind2 - ind1);
    }
    int tm = (tl + tr) / 2;
    return Get(2 * vershina, tl, tm, query) +
           Get(2 * vershina + 1, tm + 1, tr, query);
  }
};

int Size(int num) {
  int count = 0;
  while (num > 0) {
    ++count;
    num /= 2;
  }
  return pow(2, count);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int num;
  int query_num;
  std::cin >> num >> query_num;
  std::vector<long long> arr(num);
  for (int i = 0; i < num; ++i) {
    std::cin >> arr[i];
  }
  int size = Size(num);
  Tree tr(2 * size + 1);
  tr.Build(1, 0, size - 1, arr, num);
  for (int i = 0; i < query_num; ++i) {
    std::array<int, 4> query;
    std::cin >> query[0] >> query[1] >> query[2] >> query[3];
    if (query[2] > num) {
      std::cout << 0 << '\n';
    } else {
      --query[0];
      --query[1];
      std::cout << tr.Get(1, 0, size - 1, query) << '\n';
    }
  }
  return 0;
}
