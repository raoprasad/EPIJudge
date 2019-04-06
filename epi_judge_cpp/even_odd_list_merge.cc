#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
  auto thelist = L;
  if(L == nullptr) return thelist;

  auto evenguard = make_shared<ListNode<int>>(-1), oddguard = make_shared<ListNode<int>>(-1);
  auto curreven = evenguard, currodd = oddguard;

  while(thelist != nullptr){
    curreven->next = thelist;
    currodd->next = thelist->next;
    curreven = curreven->next;
    currodd = currodd->next;
    thelist = (thelist->next == nullptr)? nullptr : thelist->next->next;
  }
  curreven->next = oddguard->next;
  return evenguard->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
