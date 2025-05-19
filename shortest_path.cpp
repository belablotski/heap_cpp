/*
You are given a 2D grid representing a terrain. Each cell in the grid has an associated cost to traverse. 
You start at the top-left cell (0, 0) and want to reach the bottom-right cell (rows - 1, cols - 1). 
You can only move in four directions: up, down, left, or right.

Find the minimum total cost to travel from the start to the end cell.

Example:
grid = [
  [1, 3, 1],
  [1, 5, 1],
  [4, 2, 1]
]
The minimum cost path is (0, 0) -> (0, 1) -> (0, 2) -> (1, 2) -> (2, 2), with a total cost of 7.

See also https://github.com/belablotski/heap/blob/main/shortest_path.py
*/

#include <limits>
#include <iostream>
#include <queue>
#include <vector>

namespace PF {

using Matrix = std::vector<std::vector<int>>;
using Path = std::vector<std::pair<int, int>>;

class PathFinder {
public:
    explicit PathFinder(const Matrix& matrix) : _traverseCosts(matrix) { }

    Path findPath(int startRow, int startCol, int endRow, int endCol) {
        Path path;
        auto distances = calcDistances(startRow, startCol, endRow, endCol);
        std::cout << "Traverse costs:" << std::endl;
        print(_traverseCosts);
        std::cout << "Distances:" << std::endl;
        print(distances);
        return path;
    }

protected:
    Matrix calcDistances(int startRow, int startCol, int endRow, int endCol) {
        auto distances = Matrix(_traverseCosts.size(), std::vector<int>(_traverseCosts[0].size(), std::numeric_limits<int>::max()));
        calcDistancesRec(startRow, startCol, endRow, endCol, distances);
        return distances;
    }

    void calcDistancesRec(const int startRow, const int startCol, const int endRow, const int endCol, Matrix& distances) {
        std::queue<std::pair<int, int>> queue;
        queue.push({endRow, endCol});
        distances[endRow][endCol] = _traverseCosts[endRow][endCol];
        while (!queue.empty()) {
            auto p = queue.front();
            static const int dr[] = {-1, 1, 0, 0};
            static const int dc[] = {0, 0, -1, 1};
            for (int d = 0; d < 4; ++d) {
                int nr = p.first + dr[d];
                int nc = p.second + dc[d];
                if (nr >= 0 && nr < _traverseCosts.size() && nc >= 0 && nc < _traverseCosts[0].size()) {
                    int newDist = distances[p.first][p.second] + _traverseCosts[nr][nc];
                    if (newDist < distances[nr][nc]) {
                        distances[nr][nc] = newDist;
                        queue.push({nr, nc});
                    }
                }
            }
            queue.pop();
        }
    }

    void print(const Matrix& matrix) const {
        for (auto r : matrix) {
            for (auto c : r) {
                std::cout << c << "\t";
            }
            std::cout << std::endl;
        }
    }

private:
    const Matrix& _traverseCosts;
};

std::ostream& operator<<(std::ostream& o, Path path) {
    for (auto p : path) {
        o << "[" << p.first << "," << p.second << "]" << (&p == &path.back() ? "" : " -> ");
    }
    o << std::endl;
    return o;
}

}

using PF::operator<<;

int main() {
    PF::Matrix matrix = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    auto pathFinder = PF::PathFinder(matrix);
    auto path = pathFinder.findPath(0, 0, matrix.size()-1, matrix.size()-1);
    std::cout << path; 
    return 0;
}