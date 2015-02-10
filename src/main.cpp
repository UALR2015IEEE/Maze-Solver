#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "../include/sensor.h"
#include "../include/solver.h"

using namespace std;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

std::vector<std::string> split(const std::string &s, char delim);

template<typename T>
ostream& operator<< (ostream& out, const vector<T>& v);

template<typename T>
bool load_maze(string name, vector<vector<T > >& maze);

int main()
{
    //initialize maze vector
    vector<vector<int > > maze;
    
    //initialize maze
    if(!load_maze("maze.txt", maze))
    {
        cout << "Error loading maze." << endl;
        return -1;
    }

    //set current position
    int px = 0;
    int py = 1;

    //directions - 0=up, 1=right, 2=down, 3=left
    int dir = 1;
    int startId = 0;

    sensor *maze_sensor = new sensor(maze);
    solver *maze_solver = new solver(startId, px, py, dir);
    int left;
    int straight;
    int right;

    maze_sensor->get_maze();

    vector<instruction> i;

    do
    {

        dir = maze_solver->direction;
        px = maze_solver->current.px;
        py = maze_solver->current.py;

        left = maze_sensor->get_distance_to_wall(px, py, dir-1);
        straight = maze_sensor->get_distance_to_wall(px, py, dir);
        right = maze_sensor->get_distance_to_wall(px, py, dir+1);

        i = maze_solver->update_solver(left, straight, right);

    }
    while(!i.empty());

    maze_solver->printCells();
    cout << maze_solver->maze.size() << endl;
    delete maze_sensor;
    delete maze_solver;

    return 0;
}
template<typename T>
bool load_maze(string name, vector<vector<T > >& maze)
{
    cout << "Loading maze" << endl;
    ifstream maze_file;
    string line;

    //open maze file
    maze_file.open(name.c_str());

    //prepopulate maze vector
    if(maze_file.is_open())
    {
        while( getline (maze_file, line))
        {
            vector<string> x = split(line, ',');
            maze.push_back(vector<T >());
            maze.back().resize(x.size());
        }
        maze_file.close();
    }
    else return false;

    cout << "maze allocated." << endl;

    maze_file.open(name.c_str());
    //load maze into maze vector
    if(maze_file.is_open())
    {
        int y = 0;
        while( getline (maze_file, line))
        {
            vector<string> x = split(line, ',');

            for (unsigned int i=0; i<x.size(); i++)
            {
                istringstream buffer(x[i]);
                buffer >> maze[i][y];
            }
            y++;
        }
        maze_file.close();
    }
    else return false;

    return true;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
