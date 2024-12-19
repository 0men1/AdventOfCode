#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<string, vector<string>> rules;
vector<vector<string>> sequences;

bool isInCorrectOrder(vector<string> sequence, string before, string after)
{
    int beforePos = -1, afterPos = -1;
    for (int i = 0; i < sequence.size(); ++i)
    {
        if (sequence[i] == before)
            beforePos = i;
        if (sequence[i] == after)
            afterPos = i;
    }

    if (beforePos == -1 || afterPos == -1)
        return true;

    return beforePos < afterPos;
}

bool validateSequence(vector<string> sequence)
{
    unordered_set<string> pages_(sequence.begin(), sequence.end());
    for (const auto &[before, afterPages] : rules)
    {
        if (pages_.find(before) == pages_.end())
            continue;

        for (const string &after : afterPages)
        {
            if (pages_.find(after) == pages_.end())
                continue;

            if (!isInCorrectOrder(sequence, before, after))
            {
                return false;
            }
        }
    }
    return true;
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
    bool parsingRules = true;  // Start by parsing rules section
    while (getline(file, line)) {
        // If we encounter an empty line, switch to parsing sequences
        if (line.empty()) {
            parsingRules = false;
            continue;
        }
        
        if (parsingRules) {
            // Parsing rules in X|Y format
            size_t pipePos = line.find('|');
            if (pipePos != string::npos) {
                string before = line.substr(0, pipePos);
                string after = line.substr(pipePos + 1);
                rules[before].push_back(after);
            }
        } else {
            // Parsing sequences in X,Y,Z format
            vector<string> sequence;
            string number;
            
            for (char c : line) {
                if (c == ',') {
                    if (!number.empty()) {
                        sequence.push_back(number);
                        number.clear();
                    }
                } else {
                    number += c;
                }
            }
            // Don't forget to add the last number
            if (!number.empty()) {
                sequence.push_back(number);
            }
            
            sequences.push_back(sequence);
        }
    }

    vector<vector<string>> valid;

    for (int i = 0; i < sequences.size(); ++i)
    {
        if (validateSequence(sequences[i]))
        {
            valid.push_back(sequences[i]);
        }
    }

    int result = 0;

    for(int i = 0; i < valid.size(); ++i) {
        int middle = stoi(valid[i][valid[i].size() / 2]);
        result += middle;
    }

    cout << result << endl;

    return 0;
}