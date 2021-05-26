#include <bits/stdc++.h>
#include "agent.cpp"
using namespace std;
int main()
{
    int matrix[7][7] = {
        {1, 0, 0, 0, 0, 0, 2}, //0
        {0, 0, 2, 2, 0, 0, 0}, //1
        {0, 0, 2, 2, 0, 2, 0}, //2
        {0, 0, 0, 0, 0, 0, 0}, //3
        {2, 2, 2, 0, 0, 2, 2}, //4
        {0, 0, 0, 0, 0, 2, 2}, //5
        {0, 0, 2, 2, 0, 0, 0}  //6
    };
    position destination;
    destination.x = 6;
    destination.y = 6;
    Agent *ag = new Agent(0, 0);
    // print the matrix after each iteration
    int max_iter = 36;
    bool over = false;
    while (max_iter && !over)
    {
        matrix[ag->pos_t.x][ag->pos_t.y] = 0;
        scope *sc = (scope *)malloc(sizeof(scope));
        for (int x = 0; x < 5; x++)
        {
            for (int y = 0; y < 5; y++)
            {
                int ix = ag->pos_t.x - 2 + x;
                int iy = ag->pos_t.y - 2 + y;
                if (ix < 0 || iy < 0 || ix > 6 || iy > 6)
                {
                    sc->ar[x][y] = 4;
                }
                else
                {
                    sc->ar[x][y] = matrix[ix][iy];
                }
            }
        }
        sc->pos.x = ag->pos_t.x;
        sc->pos.y = ag->pos_t.y;
        ag->move(sc, destination);
        free(sc);
        matrix[ag->pos_t.x][ag->pos_t.y] = 1;
        max_iter--;
        for (int x = 0; x < 7; x++)
        {
            for (int y = 0; y < 7; y++)
            {
                cout << ((matrix[x][y] == 0) ? " " : (matrix[x][y] == 1 ? "V" : "X")) << " ";
            }
            cout << endl;
        }
    }
}