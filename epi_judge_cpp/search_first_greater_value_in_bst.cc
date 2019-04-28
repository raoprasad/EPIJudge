#include <memory>
#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

BstNode<int>* FindFirstGreaterThanK(const unique_ptr<BstNode<int>>& tree,
                                    int k) {
    BstNode<int>* curr = tree.get();
    BstNode<int>* successor = nullptr;

    while(curr != nullptr){
        if(curr->data == k){
            if(curr->right == nullptr) return successor;
            //successor is in the right subtree of this node
            successor = curr->right.get();
            while(successor->left != nullptr && successor->left->data > k){
                successor = successor->left.get();
            }
            return successor;
        }
        else if(curr->data < k){
            curr = curr->right.get();
        }
        else {
            successor = curr;
            curr = curr->left.get();
        }
    }
    return successor;
}
int FindFirstGreaterThanKWrapper(const unique_ptr<BstNode<int>>& tree, int k) {
  auto result = FindFirstGreaterThanK(tree, k);
  return result ? result->data : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "search_first_greater_value_in_bst.cc",
                         "search_first_greater_value_in_bst.tsv",
                         &FindFirstGreaterThanKWrapper, DefaultComparator{},
                         param_names);
}
