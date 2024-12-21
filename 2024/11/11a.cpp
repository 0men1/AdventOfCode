#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

vector<string> grid;

struct PathInfo
{
    vector<pair<int, int>> positions;
    vector<char> values;
};

vector<pair<int, int>> directions = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

int rows;
int cols;

map<pair<int, int>, int> scores;

void dfs(int row, int col, set<pair<int, int>> &visited, vector<pair<int, int>>& currentPath, vector<vector<pair<int, int>>> &allPaths)
{
    visited.insert({row, col});

    currentPath.push_back({row, col});

    if (grid[row][col] == '9') {
        allPaths.push_back(currentPath);
        scores[currentPath[0]]++;  // Store unique endpoint
    }

    for (const auto& [x, y] : directions) {
        int dx = row + x;
        int dy = col + y;


        if ((dx >= 0 && dx < rows && dy >= 0 && dy < cols)) {
            int valNew = grid[dx][dy] - '0';
            int val = grid[row][col] - '0';
            if (visited.find({dx, dy}) == visited.end() && (val+1 == valNew)) {
                dfs(dx, dy, visited, currentPath, allPaths);
            }
        }
    }

    visited.erase({row, col});
    currentPath.pop_back();
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Missing input text file";
        return 0;
    }
    ifstream file(argv[1]);
    if (!file.is_open())
    {
        cerr << "There was an error opening file";
        return 1;
    }
    string line;

    vector<string> map;

    while (getline(file, line))
    {
        grid.push_back(line);
    }

    set<pair<int, int>> visited;
    vector<pair<int, int>> currPath;
    vector<vector<pair<int, int>>> allPaths;

    rows = grid.size();
    cols = grid[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '0') dfs(i, j, visited, currPath, allPaths);
        }
    }

    int sumScores = 0;

    for (const auto& [p, n] : scores) {
        cout << p.first << ", " << p.second << ": " << n << endl;
        sumScores += n;
    }

    cout << sumScores << endl;

    return 0;
}