#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

double BuyAndSellStockOnce(const vector<double>& prices) {
	double maxprofit = 0.0, currprofit = 0.0;
	int numdays = prices.size();
	for (int sellday = 1; sellday <= numdays - 1; sellday++) {
		currprofit = std::max(currprofit + prices[sellday] - prices[sellday -1], 0.0);
		maxprofit = std::max(currprofit, maxprofit);
	}
	return maxprofit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
