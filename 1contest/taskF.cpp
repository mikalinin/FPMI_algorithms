#include <iostream>
#include <vector>

int QuickSelect(std::vector<int>& elems, int stat, int elem_num, int left,
                int right) {
  if (left > right) {
    return elems[left];
  }
  int mid = elems[left];
  int first_uk = left;
  int second_uk = right;
  while (first_uk <= second_uk) {
    while (elems[first_uk] < mid) {
      ++first_uk;
    }
    while (elems[second_uk] > mid) {
      --second_uk;
    }
    if (first_uk <= second_uk) {
      int buffer_elem = elems[first_uk];
      elems[first_uk] = elems[second_uk];
      elems[second_uk] = buffer_elem;
      ++first_uk;
      --second_uk;
    }
  }
  if ((first_uk - left) >= stat) {
    return QuickSelect(elems, stat, elem_num, left, second_uk);
  }
  return QuickSelect(elems, stat - (first_uk - left), elem_num, first_uk,
                     right);
}

int main() {
  const int kA45 = 45;
  const int kA123 = 123;
  const int kA10000000 = 10000000;
  const int kA4321 = 4321;
  int elem_num;
  int stat;
  int elem1;
  int elem2;
  std::cin >> elem_num >> stat >> elem1 >> elem2;
  std::vector<int> elems(elem_num, 0);
  elems[0] = elem1;
  elems[1] = elem2;
  for (int i = 2; i < elem_num; ++i) {
    elems[i] = ((elems[i - 2] * kA45) + (elems[i - 1] * kA123)) %
               (kA10000000 + kA4321);
  }
  int ans;
  ans = QuickSelect(elems, stat, elem_num, 0, elem_num - 1);
  std::cout << ans;
  return 0;
}
