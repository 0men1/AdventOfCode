#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

unordered_map<string, string> mult_cache;

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

    // Initial vector to store the input values
    vector<string> numbers;
    string line;
    
    // Read input into the vector
    while (getline(file, line))
    {
        stringstream ss(line);
        string word;
        while (ss >> word)
        {
            numbers.push_back(word);
        }
    }

    // Process the numbers for 75 iterations
    for (int i = 0; i < 75; ++i)
    {
        // Create a new vector for this iteration's results
        vector<string> next_iteration;
        // Reserve space to prevent reallocations
        next_iteration.reserve(numbers.size() * 2);

        // Process each number in order
        for (const string& value : numbers)
        {
            if (value == "0")
            {
                next_iteration.push_back("1");
            }
            else if (value.length() % 2 == 0)
            {
                int half = value.length() / 2;
                string fh = value.substr(0, half);
                string sh = value.substr(half, half);
                
                // Process first half
                size_t first_non_zero_fh = fh.find_first_not_of('0');
                if (first_non_zero_fh != string::npos)
                {
                    fh = fh.substr(first_non_zero_fh);
                }
                else
                {
                    fh = "0";
                }
                
                // Process second half
                size_t first_non_zero_sh = sh.find_first_not_of('0');
                if (first_non_zero_sh != string::npos)
                {
                    sh = sh.substr(first_non_zero_sh);
                }
                else
                {
                    sh = "0";
                }
                
                // Add both halves in order
                next_iteration.push_back(fh);
                next_iteration.push_back(sh);
            }
            else
            {
                if (mult_cache.find(value) != mult_cache.end()) {
                    next_iteration.push_back(mult_cache[value]);
                } else {
                    long long newVal = stoll(value);
                    newVal *= 2024;
                    string result = to_string(newVal);
                    mult_cache[value] = result;
                    next_iteration.push_back(result);
                }
            }
        }
        
        // Replace the old vector with the new one
        numbers = std::move(next_iteration);
        cout << i << endl;
    }

    cout << numbers.size() << endl;
    return 0;
}