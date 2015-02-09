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

void update_maze(vector<vector< string > >& maze, vector<cell> path, vector<cell> unvisited);

int main()
{
    //initialize maze vector
    vector<vector<int > > maze;
    vector<vector<string > > str_maze;

    //initialize maze
    if(!load_maze("maze.txt", maze) || !load_maze("maze.txt", str_maze))
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

    cout << maze_sensor->get_maze() << endl;
    cout << str_maze << endl;

    cout << "distance left " << left << endl;
    cout << "distance forward " << straight << endl;
    cout << "distance right " << right << endl;

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

        update_maze(str_maze, maze_solver->path, maze_solver->unvisited);

        cout << "maze updated" << endl;
        cout << str_maze << endl;
        cout << "left: " << left << endl;
        cout << "straight: " << straight << endl;
        cout << "right: " << right << endl;
        cout << "\nPX: " << px << " PY: " << py << " dir: " << dir << endl;
        cout << "instruction: " << endl;

        for(vector<instruction>::iterator it = i.begin(); it != i.end(); ++it)
        {
            cout << it->command << " " << it->value << endl;
        }

        //cout << "-------------------------\n" << endl;

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
                maze[i][y] = stoi(x[i]);
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

template<typename T>
ostream& operator<< (ostream& out, const vector<T>& v)
{
    size_t last = v.size() - 1;
    for(size_t i = 0; i < v.size(); ++i)
    {
        for(size_t j = 0; j < v[i].size(); ++j)
        {
            out << v[j][i];
            if (j != last)
                out << " ";
            else
                out << "\n";
        }
    }
    out << "\n";
    return out;
}

void update_maze(vector<vector< string > >& maze, vector<cell> path, vector<cell> unvisited)
{
    if(!path.empty())
    {
        for (vector<cell>::iterator it = path.begin(); it != path.end(); ++it)
        {
            maze[it->px][it->py] = "x";
        }
        for (vector<cell>::iterator it = unvisited.begin(); it != unvisited.end(); ++it)
        {
            maze[it->px][it->py] = "o";
        }
        maze[path.back().px][path.back().py] = "c";
    }
}
