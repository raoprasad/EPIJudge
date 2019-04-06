#include <iterator>
#include <string>
#include <vector>
#include <array>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using namespace std;

int ReplaceAndRemove(int size, char s[]) {
  if(size == 0) return 0;
  int newsize = size, additions = 0;
  int write = 0, read = 0;
  while(read < size) {
    if (s[read] == 'b'){
      read++;
      newsize--;
    }
    else if(s[read] == 'a'){
      swap(s[write++], s[read++]);
      additions++;
    }
    else{
      swap(s[write++], s[read++]);
    }
  }
  write = newsize + additions - 1, read = newsize - 1;
  while(read >= 0){
    swap(s[read--], s[write]);
    if(s[write] == 'a'){
      s[write] = s[write-1] = 'd';
      write -= 2;
    }else write--;
  }

  return newsize + additions;
}

vector<string> ReplaceAndRemoveWrapper(TimedExecutor& executor, int size,
                                       const vector<string>& s) {
  std::vector<char> s_copy(s.size(), '\0');
  for (int i = 0; i < s.size(); ++i) {
    if (!s[i].empty()) {
      s_copy[i] = s[i][0];
    }
  }

  int res_size =
      executor.Run([&] { return ReplaceAndRemove(size, s_copy.data()); });

  vector<string> result;
  for (int i = 0; i < res_size; ++i) {
    result.emplace_back(string(1, s_copy[i]));
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "size", "s"};
  return GenericTestMain(args, "replace_and_remove.cc",
                         "replace_and_remove.tsv", &ReplaceAndRemoveWrapper,
                         DefaultComparator{}, param_names);
}
