#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  if(node0 == nullptr) return node1.get();
  else if(node1 == nullptr) return node0.get();

  int len0 = 0, len1 = 0;
  BinaryTreeNode<int>* temp = node0.get();
  while(temp->parent != nullptr){
    len0++;
    temp = temp->parent;
  }

  temp = node1.get();
  while(temp->parent != nullptr){
    len1++;
    temp = temp->parent;
  }

  BinaryTreeNode<int>* node0t = node0.get();
  while(len0 > len1){
    node0t = node0t->parent;
    len0--;
  }

  BinaryTreeNode<int>* node1t = node1.get();
  while(len1 > len0){
    node1t = node1t->parent;
    len1--;
  }

  while(node0t != nullptr && node1t != nullptr){
    if(node0t == node1t) return node0t;
    else{
      node0t = node0t->parent;
      node1t = node1t->parent;
    }
  }
  return nullptr;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return LCA(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
