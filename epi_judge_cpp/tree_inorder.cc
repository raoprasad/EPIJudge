#include <memory>
#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <stack>
using namespace std;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
	stack<pair<BinaryTreeNode<int>*, bool>> stk;
	vector<int> res;
	if (tree == nullptr) return res;

	stk.push({ tree.get(), true });
	while (!stk.empty()) {
		auto cont = ref(stk.top());
		while (cont.get().first->left != nullptr && cont.get().second) {
			cont.get().second = false;
			auto next = make_pair(cont.get().first->left.get(), true );
			stk.push(next);
			cont = ref(stk.top());
		}
		
		res.emplace_back(cont.get().first->data);
		stk.pop();

		if (cont.get().first->right != nullptr) stk.push({ cont.get().first->right.get(), true });
	}
	return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
