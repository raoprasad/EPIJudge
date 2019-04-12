#include "list_node.h"
#include "test_framework/generic_test.h"

pair<ListNode<int>*, ListNode<int>*> reverse(ListNode<int>* startN, int count){
    ListNode<int>* prev = nullptr;
    ListNode<int>* curr = startN;
    while(count){
        count--;
        ListNode<int>* next = curr->next.get();
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return {curr, next};
}

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
    if(L == nullptr) return L;
    ListNode<int>* startN = L.get(), prev = nullptr;
    int begin = start;
    while(--begin){
        prev = startN;
        startN = startN->next.get();
    }
    pair<ListNode<int>*, ListNode<int>*> res = reverse(startN, finish - start + 1);

    startN->next = make_shared(res.second);
    if(prev != nullptr){
        prev->next = make_shared(res.first);
    }

    return (prev == nullptr)? make_shared(res.first) : L;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
