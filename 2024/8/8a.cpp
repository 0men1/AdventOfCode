#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <sstream>
#include <vector>

using namespace std;


vector<string> scan;

unordered_map<char, vector<pair<int, int>>> antennas;

set<pair<int, int>> antinodes;

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
        scan.push_back(line);
    }

    int r = scan.size();
    int c = scan[0].size();

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            char v = scan[i][j];
            if (v != '.') {
                for (const auto& [x, y] : antennas[v]) {
                    int dx = x-i;
                    int dy = y-j;

                    int cx = i;
                    int cy = j;
                    while (cx >= 0 && cx < r && cy >= 0 && cy < c) {
                        antinodes.insert({cx, cy});
                        cx -= dx;
                        cy -= dy;
                    }
                    cx = x;
                    cy = y;
                    while (cx >= 0 && cx < r && cy >= 0 && cy < c) {
                        antinodes.insert({cx, cy});
                        cx += dx;
                        cy += dy;
                    }
                }
                antennas[v].push_back({i,j});
            }
        }
    }

    int ants = 0;
    for (const auto& [x, y] : antinodes) {
        if (x >= 0 && x < r && y >= 0 && y < c) {
            ants++;
        }
    }

    cout << ants << endl;

    return 0;
}
