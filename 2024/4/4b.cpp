#include <iostream>
#include <fstream>
#include <map>

using namespace std;

vector<string> word_search;
string word = "MAS";

map<pair<int, int>, int> xMatches;

const vector<pair<int, int>> directions = {
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

void beginSearch()
{
    int rows = word_search.size();
    int cols = word_search[0].size();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            for (const auto &[dx, dy] : directions)
            {
                int endX = i + ((word.length() - 1) * dx);
                int endY = j + ((word.length() - 1) * dy);

                if (endX >= 0 && endX < cols && endY >= 0 && endY < rows)
                {
                    bool match = true;
                    pair<int, int> aIndex = {-1, -1};

                    for (int k = 0; k < word.length(); k++)
                    {
                        int currX = i + k * dx;
                        int currY = j + k * dy;

                        if (word_search[currX][currY] != word[k])
                        {
                            match = false;
                            break;
                        }

                        if (word_search[currX][currY] == word[k] && word[k] == 'A') {
                            aIndex = {currX, currY};
                        }
                    }
                    if (match)
                    {
                        xMatches[aIndex]++;
                    }
                }
            }
        }
    }
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
    string fullString;
    while (getline(file, line))
    {
        word_search.push_back(line);
    }

    beginSearch();
    int count = 0;

    for (const auto& m : xMatches) {
        if (m.second == 2) {
            count++;
        }
    }

    cout << count << endl;

    return 0;
}