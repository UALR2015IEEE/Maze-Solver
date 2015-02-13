#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

#include "../include/sensor.h"
#include "../include/solver.h"

using namespace std;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

std::vector<std::string> split(const std::string &s, char delim);

template<typename T>
ostream& operator<< (ostream& out, const vector<T>& v);

bool load_maze(string name, map<int, cell>& maze);

int toInt(string s);
int findMaxX(map<int, cell> maze);
int findMaxY(map<int, cell> maze);

void updateMaze(vector<vector< string > >& str_maze, map<int, cell> maze, vector<int> visited, cell current);
void initMaze(vector<vector< string > >& str_maze, map<int, cell> maze);
void printMaze(vector<vector< string > > str_maze, map<int, cell> maze);

int main()
{
    //initialize maze vector
    map<int, cell> maze;

    //initialize maze
    if(!load_maze("maze.txt", maze))
    {
        cout << "Error loading maze." << endl;
        return -1;
    }

    vector<vector< string > > str_maze;
    initMaze(str_maze, maze);

    //set current position
    int px = 1;
    int py = 0;

    //directions - 0=up, 1=right, 2=down, 3=left
    int dir = 2;
    int id = 48;

    sensor *maze_sensor = new sensor(maze);
    solver *maze_solver = new solver(id, px, py, dir);

    int left;
    int straight;
    int right;
    cell current;

    vector<instruction> i;

    do
    {

        dir = maze_solver->getDirection();
        current = maze.find(maze_solver->getCurrent().id)->second;

        left = maze_sensor->get_distance_to_wall(current, dir-1);
        straight = maze_sensor->get_distance_to_wall(current, dir);
        right = maze_sensor->get_distance_to_wall(current, dir+1);

        //cout << "current: " << current;
        //maze_solver->printUnvisited();
        //cout << "\n\n--------------------------------------" << endl;

        updateMaze(str_maze, maze_solver->getMaze(), maze_solver->getVisited(), current);
        printMaze(str_maze, maze);

        cout << "dir: " << dir << endl;
        cout << "left: " << left << " straight: " << straight << " right: " << right << endl << endl;;

        i = maze_solver->update_solver(left, straight, right);

    }
    while(!i.empty());

    cout << "PATHING TO END OF MAZE: " << endl;
    i = maze_solver->go_to_end();
    current = maze.find(maze_solver->getCurrent().id)->second;
    updateMaze(str_maze, maze_solver->getMaze(), maze_solver->getVisited(), current);
    printMaze(str_maze, maze);

    
    cout << "\n\nPATHING TO BEGINNING OF MAZE: " << endl;
    i = maze_solver->go_to_start();
    current = maze.find(maze_solver->getCurrent().id)->second;
    updateMaze(str_maze, maze_solver->getMaze(), maze_solver->getVisited(), current);
    printMaze(str_maze, maze);

    //maze_solver->printCells();
    //cout << maze_solver->getMaze().size() << endl;
    //maze_solver->printUnvisited();

    delete maze_sensor;
    delete maze_solver;

    return 0;
}

int findMaxX(map<int, cell> maze)
{
  int result = 0;
  for(map<int, cell>::iterator it = maze.begin(); it != maze.end(); ++it)
  {
    cell c = it->second;
    if (c.px > result) result = c.px;
  }
  return result*2+1;
}

int findMaxY(map<int, cell> maze)
{
  int result = 0;
  for(map<int, cell>::iterator it = maze.begin(); it != maze.end(); ++it)
  {
    cell c = it->second;
    if (c.py > result) result = c.py;
  }
  return result*2+1;
}

void printMaze(vector<vector< string > > str_maze, map<int, cell> maze)
{
  int mX = findMaxX(maze);
  int mY = findMaxY(maze);
  for(unsigned int y = 0; y < mY; y++)
  {
    for(unsigned int x = 0; x < mX; x++)
    {
      cout << str_maze[y][x] << " ";
    }
    cout << endl;
  }
}

void initMaze(vector<vector< string > >& str_maze, map<int, cell> maze)
{
  int mX = findMaxX(maze);
  int mY = findMaxY(maze);
  for(unsigned int y = 0; y < mX; y++)
  {
    str_maze.push_back(vector<string>());
    for(unsigned int x = 0; x < mY; x++)
    {
      str_maze[y].push_back(" ");
    }
  }
}

void updateMaze(vector<vector< string > >& str_maze, map<int, cell> maze, vector<int> visited, cell current)
{
  for(map<int, cell>::iterator it = maze.begin(); it != maze.end(); ++it)
  {
    cell c = it->second;
    str_maze[c.py*2][c.px*2] = 'o';
    for(vector<int>::iterator nit = c.neighbors.begin(); nit != c.neighbors.end(); ++nit)
    {
      cell neighbor = maze.find(*nit)->second;
      if (neighbor.px > c.px && neighbor.py == c.py)
      {
        str_maze[c.py*2][c.px*2+1] = '-';
      }
      if (neighbor.px < c.px && neighbor.py == c.py)
      {
        str_maze[c.py*2][c.px*2-1] = '-';
      }
      if (neighbor.py > c.py && neighbor.px == c.px)
      {
        str_maze[c.py*2+1][c.px*2] = '|';
      }
      if (neighbor.py < c.py && neighbor.px == c.px)
      {
        str_maze[c.py*2-1][c.px*2] = '|';
      }
    }
  }

  for(vector<int>::iterator it = visited.begin(); it != visited.end(); ++it)
  {
    cell c = maze.find(*it)->second;
    str_maze[c.py*2][c.px*2] = 'x';
  }

  str_maze[current.py*2][current.px*2] = 'c';

}

int toInt(string s)
{
  char *buffer=new char[s.size()+1];
  buffer[s.size()]=0;
  memcpy(buffer,s.c_str(),s.size());
  return atoi(buffer);
}

bool load_maze(string name, map<int, cell>& maze)
{
  cout << "Loading maze." << endl;
  ifstream maze_file;
  string line;

  //open maze file
  maze_file.open(name.c_str());

  if(maze_file.is_open())
  {
    while( getline(maze_file, line))
    {
      vector<string> x = split(line, ':');

      int cid = toInt(x[0]);

      int cpy = 0;
      int cpx = 0;

      while( ((6-cpy)*7)+(6-cpx)+1 != cid )
      {
        cpx += 1;
        if ( cpx > 6 )
        {
          cpy += 1;
          cpx = 0;
        }
      }

      vector<string> y = split(x[1], ',');

      vector<int> neighbors;

      for(vector<string>::iterator it = y.begin(); it != y.end(); ++it)
      {
        neighbors.push_back(toInt(*it));
      }

      maze.insert(pair<int, cell>(cid, cell(cid, cpx, cpy, 0, neighbors)));
    }
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
