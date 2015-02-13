#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

#include "constants.h"

using namespace std;

struct cell
{
    int id;
    int visited;
    bool traversed;
    bool onPath;
    int px;
    int py;
    vector<int> neighbors;
    cell()
    {
      px = -1;
      py = -1;
      id = -1;
      visited = -1;
      traversed = false;
      onPath = false;
    }
    cell(int i, int x, int y) : id(i), px(x), py(y)
    {
      visited = -1;
      traversed = false;
      onPath = false;
    }
    cell(int i, int x, int y, int v) : id(i), px(x), py(y), visited(v)
    {
      traversed = false;
      onPath = false;
    }

    cell(int i, int x, int y, int v, vector<int> n) : id(i), px(x), py(y), visited(v), neighbors(n)
    {
      traversed = false;
      onPath = false;
    }

    bool operator==(cell& rhs)
    {
        return this->id == rhs.id;
    }
    bool operator==(const cell& rhs) const
    {
        return this->id == rhs.id;
    }
    bool operator!=(cell& rhs)
    {
        return this->id != rhs.id;
    }
};

struct instruction
{
    int command;
    int value;
    //command = 1 -> move forward, command = 2 -> rotate
    //value = (command) number of blocks to move forward, (rotate) number of 90* rotations
    instruction(int c, int v) : command(c), value(v) {}
    instruction()
    {
      command = -1;
      value = -1;
    }
};

ostream& operator<< (ostream &out, const cell &rhs);

class solver
{
    public:
        solver(int s, int x, int y, int d);
        vector<instruction> update_solver(int dleft, int dforward, int dright);
        vector<instruction> go_to_end();
        vector<instruction> go_to_start();
        void printCells();
        void printUnvisited();
        cell getCurrent();
        int getDirection();
        map<int, cell> getMaze();
        vector<int> getVisited();

        virtual ~solver();
    protected:
    private:
        map<int, cell> maze;
        vector<cell> path;
        vector<cell> unvisited;
        int direction;
        cell current;

        instruction generateRotateAmount(int c1, int c2);
        int getCellId(int x, int y);
        int parseDirection(int d);
        int parseX(int d);
        int parseY(int d);
        void resetCells();
        void findPath(cell start, cell finish);
        bool findInMaze(int x, int y);
        vector<instruction> generateInstructions();
        void findNeighbors(int dleft, int dforward, int dright);
        vector<cell> getNeighbors(cell c);
        void removeVisited();
        void updateVisited();
};

#endif // SOLVER_H
