#include <istream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_set>
#include <functional>
#include <stack>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using namespace std;
typedef enum { kWhite, kBlack } Color;
struct Coordinate {
    Coordinate(int _x, int _y){
        this->x = _x;
        this->y = _y;
    }
    bool operator==(const Coordinate& that) const {
        return x == that.x && y == that.y;
    }

    int x, y;
};
class MyHash{
public:
    size_t operator()(Coordinate const& that) const noexcept{
        std::hash<int> x, y;
        return x(that.x) ^ (y(that.y) << 1);
    }
};
bool DFS(vector<vector<Color>>& maze, int row, int col, vector<Coordinate>& path, unordered_set<Coordinate, MyHash>& seen, const Coordinate& e){
    Coordinate cood(row,col);
    if(row > maze.size() - 1 || col > maze[0].size() - 1 || row < 0 || col < 0 || seen.find(cood) != seen.end() || maze[row][col] == 1) return false;

    seen.emplace(cood);
    path.emplace_back(cood);

    if(cood == e) return true;

    if(!DFS(maze, row, col+1, path, seen, e)){
        if(!DFS(maze, row+1, col, path, seen, e)) {
            if (!DFS(maze, row, col - 1, path, seen, e)) {
                if(!DFS(maze, row-1, col, path, seen, e)){
                    path.pop_back();
                    return false;
                }
            }
        }
    }
    return true;
}
vector<Coordinate> SearchMaze(vector<vector<Color>> maze, const Coordinate& s,
                              const Coordinate& e) {
    vector<Coordinate> path;
    unordered_set<Coordinate, MyHash> seen;
    DFS(maze, s.x,s.y,path,seen, e);
    return path;
}
template <>
struct SerializationTraits<Color> : SerializationTraits<int> {
  using serialization_type = Color;

  static serialization_type Parse(const std::string& str) {
    return static_cast<serialization_type>(
        SerializationTraits<int>::Parse(str));
  }

  static serialization_type JsonParse(const json_parser::Json& json_object) {
    return static_cast<serialization_type>(
        SerializationTraits<int>::JsonParse(json_object));
  }
};

template <>
struct SerializationTraits<Coordinate> : UserSerTraits<Coordinate, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {};
  }

  static std::vector<int> GetMetrics(const Coordinate& x) { return {}; }
};

bool PathElementIsFeasible(const vector<vector<Color>>& maze,
                           const Coordinate& prev, const Coordinate& cur) {
  if (!(0 <= cur.x && cur.x < maze.size() && 0 <= cur.y &&
        cur.y < maze[cur.x].size() && maze[cur.x][cur.y] == kWhite)) {
    return false;
  }
  return cur == Coordinate{prev.x + 1, prev.y} ||
         cur == Coordinate{prev.x - 1, prev.y} ||
         cur == Coordinate{prev.x, prev.y + 1} ||
         cur == Coordinate{prev.x, prev.y - 1};
}

bool SearchMazeWrapper(TimedExecutor& executor,
                       const vector<vector<Color>>& maze, const Coordinate& s,
                       const Coordinate& e) {
  vector<vector<Color>> copy = maze;

  auto path = executor.Run([&] { return SearchMaze(copy, s, e); });

  if (path.empty()) {
    return s == e;
  }

  if (!(path.front() == s) || !(path.back() == e)) {
    throw TestFailure("Path doesn't lay between start and end points");
  }

  for (size_t i = 1; i < path.size(); i++) {
    if (!PathElementIsFeasible(maze, path[i - 1], path[i])) {
      throw TestFailure("Path contains invalid segments");
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "maze", "s", "e"};
  return GenericTestMain(args, "search_maze.cc", "search_maze.tsv",
                         &SearchMazeWrapper, DefaultComparator{}, param_names);
}
