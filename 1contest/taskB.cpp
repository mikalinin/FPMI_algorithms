#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
  const int kPrecision = 10;
  int elems_num;
  int query_num;
  std::cin >> elems_num;
  std::vector<double> pref(elems_num);
  for (int i = 0; i < elems_num; i++) {
    double new_elem;
    std::cin >> new_elem;
    if (i == 0) {
      pref[i] = log(new_elem);
    } else {
      pref[i] = pref[i - 1] + log(new_elem);
    }
  }
  std::cin >> query_num;
  int left;
  int right;
  for (int i = 0; i < query_num; i++) {
    std::cin >> left >> right;
    if (left == 0) {
      std::cout << std::fixed << std::setprecision(kPrecision)
                << exp((1.0 / (right + 1)) * pref[right]) << std::endl;
    } else {
      std::cout << std::fixed << std::setprecision(kPrecision)
                << exp((1.0 / (right - left + 1)) *
                       (pref[right] - pref[left - 1]))
                << std::endl;
    }
  }
  return 0;
}
