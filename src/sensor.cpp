#include "../include/sensor.h"

sensor::sensor(vector<vector<int > > m)
{
    maze = m;
}

sensor::~sensor()
{
    //dtor
}

vector<vector<int > > sensor::get_maze()
{
    return maze;
}

int sensor::get_distance_to_wall(int px, int py, int dir)
{
    if(dir < 0) dir = 4+dir;
    if(dir > 3) dir = 0;

    //directions - 0=up, 1=right, 2=down, 3=left
    int distance = -1;
    if (dir == UP)
    {
        cout << "py: " << py << " px: " << px << endl;
        while (py >= 0 && maze[px][py] != 1)
        {
            py--;
            distance++;
        }
    }
    else if (dir == RIGHT)
    {
        while (px < maze.size() && maze[px][py] != 1)
        {
            px++;
            distance++;
        }
    }
    else if (dir == DOWN)
    {
        while (py < maze.size() && maze[px][py] != 1)
        {
            py++;
            distance++;
        }
    }
    else if (dir == LEFT)
    {
        while (px >= 0 && maze[px][py] != 1)
        {
            px--;
            distance++;
        }
    }

    return distance;

}
