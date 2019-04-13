#include "list_node.h"
#include "test_framework/generic_test.h"
#include <utility>
using namespace std;

pair<shared_ptr<ListNode<int>>, shared_ptr<ListNode<int>>> reverse(shared_ptr<ListNode<int>> startN, int count){
    shared_ptr<ListNode<int>> prev(nullptr);
    shared_ptr<ListNode<int>> next(nullptr);
    shared_ptr<ListNode<int>> curr = startN;
    while(count){
        count--;
        next = move(curr->next);
        curr->next = move(prev);
        prev = move(curr);
        curr = move(next);
    }
    return make_pair(prev, curr);
}

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
    if(L == nullptr || start <= 0) return L;
    shared_ptr<ListNode<int>> startN = L, prev(nullptr);
    int begin = start;
    while(--begin){
        prev = startN;
        startN = startN->next;
    }
    pair<shared_ptr<ListNode<int>>, shared_ptr<ListNode<int>>> res = reverse(startN, finish - start + 1);

    startN->next = res.second;
    if(prev != nullptr){
        prev->next = res.first;
    }

    return (prev == nullptr)? res.first : L;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
