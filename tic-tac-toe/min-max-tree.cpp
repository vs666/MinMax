#include <iostream>
#include <stdlib.h>

using namespace std;

#define UNASSIGNED 0
#define CROSS 1
#define ZERO -1

typedef struct grid
{
    int ar[3][3];
} grid;

grid *make_grid()
{
    grid *ob = (grid *)malloc(sizeof(grid));
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            ob->ar[x][y] = UNASSIGNED;
        }
    }
    return ob;
}

grid *make_grid(grid *prev)
{
    grid *ob = (grid *)malloc(sizeof(grid));
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            ob->ar[x][y] = prev->ar[x][y];
        }
    }
    return ob;
}

int calc_utility(grid *g, int player)
{
    // check for vertical and horizontial
    for (int x = 0; x < 3; x++)
    {
        if (g->ar[x][0] == player && g->ar[x][1] == player and g->ar[x][2] == player)
        {
            return 1;
        }
        if (g->ar[0][x] == player && g->ar[1][x] == player and g->ar[2][x] == player)
        {
            return 1;
        }
        if (g->ar[x][0] == -player && g->ar[x][1] == -player and g->ar[x][2] == -player)
        {
            return -1;
        }
        if (g->ar[0][x] == -player && g->ar[1][x] == -player and g->ar[2][x] == -player)
        {
            return -1;
        }
    }
    if (g->ar[0][0] == player && g->ar[1][1] == player && g->ar[2][2] == player)
    {
        return 1;
    }
    if (g->ar[0][2] == player && g->ar[1][1] == player && g->ar[2][0] == player)
    {
        return 1;
    }
    if (g->ar[0][0] == -player && g->ar[1][1] == -player && g->ar[2][2] == -player)
    {
        return -1;
    }
    if (g->ar[0][2] == -player && g->ar[1][1] == -player && g->ar[2][0] == -player)
    {
        return -1;
    }
    return 0;
}

pair<int, pair<int, int>> next_move(grid *g, int player, int dist)
{
    grid *cp_g = make_grid(g);
    int available_moves = 0;
    int ut_sum = 0;
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (cp_g->ar[x][y] == 0)
            {
                available_moves++;
            }
        }
    }
    pair<int, int> best_chance = {-1, -1};
    int best_util = -100; // random small value
    if (dist % 2 == 1)
    {
        best_util = 100;
    }
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (cp_g->ar[x][y] == 0)
            {
                cp_g->ar[x][y] = (available_moves % 2 == 0 ? ZERO : CROSS);
                int u = calc_utility(cp_g, player);
                if (available_moves != 1 && u == 0)
                {
                    auto var = next_move(cp_g, player, dist + 1);
                    u = var.first;
                }
                else if (u == -1 && dist == 1)
                {
                    return {-99, {x, y}};
                }
                cp_g->ar[x][y] = 0;
                // now check with max util so far

                if ((u > best_util and dist % 2 == 0) || (u < best_util and dist % 2 == 1))
                {
                    best_util = u;
                    best_chance = {x, y};
                }
            }
        }
    }
    delete (cp_g);
    if (best_util < 0)
    {
        best_util = -99;
    }
    return {best_util, best_chance};
}

void turing_play(grid *g, int p)
{
    auto re = next_move(g, p, 0);
    cout << "CPU Utility : " << re.first << endl;
    g->ar[re.second.first][re.second.second] = p;
}

void display(grid *g)
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            cout << (g->ar[x][y] == 1 ? 'X' : g->ar[x][y] == -1 ? 'O'
                                                                : '-')
                 << " ";
        }
        cout << endl;
    }
}
int main()
{
    grid *g = make_grid();
    // empty grid so far
    int ch;
    cout << "Enter player's choice : \n1 for X\n2 for O" << endl;
    cin >> ch;
    int player = 1;
    int chance_count = 0;
    if (ch == 2)
    {
        chance_count++;
        player = -1;
        turing_play(g, -player);
        display(g);
    }
    int turn = 1;
    while (calc_utility(g, player) == 0 && chance_count < 9)
    {
        chance_count += 1;
        if (turn)
        {
            int a = -1, b = -1;
            while (a < 0 or a > 2 or b < 0 or b > 2 or g->ar[a][b] != 0)
            {
                cout << "Enter play [x y] : ";
                cin >> a >> b;
            }
            g->ar[a][b] = player;
        }
        else
        {
            turing_play(g, -player);
        }
        display(g);
        turn = 1 - turn;
    }
    switch (calc_utility(g, player))
    {
    case 1:
        cout << "you win!!" << endl;
        break;
    case -1:
        cout << "computer wins!!" << endl;
        break;
    default:
        cout << "game draw!" << endl;
        break;
    }
}
