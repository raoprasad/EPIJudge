#include <vector>
#include <cmath>
#include "test_framework/generic_test.h"
using std::vector;
using namespace std;

vector<int> MatrixInSpiralOrder(vector<vector<int>> square_matrix) {
  int n = square_matrix.size();
  int layers = ceil(n/2.0);

  vector<int> res;
  for(int l = 0; l < layers; l++){
    int r = l, c = l;
    do{
      res.emplace_back(square_matrix[r][c]);
      if(r == l && c < n-1-l) c++;
      else if(r == n-1-l && c > l) c--;
      else if(c == l && r > l)r--;
      else if(c == n-1-l && r < n-1-l)r++;

    }while(r != l || c != l);
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering_segments.cc",
                         "spiral_ordering_segments.tsv", &MatrixInSpiralOrder,
                         DefaultComparator{}, param_names);
}
