#include "test_framework/generic_test.h"
short Parity(unsigned long long x) {
	long long mask = 0xFFFFFFFF;
	unsigned int len = 32;
	while (len) {
		unsigned int num1 = x & mask;
		unsigned int num2 = (x >> len) & mask;
		x = num1 ^ num2;
		len = len / 2;
		mask = mask >> len;
	}
	return x;
}
int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "x" };
	return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
		DefaultComparator{}, param_names);
}