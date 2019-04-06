#include "test_framework/generic_test.h"
#include <map>
using namespace std;

double Power(double x, int y) {
  cout << "Input num = " << x << " and input power = " << y << endl;
  bool neg = (y < 0);
  y = abs(y);
  double ans = 1.0;
  map<int, double> powers({{1, x}});
  for(int i = 2; i <= y; i *= 2){
    powers[i] = powers[i/2] * powers[i/2];
  }

  for (map<int, double>::reverse_iterator iter  = powers.rbegin();
       iter != powers.rend(); ++iter ) {
    if(y >= (*iter).first){
      ans *= (*iter).second;
      y -= (*iter).first;
    }
  }

  return (neg)? 1/ans:ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}
