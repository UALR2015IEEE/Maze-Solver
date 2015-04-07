#include "../include/sensor.h"

sensor::sensor(map<int, cell> m)
{
    maze = m;
}

sensor::~sensor()
{
    //dtor
}

map<int, cell> sensor::get_maze()
{
    return maze;
}

data* sensor::get_distances(cell c, DIRECTION dir)
{
    data* d = new data();
    d->left = get_distance_to_wall(c, dir-1);
    d->forward = get_distance_to_wall(c, dir);
    d->right = get_distance_to_wall(c, dir+1);
    return d;
}

int sensor::get_distance_to_wall(cell c, int dir)
{
    //directions - 0=up, 1=right, 2=down, 3=left
    if(dir < 0) dir = 3;
    if(dir > 3) dir = 0;
    cell current = maze.find(c.id)->second;
    int cx = current.px;
    int cy = current.py;

    for(vector<int>::iterator it = current.neighbors.begin(); it != current.neighbors.end(); ++it)
    {
      int nx = maze.find(*it)->second.px;
      int ny = maze.find(*it)->second.py;
      if (dir == UP )
      {
        if ( ny < cy && nx == cx)
        {
          //cout << "cell up" << endl;
          return 1;
        }
      }
      else if ( dir == RIGHT )
      {
        if ( nx > cx && ny == cy)
        {
          //cout << "cell right" << endl;
          return 1;
        }
      }
      else if ( dir == DOWN )
      {
        if ( ny > cy && nx == cx)
        {
          //cout << "cell down" << endl;
          return 1;
        }
      }
      else if ( dir == LEFT )
      {
        if ( nx < cx && ny == cy)
        {
          //cout << "cell left" << endl;
          return 1;
        }
      }
    }
    return 0;
}
