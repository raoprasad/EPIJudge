#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
std::pair<bool, int> balanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
	if (tree == nullptr) return std::make_pair(true, 0);
	else if (tree->left == nullptr && tree->right == nullptr) return std::make_pair(true, 1);
	else {
		std::pair<bool, int> left = balanced(tree->left);
		if (!left.first) return std::make_pair(false, -1);
		std::pair<bool, int> right = balanced(tree->right);
		if (!right.first) return std::make_pair(false, -1);
		return (abs(left.second - right.second) <= 1) ? std::make_pair(true, (left.second >= right.second) ? left.second + 1 : right.second + 1) : std::make_pair(false, -1);
	}
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
	return balanced(tree).first;
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
