#include <bits/stdc++.h>

using namespace std;
#define FLOAT_MIN -9999999.0

typedef map<string, map<string, string>> matrix;

matrix transition;
map<string, int> utility;
vector<string> actions;
vector<string> states;
vector<string> final_states;
vector<float> weight;
int depth;
int k = -1;

float tof(string s)
{
    bool isNeg = false;
    if (s[0] == '-')
    {
        isNeg = true;
    }
    float ret = 0, pnmf = 10, exp = 1;
    for (int x = (isNeg ? 1 : 0); x < s.length(); x++)
    {
        if (s[x] == '.')
        {
            pnmf = 1;
            exp = 0.1;
            continue;
        }
        int n = (int)(s[x] - '0');
        ret = ret * pnmf;
        ret += exp * n;
        if (pnmf == 1)
        {
            exp *= 0.1;
        }
    }
}

// input function
void input(string filename)
{
    string line;
    ifstream InFile(filename);
    while (getline(InFile, line))
    {
        if (line[0] == 's')
        {
            stringstream line_str(line.substr(2, line.length()));
            string st = "";
            while (getline(line_str, st, ' '))
            {
                states.push_back(st);
            }
        }
        else if (line[0] == 'a')
        { // actions should be after states, before transition
            stringstream line_str(line.substr(2, line.length()));
            string st = "";
            while (getline(line_str, st, ' '))
            {
                actions.push_back(st);
            }

            // initialization of transition function
            for (auto s : states)
            {
                transition[s] = map<string, string>();
                for (auto a : actions)
                {
                    transition[s][a] = "-";
                }
            }
        }
        else if (line[0] == 'u')
        {
            stringstream line_str(line.substr(2, line.length()));
            string st = "";
            int index = 0;
            while (getline(line_str, st, ' '))
            {
                utility[states[index++]] = tof(st);
            }
        }
        else if (line[0] == 't')
        { // like :t from_state action_to_take to_state
            stringstream line_str(line.substr(2, line.length()));
            string st = "";
            string from, to, act;
            int index = 0;
            while (getline(line_str, st, ' '))
            {
                if (index == 0)
                {
                    from = st;
                }
                else if (index == 1)
                {
                    act = st;
                }
                else if (index == 2)
                {
                    to = st;
                }
                index++;
            }
            transition[from][act] = to; // shouldn't throw errors as initialization is already done
        }
        else if (line[0] == 'f')
        {
            // no need of final state arrays. final states are those which have entire row of transition matrix as '-'.
        }
    }
}

float calculate_utility(string state, int d)
{
    if (d >= depth)
    {
        return 0;
    }
    // make sure no out of bounds because this will give runtime error otherwise
    int util = weight[d] * utility[state];
    if (d % 2 == 1)
    {
        util *= k; // more effort on minimizing loss
    }
    for (auto act : actions)
    {
        util += calculate_utility(transition[state][act], d + 1);
    }
    return util;
}

string get_action(string state)
{
    float max_util = FLOAT_MIN;
    string selected_action = "-";
    for (auto action : actions)
    {
        if (transition[state][action][0] != '-')
        {
            // transition possible
            float util = calculate_utility(transition[state][action], 0);
            if (util > max_util)
            {
                max_util = util;
                selected_action = action;
            }
        }
    }
    return selected_action;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "ERROR:: INVALID NUMBER OF ARGUMENTS\n";
        exit(1);
    }
    input(argv[1]); // filename in argv[1]
    char ch = 'y';
    while (ch != 'x')
    {
        cout << "Enter State : ";
        string st;
        cin >> st;
        cout << "Best action is : " << get_action(st) << endl;
        cout << "Press 'x' to exit, anything else otherwise" << endl;
        cin >> st;
        ch = st[0];
    }
    return 0;
}