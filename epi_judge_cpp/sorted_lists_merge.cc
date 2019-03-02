#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
	if (L1 == nullptr) return L2;
	else if (L2 == nullptr) return L1;

	shared_ptr<ListNode<int>> guard = shared_ptr<ListNode<int>>(new ListNode<int>(-1));
	shared_ptr<ListNode<int>> result(guard);
	while (L1 != nullptr || L2 != nullptr) {
		if (L1 == nullptr) {
			result->next = L2;
			break;
		}
		else if (L2 == nullptr) {
			result->next = L1;
			break;
		}

		if (L1->data <= L2->data) {
			result->next = L1;
			result = result->next;
			L1 = L1->next;
		}
		else {
			result->next = L2;
			result = result->next;
			L2 = L2->next;
		}
	}
	return guard->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
