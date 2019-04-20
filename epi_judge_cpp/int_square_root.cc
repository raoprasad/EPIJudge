#include "test_framework/generic_test.h"

int SquareRoot(int k) {
  if(k < 2) return k;
  int begin = 1, end = k/2 + 1, sqr = 1;
  long long curr = 1, prd = 1;

  while(begin < end){
      curr = begin + (end - begin)/2;
      prd = curr*curr;
      if(prd == k){
          return curr;
      }
      else if(prd < k){
          sqr = curr;
          begin = curr + 1;
      }
      else{
          end = curr;
      }
  }
  return sqr;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
