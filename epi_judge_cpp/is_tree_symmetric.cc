#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool symmetric(const unique_ptr<BinaryTreeNode<int>>& left, const unique_ptr<BinaryTreeNode<int>>& right) {
	if (left == nullptr && right == nullptr) return true;
	else if (left == nullptr || right == nullptr) return false;
	else if (left->data != right->data) return false;
	else return symmetric(left->left, right->right) && symmetric(left->right, right->left);
}
bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
	if (tree == nullptr) return true;
	else return symmetric(tree->left, tree->right);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
