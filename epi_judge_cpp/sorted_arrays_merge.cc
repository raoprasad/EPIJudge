#include <vector>
#include "test_framework/generic_test.h"
#include <unordered_map>
using namespace std;
//vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
//	map<int, int> map;
//	for (vector<int> array : sorted_arrays) {
//		for (int element : array) {
//			map[element]++;
//		}
//	}
//	vector<int> res;
//	for (pair<int, int> entry : map) {
//		for (int i = 0; i < entry.second; i++) {
//			res.emplace_back(entry.first);
//		}
//	}
//	return res;
//}
vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
	unordered_map<int, int> map;
	for (vector<int> array : sorted_arrays) {
		for (int element : array) {
			map[element]++;
		}
	}
	vector<int> res;
	priority_queue<pair<int, int>, vector<pair<int, int>>, function<bool(const pair<int, int>&, const pair<int, int>&)>> q(map.begin(), map.end(), [](const pair<int, int>& lhs, const pair<int, int>& rhs)->bool {
		return lhs.first > rhs.first;
	});

	while(!q.empty()) {
		pair<int, int> entry = q.top(); q.pop();
		for (int i = 0; i < entry.second; i++) {
			res.emplace_back(entry.first);
		}
	}
	return res;
}
int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
