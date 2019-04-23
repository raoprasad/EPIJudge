#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include <unordered_map>

using namespace std;;
int iter = 0;
class LruCache {
private:
    struct LRUNode{
        int isbn;
        int price;
        LRUNode* next;
        LRUNode* prev;
        LRUNode(int _isbn, int _price): isbn(_isbn), price(_price), next(nullptr), prev(nullptr){}
    };
    unordered_map<int, LRUNode*> cache;
    LRUNode* head = nullptr;
    LRUNode* tail = nullptr;
    int capacity = 0;
public:
    LruCache(size_t capacity) {
        this->capacity = capacity;
    }
    int Lookup(int isbn) {
        if(cache.find(isbn) != cache.end()){
            LRUNode* curr = cache[isbn];
            if(head == curr) return curr->price;
            else curr->prev->next = curr->next;

            if(curr == tail) tail = curr->prev;
            else curr->next->prev = curr->prev;

            head->prev = curr;
            curr->next = head;
            curr->prev = nullptr;
            head = curr;
            return curr->price;
        }
        return -1;
}
    void Insert(int isbn, int price) {
        if(cache.find(isbn) != cache.end()){
            Lookup(isbn);
        }
        else{
            LRUNode* node = new LRUNode(isbn, price);
            if(cache.size() == capacity){
                Erase(tail->isbn);
            }
            if(head == nullptr){
                tail = node;
            }
            else{
                node->next = head;
                head->prev = node;
            }
            head = node;
            cache[isbn] = node;
        }
    }
    bool Erase(int isbn) {
        if(cache.find(isbn) == cache.end()) return false;
        LRUNode* curr = cache[isbn];
        cache.erase(curr->isbn);
        if(head == tail){
            head = tail = nullptr;
        }
        else if(head->next == tail){
            if(curr == head){
                head = curr->next;
                head->prev = nullptr;
            }
            else{
                tail = curr->prev;
                tail->next = nullptr;
            }
        }
        else{
            if(curr->prev != nullptr) curr->prev->next = curr->next;
            if(curr->next!= nullptr) curr->next->prev = curr->prev;
            if(curr == head) head = curr->next;
            if(curr == tail) tail = curr->prev;
        }
        delete curr;
        return true;
    }
};
struct Op {
  std::string code;
  int arg1;
  int arg2;
};

template <>
struct SerializationTraits<Op> : UserSerTraits<Op, std::string, int, int> {};

void RunTest(const std::vector<Op>& commands) {
  if (commands.empty() || commands[0].code != "LruCache") {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++) {
    auto& cmd = commands[i];
    if (cmd.code == "lookup") {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else if (cmd.code == "insert") {
      cache.Insert(cmd.arg1, cmd.arg2);
    } else if (cmd.code == "erase") {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"commands"};
  return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &RunTest,
                         DefaultComparator{}, param_names);
}
