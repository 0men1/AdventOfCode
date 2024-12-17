#include <iostream>
#include <fstream>

using namespace std;

// xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))

vector<pair<int, int> > mults;


bool checkParentheses(int i, string s)
{
    if (s[i] != '(')
    {
        return false;
    }

    if (s.length() - i < 5)
    {
        return false;
    }

    int firstArg;

    int j = i + 1;
    while (isdigit(s[j])) {
        j++;
    }
    firstArg = atoi(s.substr(i + 1, j - i - 1).c_str());

    if (s[j] != ',') {
        return false;
    }


    int secondArg;
    i = j;
    j++;
    while(isdigit(s[j])) {
        j++;
    }

    secondArg = atoi(s.substr(i + 1, j - i - 1).c_str());

    if (s[j] != ')') {
        return false;
    }

    mults.push_back(make_pair(firstArg, secondArg));

    return true;
}

bool checkMul(string s)
{
    for (int i = 0; i < s.length() - 3; i++)
    {
        if (s.substr(i, 3) == "mul")
        {
            checkParentheses(i + 3, s);
        }
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

    string line;
    string fullString;
    while (getline(file, line))
    {
        fullString += line;
    }

    checkMul(fullString);

    int result = 0;

    for (int i = 0; i < mults.size(); ++i) {
        result += (mults[i].first * mults[i].second);
    }

    file.close();

    cout << result << endl;

    return result;
}