#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int CountInversions(vector<int> A) {
    int size = A.size();
    if(size < 2) return 0;
    int inversions = 0;
    for(int i = 0; i < size-1; i++){
        for(int j = i+1; j < size; j++){
            if(A[i] > A[j]) inversions++;
        }
    }
    return inversions;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "count_inversions.cc", "count_inversions.tsv",
                         &CountInversions, DefaultComparator{}, param_names);
}
