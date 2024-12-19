#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>

using namespace std;
vector<string> map_;

const vector<pair<int, int>> directions = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

pair<int, int> guardPos;
set<pair<int, int>> positions;

int solvePuzzle()
{
    int obstaclePositions = 0;
    int rows = map_.size();
    int cols = map_[0].size();
    int direction = 0;
    int i = guardPos.first;
    int j = guardPos.second;

    positions.insert({i, j});

    while (i >= 0 && i < rows && j >= 0 && j < cols)
    {
        int newI = i + directions[direction].first;
        int newJ = j + directions[direction].second;
        if (map_[newI][newJ] == '#')
        {
            if (direction == directions.size() - 1)
            {
                direction = 0;
            }
            else
            {
                direction++;
            }
        }
        else
        {
            i = newI;
            j = newJ;
            positions.insert({i, j});
        }
    }

    return positions.size()-1;
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
    while (getline(file, line))
    {
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '^')
            {
                guardPos = {map_.size(), i};
            }
        }
        map_.push_back(line);
    }

    cout << solvePuzzle() << endl;

    return 0;
}