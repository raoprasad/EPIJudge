#include <algorithm>
#include <cmath>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_utils.h"
#include <queue>
using namespace std;

struct Star {
  bool operator<(const Star& that) const {
    return Distance() < that.Distance();
  }

  double Distance() const { return sqrt(x * x + y * y + z * z); }

  double x, y, z;
};

class compare{
public:
    bool operator()(const Star& lhs, const Star& rhs){
        return lhs < rhs;
    }
};

vector<Star> FindClosestKStars(vector<Star>::const_iterator stars_begin,
                               const vector<Star>::const_iterator& stars_end,
                               int k) {
    priority_queue<Star, vector<Star>, function<bool(const Star& lhs, const Star& rhs)>> q(
            [](const Star& lhs, const Star& rhs)->bool{return lhs < rhs;}
            );
    vector<Star>::const_iterator begin = stars_begin;
    vector<Star> kclosest;
    if(k == 0 || stars_begin == stars_end) return kclosest;

    while(k-- && begin != stars_end){
        q.emplace(*begin);
        ++begin;
    }

    while(begin != stars_end){
        if(*begin < q.top()){
            q.pop();
            q.emplace(*begin);
        }
        begin++;
    }

    while(!q.empty()){
        kclosest.emplace_back(q.top());
        q.pop();
    }
    return kclosest;
}
template <>
struct SerializationTraits<Star> : UserSerTraits<Star, double, double, double> {
};

std::ostream& operator<<(std::ostream& out, const Star& s) {
  return out << s.Distance();
}

bool Comp(const vector<double>& expected, vector<Star> output) {
  if (output.size() != expected.size()) {
    return false;
  }

  std::sort(begin(output), end(output));

  for (int i = 0; i < output.size(); ++i) {
    if (!DefaultComparator()(output[i].Distance(), expected[i])) {
      return false;
    }
  }
  return true;
}

vector<Star> FindClosestKStarsWrapper(const vector<Star>& stars, int k) {
  return FindClosestKStars(cbegin(stars), cend(stars), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stars", "k"};
  return GenericTestMain(args, "k_closest_stars.cc", "k_closest_stars.tsv",
                         &FindClosestKStarsWrapper, &Comp, param_names);
}
