#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<string, vector<string>> rules;
vector<vector<string>> sequences;
vector<vector<string>> fixedSequences;

void dfs(const string &node, unordered_map<string, vector<string>> &graph, unordered_set<string> &visited, unordered_set<string> &inProgress, stack<string> &result)
{
    if (inProgress.count(node)) {
        return;
    }

    if (visited.count(node)) {
        return;
    }

    inProgress.insert(node);

    if (graph.count(node)) {
        for (const string& next : graph[node]) {
            dfs(next, graph, visited, inProgress, result);
        }
    }

    inProgress.erase(node);
    visited.insert(node);
    result.push(node);
}

vector<string> fixSequeunce(vector<string> &sequence)
{
    unordered_map<string, vector<string>> graph;
    unordered_set<string> nodes(sequence.begin(), sequence.end());

    for (const auto &[before, afterList] : rules)
    {
        for (const string &after : afterList)
        {
            if (nodes.count(before) && nodes.count(after))
            {
                graph[before].push_back(after);
            }
        }
    }

    unordered_set<string> visited;
    unordered_set<string> inProgress;
    stack<string> sortResult;

    for (const string &node : nodes)
    {
        if (!visited.count(node))
        {
            dfs(node, graph, visited,inProgress, sortResult);
        }
    }

    vector<string> result;
    while(!sortResult.empty()) {
        result.push_back(sortResult.top());
        sortResult.pop();
    }

    return result;
}

bool validateSequence(vector<string> sequence)
{
    unordered_set<string> pages_(sequence.begin(), sequence.end());
    for (const auto &[before, afterPages] : rules)
    {
        for (const string &after : afterPages)
        {
            auto beforeIt = find(sequence.begin(), sequence.end(), before);
            auto afterIt = find(sequence.begin(), sequence.end(), after);

            if (beforeIt != sequence.end() && afterIt != sequence.end())
            {
                if (beforeIt > afterIt)
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
    bool parsingRules = true;
    while (getline(file, line))
    {
        if (line.empty())
        {
            parsingRules = false;
            continue;
        }

        if (parsingRules)
        {
            size_t pipePos = line.find('|');
            if (pipePos != string::npos)
            {
                string before = line.substr(0, pipePos);
                string after = line.substr(pipePos + 1);
                rules[before].push_back(after);
            }
        }
        else
        {
            vector<string> sequence;
            string number;

            for (char c : line)
            {
                if (c == ',')
                {
                    if (!number.empty())
                    {
                        sequence.push_back(number);
                        number.clear();
                    }
                }
                else
                {
                    number += c;
                }
            }
            if (!number.empty())
            {
                sequence.push_back(number);
            }

            sequences.push_back(sequence);
        }
    }

    vector<vector<string>> invalid;
    int middleSum = 0;

    for (int i = 0; i < sequences.size(); ++i)
    {
        if (!validateSequence(sequences[i]))
        {
            vector<string> fixed = fixSequeunce(sequences[i]);

            int middle = fixed.size() / 2;
            middleSum += stoi(fixed[middle]);
        }
    }

    cout << middleSum << endl;


    return 0;
}