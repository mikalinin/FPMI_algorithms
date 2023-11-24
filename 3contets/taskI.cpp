#include <bits/stdc++.h>
#define INT_MA 2000000000
#define MAX 25

struct Pair {
  int val;
  int ind;
};

bool Comp(Pair left, Pair right) { return left.val < right.val; }

int Query(int left, int right, std::vector<std::vector<Pair>>& st1,
          std::vector<std::vector<Pair>>& st2) {
  int ind = (int)log2(right - left + 1);
  std::vector<Pair> mas = {st2[left][ind], st1[left][ind],
                           st2[right - (1 << ind) + 1][ind],
                           st1[right - (1 << ind) + 1][ind]};
  std::sort(mas.begin(), mas.end(), Comp);
  if (mas[0].ind == mas[1].ind && mas[1].ind != mas[2].ind) {
    return mas[2].val;
  }
  if (mas[0].ind == mas[1].ind && mas[1].ind == mas[2].ind) {
    return mas[3].val;
  }
  return mas[1].val;
}

int main() {
  int arr_len;
  int query_num;
  std::cin >> arr_len >> query_num;
  std::vector<int> arr(arr_len);
  for (int i = 0; i < arr_len; ++i) {
    std::cin >> arr[i];
  }
  const int kSize = arr_len;
  std::vector<std::vector<Pair>> st1(kSize, std::vector<Pair>(MAX, Pair(0, 0)));
  for (int i = 0; i < arr_len; ++i) {
    st1[i][0] = Pair(arr[i], i);
  }
  for (int j = 1; (1 << j) <= arr_len; ++j) {
    for (int i = 0; (i + (1 << j) - 1) < arr_len; ++i) {
      if (st1[i][j - 1].val < st1[i + (1 << (j - 1))][j - 1].val) {
        st1[i][j] = st1[i][j - 1];
      } else {
        st1[i][j] = st1[i + (1 << (j - 1))][j - 1];
      }
    }
  }
  std::vector<std::vector<Pair>> st2(kSize, std::vector<Pair>(MAX, Pair(0, 0)));
  for (int i = 0; i < arr_len; ++i) {
    st2[i][0] = Pair(INT_MA, i);
  }
  for (int j = 1; (1 << j) <= arr_len; ++j) {
    for (int i = 0; (i + (1 << j) - 1) < arr_len; ++i) {
      std::vector<Pair> sr = {st2[i][j - 1], st2[i + (1 << (j - 1))][j - 1],
                              st1[i][j - 1], st1[i + (1 << (j - 1))][j - 1]};
      std::sort(sr.begin(), sr.end(), Comp);
      st2[i][j] = sr[1];
    }
  }
  for (int i = 0; i < query_num; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    if (right > arr_len) {
      right = arr_len;
    }
    std::cout << Query(left - 1, right - 1, st1, st2) << '\n';
  }
  return 0;
}
