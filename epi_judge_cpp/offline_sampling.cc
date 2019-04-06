#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
#include <random>
#include <unordered_set>
using namespace std;
using std::bind;
using std::vector;
void RandomSampling(int k, vector<int>* A_ptr) {
  vector<int>& A = (*A_ptr);
  vector<int> res;
  unordered_set<int> seen;
  // obtain a seed from the system clock:
  unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
  mt19937 g1 (seed1);
  uniform_int_distribution<int> distribution(0,A.size()-1);
  while(k){
    int randomIndex = distribution(g1);
    if(seen.count(randomIndex) > 0) continue;
    seen.emplace(randomIndex);
    k--;
    res.emplace_back(A[randomIndex]);
  }
  A.swap(res);
}
bool RandomSamplingRunner(TimedExecutor& executor, int k, vector<int> A) {
  vector<vector<int>> results;

  executor.Run([&] {
    for (int i = 0; i < 100000; ++i) {
      RandomSampling(k, &A);
      results.emplace_back(begin(A), begin(A) + k);
    }
  });

  int total_possible_outcomes = BinomialCoefficient(A.size(), k);
  sort(begin(A), end(A));
  vector<vector<int>> combinations;
  for (int i = 0; i < BinomialCoefficient(A.size(), k); ++i) {
    combinations.emplace_back(ComputeCombinationIdx(A, A.size(), k, i));
  }
  vector<int> sequence;
  for (vector<int> result : results) {
    sort(begin(result), end(result));
    sequence.emplace_back(
        distance(begin(combinations),
                 find(begin(combinations), end(combinations), result)));
  }
  return CheckSequenceIsUniformlyRandom(sequence, total_possible_outcomes,
                                        0.01);
}

void RandomSamplingWrapper(TimedExecutor& executor, int k,
                           const vector<int>& A) {
  RunFuncWithRetries(
      bind(RandomSamplingRunner, std::ref(executor), k, std::cref(A)));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "k", "A"};
  return GenericTestMain(args, "offline_sampling.cc", "offline_sampling.tsv",
                         &RandomSamplingWrapper, DefaultComparator{},
                         param_names);
}
