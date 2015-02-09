#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

#include "constants.h"

using namespace std;

class sensor
{
    public:
        sensor(vector<vector<int > > m);
        vector<vector<int > > get_maze();
        int get_distance_to_wall(int px, int py, int dir);
        virtual ~sensor();
    protected:
    private:
        vector<vector<int > > maze;
};

#endif // SENSOR_H
