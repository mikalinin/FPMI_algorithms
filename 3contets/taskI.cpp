#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#define INT_MA 2000000000

struct Pair {
  int val;
  int ind;
};

bool Comp(Pair left, Pair right) { return left.val < right.val; }

class Sparse {
  std::vector<std::vector<Pair>> st1_;
  std::vector<std::vector<Pair>> st2_;
  int size_ = 0;

public:
  Sparse(int size) {
    size_ = size;
    st1_.resize(size,
                std::vector<Pair>(static_cast<int>(log2(size)), Pair(0, 0)));
    st2_.resize(size,
                std::vector<Pair>(static_cast<int>(log2(size)), Pair(0, 0)));
  }
  ~Sparse() {
    for (auto& i : st1_) {
      i.clear();
    }
    for (auto& i : st2_) {
      i.clear();
    }
  };
  void Sparse1(std::vector<int>& arr) {
    for (int i = 0; i < size_; ++i) {
      st1_[i][0] = Pair(arr[i], i);
    }
    for (int j = 1; (1 << j) <= size_; ++j) {
      for (int i = 0; (i + (1 << j) - 1) < size_; ++i) {
        if (st1_[i][j - 1].val < st1_[i + (1 << (j - 1))][j - 1].val) {
          st1_[i][j] = st1_[i][j - 1];
        } else {
          st1_[i][j] = st1_[i + (1 << (j - 1))][j - 1];
        }
      }
    }
  }

  void Sparse2() {
    for (int i = 0; i < size_; ++i) {
      st2_[i][0] = Pair(INT_MA, i);
    }
    for (int j = 1; (1 << j) <= size_; ++j) {
      for (int i = 0; (i + (1 << j) - 1) < size_; ++i) {
        std::vector<Pair> sr = {st2_[i][j - 1], st2_[i + (1 << (j - 1))][j - 1],
                                st1_[i][j - 1],
                                st1_[i + (1 << (j - 1))][j - 1]};
        std::sort(sr.begin(), sr.end(), Comp);
        st2_[i][j] = sr[1];
      }
    }
  }

  int Query(int left, int right) {
    int ind = static_cast<int>(log2(right - left + 1));
    std::vector<Pair> mas = {st2_[left][ind], st1_[left][ind],
                             st2_[right - (1 << ind) + 1][ind],
                             st1_[right - (1 << ind) + 1][ind]};
    std::sort(mas.begin(), mas.end(), Comp);
    if (mas[0].ind == mas[1].ind && mas[1].ind != mas[2].ind) {
      return mas[2].val;
    }
    if (mas[0].ind == mas[1].ind && mas[1].ind == mas[2].ind) {
      return mas[3].val;
    }
    return mas[1].val;
  }
};

int main() {
  int arr_len;
  int query_num;
  std::cin >> arr_len >> query_num;
  std::vector<int> arr(arr_len);
  for (int i = 0; i < arr_len; ++i) {
    std::cin >> arr[i];
  }
  Sparse st(arr_len);
  st.Sparse1(arr);
  st.Sparse2();
  for (int i = 0; i < query_num; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    if (right > arr_len) {
      right = arr_len;
    }
    std::cout << st.Query(left - 1, right - 1) << '\n';
  }
  return 0;
}
