#include <memory>
#include <vector>
#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

void findSize(BstNode<int>* tree, int& size){
    if(tree->left != nullptr) findSize(tree->left.get(), size);
    size++;
    if(tree->right != nullptr) findSize(tree->right.get(), size);
}
void PopulateLastKNodes(BstNode<int>* tree, vector<int>& res, int size, int& curr, int k){
    if(tree->left != nullptr) PopulateLastKNodes(tree->left.get(), res, size, curr, k);
    curr++;
    if(curr >= size - k + 1) res.emplace_back(tree->data);
    if(tree->right != nullptr) PopulateLastKNodes(tree->right.get(), res, size, curr, k);
}
vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
    int size = 0, curr = 0;
    findSize(tree.get(), size);

    vector<int> res;

    PopulateLastKNodes(tree.get(), res, size, curr, k);
    return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         &UnorderedComparator<std::vector<int>>, param_names);
}
