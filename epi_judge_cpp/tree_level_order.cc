#include <memory>
#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <queue>
using namespace std;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
    vector<vector<int>> res;
    if(tree == nullptr) return res;

    queue<BinaryTreeNode<int>*> thislevel, nextlevel;
    thislevel.push(tree.get());
    vector<int> temp;
    while(!thislevel.empty()){
        BinaryTreeNode<int>* curr = move(thislevel.front()); thislevel.pop();
        temp.emplace_back(curr->data);
        if(curr->left != nullptr) nextlevel.push(curr->left.get());
        if(curr->right != nullptr) nextlevel.push(curr->right.get());

        if(thislevel.empty()){
            res.emplace_back(temp);
            temp.clear();
            thislevel.swap(nextlevel);
        }
    }

    return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
