#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

#include "constants.h"
#include "solver.h"

using namespace std;

class sensor
{
    public:
        sensor(map<int, cell> m);
        map<int, cell> get_maze();
        int get_distance_to_wall(cell c, int dir);
        virtual ~sensor();
    protected:
    private:
        map<int, cell> maze;
};

#endif // SENSOR_H
