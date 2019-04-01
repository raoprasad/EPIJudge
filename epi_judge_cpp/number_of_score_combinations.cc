#include <vector>
#include <unordered_map>
#include "test_framework/generic_test.h"

using namespace std;

int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores) {
	set<int> individualScores(individual_play_scores.begin(), individual_play_scores.end());
	vector<int> combinations(final_score + 1, 0);
	unordered_map<int, set<set<int>>> uniqPlays;

	combinations[0] = 1;
	uniqPlays.emplace(0,set<set<int>>({{}}));

	for(int score = 1; score <= final_score; score++){
		set<set<int>> temp;
		for(int currPlay : individual_play_scores){
			if(score >= currPlay && combinations[score-currPlay] > 0){
				for(set<int> currset : uniqPlays[score - currPlay]){
					set<int> curr(currset.begin(), currset.end());
					curr.emplace(currPlay);
					if(temp.find(curr) == temp.end()){
						combinations[score] += 1;
						temp.emplace(curr);
					}
				}
			}
		}
		uniqPlays.emplace(score, temp);
	}
	return combinations[final_score];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
