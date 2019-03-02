#include <string>
#include "test_framework/generic_test.h"
#include <unordered_map>
using std::string;
std::unordered_map<int, unsigned long long> powers;

int maxPower(unsigned long long base10num, int b2) {
	int prevPower = 0;
	unsigned long long val = 1;
	for (int power = 0; val <= base10num;) {
		powers[power] = val;
		prevPower = power;
		power = (power == 0) ? 1 : power * 2;
		val = std::pow(b2, power);
	}
	int maxPower = prevPower * 2;
	while (prevPower < maxPower) {
		int currPower = prevPower + (maxPower - prevPower) / 2;
		unsigned long long currval = pow(b2, currPower);
		unsigned long long nextval = pow(b2, currPower + 1);
		if (currval == base10num) return currPower;
		else if (currval < base10num) {
			if (nextval > base10num) return currPower;
			else prevPower = currPower;
		}
		else maxPower = currPower;
	}
	return prevPower;
}
string ConvertBase(const string& num_as_string, int b1, int b2) {
	unsigned long long base10num = getBase10Num(num_as_string, b1);
	int maxpow = maxPower(base10num, b2);
	for()
}

int main(int argc, char* argv[]) {
  powers = std::unordered_map<int, unsigned long long>();
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
