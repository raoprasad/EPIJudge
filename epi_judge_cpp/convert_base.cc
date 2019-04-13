#include <string>
#include "test_framework/generic_test.h"
#include <unordered_map>
using namespace std;

static unordered_map<char, int> decimalMap({{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}
												   , {'9', 9}, {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}});
static unordered_map<int, char> hexMap({{0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}
												   , {9, '9'}, {10, 'A'}, {11, 'B'}, {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'}});

unsigned long int computePower(int base, int power){
	unsigned long int val = 1;

    while(power){
        if(power & 1){
            if(val > numeric_limits<unsigned long>::max()/base) return -1;
            val *= base;
            power ^= 1;
        }
        else{
            power >>= 1;
            base *= base;
        }
    }

	return val;
}

int getBase10Num(string num, int b1){
	int res = 0;
	for(int i = num.length() - 1; i >= 0; i--){
		res += computePower(b1,num.length() - 1 - i) * decimalMap[num[i]];
	}
	return res;
}

pair<int, int> maxPower(unsigned long base10num, int b2) {
    if(base10num == 1 || base10num < b2) return {0,1};
    int power = 1;
    unsigned long val = b2;
    while(val <= base10num/b2){
        power++;
        val *= b2;
    }
    return {power, val};
}
string ConvertBase(const string& num_as_string, int b1, int b2) {
    bool neg = false;
    string num = num_as_string;
    if(num_as_string[0] == '-'){
        neg = true;
        num = num.substr(1);
    }
	unsigned long long base10num = getBase10Num(num, b1);
    string result = "";
    int prevPow = -1;
	while( base10num > 0 ){
        pair<int, int> maxpow = maxPower(base10num, b2);
        if(prevPow > 0){
            while(--prevPow > maxpow.first){
                result += '0';
            }
        }
        prevPow = maxpow.first;
        result += hexMap[base10num/maxpow.second];
        base10num %= maxpow.second;
	}
    if(prevPow > 0){
        while(--prevPow >= 0){
            result += '0';
        }
    }
    if(result.empty()) result = "0";
	return (neg)? "-" + result: result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
