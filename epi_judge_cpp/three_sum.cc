#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

bool hasTwoSum(vector<int> A, int t) {
  int begin = 0, end = A.size()-1;
  while(begin <= end){
    int sum = A[begin] + A[end];
    if(sum == t) return true;
    else if(sum < t) begin++;
    else end--;
  }
  return false;
}

bool HasThreeSum(vector<int> A, int t) {
  sort(A.begin(), A.end());
  for(int a : A){
    if(hasTwoSum(A, t-a)) return true;
  }
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "three_sum.cc", "three_sum.tsv", &HasThreeSum,
                         DefaultComparator{}, param_names);
}
