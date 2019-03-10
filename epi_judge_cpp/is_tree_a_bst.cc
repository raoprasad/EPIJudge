#include <memory>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <vector>
using namespace std;

void traverse(const unique_ptr<BinaryTreeNode<int>>& tree, vector<int>& inorder) {
	if (tree == nullptr) return;
	traverse(tree->left, inorder);
	inorder.emplace_back(tree->data);
	traverse(tree->right, inorder);
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
	if (tree == nullptr) return true;
	vector<int> inorder;
	traverse(tree, inorder);
	for (int i = 0; i < inorder.size()-1; i++) {
		if (inorder[i] > inorder[i + 1]) return false;
	}
	return true;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
