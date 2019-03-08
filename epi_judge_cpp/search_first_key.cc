#include <vector>
#include "test_framework/generic_test.h"
using std::vector;


//Test case 1:
//[],10

//Test case 2:
//[10, 10, 10], 10

//Test case 3:
//[1,2,2,3,4,4,4,5,6,7,7,7,7,8], 7
//int SearchFirstOfK(const vector<int>& A, int k) {
//	int begin = 0, end = A.size();
//	while (begin < end) {
//		int mid = (end + begin) >> 1;
//		if (A[mid] == k) {
//			int i = mid;
//			while (begin < mid) {
//				i = (begin + mid) >> 1;
//				if (A[i] == k) {
//					mid = i;
//				}
//				else if (A[i] < k) {
//					begin = i + 1;
//				}
//			}
//			return mid;
//		}
//		else if (A[mid] > k) {
//			end = mid;
//		}
//		else begin = mid + 1;
//	}
//	return -1;
//}

int SearchFirstOfK(const vector<int>& A, int k) {
	int begin = 0, end = A.size();
	int index = -1;
	while (begin < end) {
		int mid = (begin + end) >> 1;
		if (A[mid] == k) {
			index = mid;
			end = mid;
		}
		else if (A[mid] > k) {
			end = mid;
		}
		else begin = mid + 1;
	}
	return index;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
