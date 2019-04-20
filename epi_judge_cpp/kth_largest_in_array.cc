#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

std::pair<int, int> partition(int pindex, int bindex, int eindex, vector<int>* A_ptr){
    vector<int>& A = *A_ptr;
    //zero based index expected.
    int pivotVal = A[pindex];
    int greater = bindex, curr = bindex, less = eindex;
    while(curr <= less){
        if(A[curr] == pivotVal){
            curr++;
        }
        else if(A[curr] < pivotVal){
            std::swap(A[curr], A[less--]);
        }
        else{
            std::swap(A[curr++], A[greater++]);
        }
    }
    return {greater, less};
}
// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    int begin = 0, end = A.size() - 1;
    do{
        int pivot = begin + (end - begin)/2;
        auto res = partition(pivot, begin, end, A_ptr);
        if(res.first <= k - 1  && res.second >= k-1) return A[k-1];
        else if(res.first > k - 1){
            end = res.first - 1;
        }
        else{
            begin = res.second + 1;
        }
    }
    while(begin <= end);
    return -1;
}
int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
