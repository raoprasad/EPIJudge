#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

void Sum(const unique_ptr<BinaryTreeNode<int>>& tree, int num, int& sum) {
	if (tree == nullptr) return;

	num << 1;
	num |= tree->data;

	if (tree->left == nullptr && tree->right == nullptr) {
		sum += num;
	}
	Sum(tree->left, num, sum);
	Sum(tree->right, num, sum);
}

int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>>& tree) {
	int sum = 0;
	Sum(tree, 0, sum);
	return sum;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "sum_root_to_leaf.cc", "sum_root_to_leaf.tsv",
                         &SumRootToLeaf, DefaultComparator{}, param_names);
}
