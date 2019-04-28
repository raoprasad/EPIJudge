#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int CountInversions(vector<int> A) {
    if(A.size() <= 1) return 0;
    int mid = A.size()/2;
    vector<int> left(A.begin(), A.begin()+mid), right(A.begin()+mid, A.end());

    int inversions = CountInversions(left);
    inversions += CountInversions(right);
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int leftId = 0, rightId = 0;
    while(leftId < left.size() && rightId < right.size()){
        if(left[leftId] > right[rightId] ){
            inversions += left.size() - leftId;
            rightId++;
        }
        else leftId++;
    }
    return inversions;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "count_inversions.cc", "count_inversions.tsv",
                         &CountInversions, DefaultComparator{}, param_names);
}
