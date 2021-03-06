#include <stdexcept>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include <forward_list>
using std::length_error;

class Stack {
private:
	std::forward_list<int> nodes;
	std::forward_list<std::pair<int,int>> maxval;
public:
	bool Empty() const {
	// TODO - you fill in here.
		return nodes.empty();
	}
	int Max() const {
		return maxval.front().first;
	}
	int Pop() {
		int val = nodes.front();
		nodes.pop_front();
		if (maxval.front().first == val) {
			
			if (maxval.front().second == 1) {
				maxval.pop_front();
			}
			else {
				int& freq = maxval.front().second;
				freq--;
			}
		}
		return val;
	}
	void Push(int x) {
		nodes.emplace_front(x);
		if (!maxval.empty()) {
			std::pair<int, int>& currmax = maxval.front();
			if (currmax.first == x) currmax.second++;
			else if(currmax.first < x) maxval.emplace_front(std::make_pair(x, 1));
		}
		else maxval.emplace_front(std::make_pair(x,1));
	}
};
struct StackOp {
  std::string op;
  int argument;
};

template <>
struct SerializationTraits<StackOp> : UserSerTraits<StackOp, std::string, int> {
};

void StackTester(const std::vector<StackOp>& ops) {
  try {
    Stack s;
    for (auto& x : ops) {
      if (x.op == "Stack") {
        continue;
      } else if (x.op == "push") {
        s.Push(x.argument);
      } else if (x.op == "pop") {
        int result = s.Pop();
        if (result != x.argument) {
          throw TestFailure("Pop: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "max") {
        int result = s.Max();
        if (result != x.argument) {
          throw TestFailure("Max: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "empty") {
        int result = s.Empty();
        if (result != x.argument) {
          throw TestFailure("Empty: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else {
        throw std::runtime_error("Unsupported stack operation: " + x.op);
      }
    }
  } catch (length_error&) {
    throw TestFailure("Unexpected length_error exception");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "stack_with_max.cc", "stack_with_max.tsv",
                         &StackTester, DefaultComparator{}, param_names);
}
