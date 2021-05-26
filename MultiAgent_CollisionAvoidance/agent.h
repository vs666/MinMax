#ifndef __AGENT_H__
#define __AGENT_H__
#define FREE 0
#define AGENT 1
#define OBSTACLE 2

struct position
{
    int x;
    int y;
};

struct scope
{
    int ar[5][5];
    position pos;
};

class Agent
{
public:
    position pos_t;
    Agent::Agent(int x, int y);
    void Agent::move(scope *sc, position p);
    void Agent::tick();
private:
    bool HP_NW;
    int t_switch,t_elapsed;
    float Agent::distance_e(position p1,position p2);
    int Agent::distance_c(position p1,position p2);
    int Agent::distance_c(position p1,int a,int b);
    int Agent::distance_c(int a, int b, int c, int d);
    bool checkRule1(position p, scope *sc);
    bool checkRule2(position p, scope *sc);
    bool checkRule3(position p, scope *sc);
    bool checkRule4(position p, scope *sc);
};

#endif