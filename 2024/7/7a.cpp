#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

bool backtrack(vector<int> nums, int pos, long long target, long long currentValue)
{
    if (pos == nums.size() - 1)
    {
        return currentValue == target;
    }

    if (backtrack(nums, pos + 1, target, currentValue + nums[pos + 1]))
    {
        return true;
    }

    if (backtrack(nums, pos + 1, target, currentValue * nums[pos + 1]))
    {
        return true;
    }

    return false;
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

    long long total = 0;

    string line;
    while (getline(file, line))
    {
        size_t colonPos = line.find(':');
        long long target = stoll(line.substr(0, colonPos));

        stringstream s(line.substr(colonPos + 1));
        int num;
        vector<int> nums;
        while (s >> num)
        {
            nums.push_back(num);
        }

        if (backtrack(nums, 0, target, nums[0]))
        {
            total += target;
        }
    }

    cout << total << endl;

    return 0;
}
