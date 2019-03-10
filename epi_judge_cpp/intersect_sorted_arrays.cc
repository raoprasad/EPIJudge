#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
	vector<int> res;
	if (A.empty() || B.empty()) return res;
	int a = 0, b = 0, alen = A.size(), blen = B.size();

	while (a < alen || b < blen) {
		if (a == alen || b == blen) break;
		if (A[a] == B[b]) {
			res.emplace_back(A[a]);
			int curr = A[a];
			while (++a < alen && A[a] == curr);
			while (++b < blen && B[b] == curr);
		}
		else if (A[a] < B[b]) {
			a++;
		}
		else {
			b++;
		}
	}

	return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
