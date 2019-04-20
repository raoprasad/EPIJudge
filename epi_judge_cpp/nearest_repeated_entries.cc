#include <string>
#include <vector>
#include "test_framework/generic_test.h"
#include <unordered_map>
using std::string;
using std::vector;
using namespace std;

int FindNearestRepetition(const vector<string>& paragraph) {
  int nearest = numeric_limits<int>::max();
  unordered_map<string, int> lastPositions;
  for(int i = 0; i < paragraph.size(); i++){
      string candidate = paragraph[i];
      if(lastPositions.find(candidate) != lastPositions.end()){
          nearest = min(nearest, i - lastPositions[candidate]);
      }
      lastPositions[candidate] = i;
  }
  return (nearest == numeric_limits<int>::max()) ? -1 : nearest;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
