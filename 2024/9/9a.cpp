#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <sstream>
#include <vector>
using namespace std;
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
    vector<string> diskmap;
    int id = 0;
    while (getline(file, line))
    {
        bool isFile = true;
        for (int i = 0; i < line.length(); i++) {
            int v = line[i] - '0';
            if (isFile) {
                for (int j = 0; j < v; j++) {                    diskmap.push_back(to_string(id));
                }
                id++;
                isFile = false;
            } else {
                for (int j = 0; j < v; j++) {
                    diskmap.push_back(".");
                }
                isFile = true;
            }
        }
    }

    // Fixed movement logic
    int left = 0;
    int right = diskmap.size() - 1;
    
    while (left < right) {
        // Find leftmost empty space
        while (left < diskmap.size() && diskmap[left] != ".") {
            left++;
        }
        // Find rightmost file
        while (right >= 0 && diskmap[right] == ".") {
            right--;
        }
        
        if (left < right) {  // Only swap if left hasn't caught up to right
            diskmap[left] = diskmap[right];
            diskmap[right] = ".";
            left++;
            right--;
        }
    }

    // Calculate checksum
    long long sum = 0;
    for (int i = 0; i < diskmap.size(); ++i) {
        if (diskmap[i] != ".") {
            sum += (stoi(diskmap[i]) * i);
        }
    }
    cout << sum << endl;
    return 0;
}