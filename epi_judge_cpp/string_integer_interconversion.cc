#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
	bool negative = x < 0;
	//x = abs(x);
	if (x == 0) return (negative) ? "-0" : "0";
	string result = "";
	while (x != 0) {
		int mod = abs(x % 10);
		result += '0' + mod;
		x = x / 10;
	}
	if(negative) result += '-';
	std::reverse(result.begin(), result.end());
	return result;
}
int StringToInt(const string& s) {
	int result = 0;
	int len = s.length();
	for (int i = len - 1, pos = 0; i >= 0; i--, pos++) {
		if (i == 0 && (s[i] == '+' || s[i] == '-')) {
			if (s[i] == '-') result *= -1;
			break;
		}
		result += std::pow(10, pos) * (s[i] - '0');
	}
	return result;
}
void Wrapper(int x, const string& s) {
  if (IntToString(x) != s) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
