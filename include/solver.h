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
    int id = -1;
    int visited = -1;
    bool traversed = false;
    bool onPath = false;
    int px = -1;
    int py = -1;
    vector<int> neighbors;
    cell() {}
    cell(int i, int x, int y) : id(i), px(x), py(y) {}
    cell(int i, int x, int y, int v) : id(i), px(x), py(y), visited(v) {}

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
    //command = 1 -> move forward, command = 2 -> rotate
    //value = (command) number of blocks to move forward, (rotate) number of 90* rotations
    instruction(int c, int v) : command(c), value(v) {}
    int command = -1;
    int value = -1;
};

ostream& operator<< (ostream &out, const cell &rhs);

class solver
{
    public:
        solver(int s, int x, int y, int d);
        vector<instruction> update_solver(int dleft, int dforward, int dright);
        int parseDirection(int d);
        int parseX(int d);
        int parseY(int d);
        instruction generateRotateAmount(int c1, int c2);
        void printCells();
        void printUnvisited();
        cell current;
        vector<cell> path;
        vector<cell> unvisited;
        int direction;
        map<int, cell> maze;
        virtual ~solver();
    protected:
    private:
        int getCellId(int x, int y);
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
