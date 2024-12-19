#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>

using namespace std;
vector<string> map_;

const vector<pair<int, int>> directions = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

pair<int, int> guardPos;

int solvePuzzle()
{
    int obstaclePositions = 0;
    int rows = map_.size();
    int cols = map_[0].size();

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {

            if (map_[row][col] != '.' || (row == guardPos.first && col == guardPos.second))
            {
                continue;
            }

            vector<string> tempMap = map_;
            tempMap[row][col] = '#';

            int direction = 0;
            int i = guardPos.first;
            int j = guardPos.second;
            set<pair<pair<int, int>, int>> visited;

            while (i >= 0 && i < rows && j >= 0 && j < cols)
            {
                auto state = make_pair(make_pair(i, j), direction);

                if (visited.find(state) != visited.end())
                {
                    obstaclePositions++;
                    break;
                }

                visited.insert(state);

                int newI = i + directions[direction].first;
                int newJ = j + directions[direction].second;
                if (tempMap[newI][newJ] == '#')
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
                }
            }
            cout << row << ", " << col << endl;
        }
    }

    return obstaclePositions;
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