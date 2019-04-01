#include <vector>
#include <unordered_map>
#include "test_framework/generic_test.h"

using namespace std;

int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores) {
	vector<vector<int>> combinations(individual_play_scores.size(), vector<int>(final_score + 1, 0));

	for(int row = 0; row < combinations.size(); row++ ){
		combinations[row][0] = 1;
	}

	for(int playid = 0; playid < individual_play_scores.size(); playid++){
		for(int targetscore = 1; targetscore <= final_score; targetscore++) {
			if(playid == 0){
				combinations[playid][targetscore] = (targetscore % individual_play_scores[playid] == 0)? 1 : 0;
				continue;
			}
			for(int multiple = 0; multiple <= targetscore/individual_play_scores[playid]; multiple++){
				combinations[playid][targetscore] += combinations[playid-1][targetscore - (multiple*individual_play_scores[playid])];
			}
		}
	}
	return combinations[individual_play_scores.size()-1][final_score];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
