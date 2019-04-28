#include <memory>
#include <vector>
#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

void PopulateLastKNodes(BstNode<int>* tree, vector<int>& res, int& curr, int k){
    if(tree->right != nullptr) PopulateLastKNodes(tree->right.get(), res, curr, k);
    if(curr < k ) res.emplace_back(tree->data);
    curr++;
    if(tree->left != nullptr) PopulateLastKNodes(tree->left.get(), res, curr, k);
}
vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
    int curr = 0;
    vector<int> res;
    PopulateLastKNodes(tree.get(), res, curr, k);
    return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         &UnorderedComparator<std::vector<int>>, param_names);
}
