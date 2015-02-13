#include "solver.h"

solver::solver(int s, int x, int y, int d)
{
    //cstor
    direction = d;
    maze.insert(pair<int, cell>(s, cell(s, x, y, 1)));
    current = maze[s];
}

solver::~solver()
{
    //dstor
}

cell solver::getCurrent()
{
  return current;
}

map<int, cell> solver::getMaze()
{
  return maze;
}

int solver::getDirection()
{
  return direction;
}

vector<int> solver::getVisited()
{
  vector<int> visited;
  for(map<int, cell>::iterator it = maze.begin(); it != maze.end(); ++it)
  {
    cell current = it->second;
    for(vector<int>::iterator nit = current.neighbors.begin(); nit != current.neighbors.end(); ++nit)
    {
      cell neighbor = maze.find(*nit)->second;
      if(neighbor.visited > 0)
      {
        visited.push_back(*nit);
      }
    }
  }
  return visited;
}

int solver::parseDirection(int d)
{
    int toReturn = (direction+d)%4;
    if (toReturn < 0) return 4+toReturn;
    else return toReturn;
}

int solver::parseX(int d)
{
    if (direction == UP && d == -1) return -1;
    if (direction == UP && d == 1) return 1;
    if (direction == DOWN && d == -1) return 1;
    if (direction == DOWN && d == 1) return -1;
    if (direction == RIGHT && d == 0) return 1;
    if (direction == LEFT && d == 0) return -1;
    return 0;
}

int solver::parseY(int d)
{
    if (direction == LEFT && d == -1) return 1;
    if (direction == LEFT && d == 1) return -1;
    if (direction == RIGHT && d == -1) return -1;
    if (direction == RIGHT && d == 1) return 1;
    if (direction == UP && d == 0) return -1;
    if (direction == DOWN && d == 0) return 1;
    return 0;
}

bool solver::findInMaze(int x, int y)
{
    for (map<int, cell>::iterator it = maze.begin(); it != maze.end(); it++)
    {
        if (it->second.px == x && it->second.py == y) return true;
    }
    return false;
}

void solver::findNeighbors(int dleft, int dforward, int dright)
{
    //directions - 0=up, 1=right, 2=down, 3=left
    //cout << "direction: " << direction << endl;
    int cx = current.px;
    int cy = current.py;
    int ci = current.id;
    if(dleft > 0 || dforward > 0 || dright > 0)
    {
        bool left = findInMaze(cx+parseX(-1), cy+parseY(-1));
        bool straight = findInMaze(cx+parseX(0), cy+parseY(0));
        bool right = findInMaze(cx+parseX(1), cy+parseY(1));

        cell toInsert;
        int id;
        int x;
        int y;
        if(dleft > 0 && !left)
        {
            //cout << "space left" << endl;
            //cout << "space direction: " << parseDirection(-1) << endl;
            x = cx+parseX(-1);
            y = cy+parseY(-1);
            //id = maze.size();
            id = getCellId(x, y);
            //cout << "X: " << x << " Y: " << y << " ID: " << id << endl;
            toInsert = cell(id, x, y, 0);
            toInsert.neighbors.push_back(ci);
            maze.insert(pair<int, cell>(id, toInsert));
            maze.find(ci)->second.neighbors.push_back(id);
            unvisited.push_back(toInsert);
        }
        if(dforward > 0 && !straight)
        {
            //cout << "space forward" << endl;
            //cout << "space direction: " << parseDirection(0) << endl;
            x = cx+parseX(0);
            y = cy+parseY(0);
            //id = maze.size();
            id = getCellId(x, y);
            //cout << "X: " << x << " Y: " << y << " ID: " << id << endl;
            toInsert = cell(id, x, y, 0);
            toInsert.neighbors.push_back(ci);
            maze.insert(pair<int, cell>(id, toInsert));
            maze.find(ci)->second.neighbors.push_back(id);
            unvisited.push_back(toInsert);
        }
        if(dright > 0 && !right)
        {
            //cout << "space right" << endl;
            //cout << "space direction: " << parseDirection(1) << endl;
            x = cx+parseX(1);
            y = cy+parseY(1);
            //id = maze.size();
            id = getCellId(x, y);
            //cout << "X: " << x << " Y: " << y << " ID: " << id << endl;
            toInsert = cell(id, x, y, 0);
            toInsert.neighbors.push_back(ci);
            maze.insert(pair<int, cell>(id, toInsert));
            maze.find(ci)->second.neighbors.push_back(id);
            unvisited.push_back(toInsert);
        }

    }
    current = maze.find(ci)->second;
}

vector<cell> solver::getNeighbors(cell c)
{
    vector<cell> neighbors;
    for (vector<int>::iterator it = c.neighbors.begin(); it != c.neighbors.end(); ++it)
    {
        if(!maze.find(*it)->second.traversed) neighbors.push_back(maze.find(*it)->second);
    }
    return neighbors;
}

void solver::findPath(cell start, cell finish)
{
    //cout << "start " << start << endl;
    //cout << "finish " << finish << endl;
    cell temp;
    path.push_back(maze.find(start.id)->second);
    temp = path.back();
    while(temp != finish)
    {
        //cout << "set " << path.back().id << " as traversed and onPath" << endl;
        maze.find(path.back().id)->second.traversed = true;
        maze.find(path.back().id)->second.onPath = true;
        temp = maze.find(path.back().id)->second;
        vector<cell> neighbors = getNeighbors(temp);
        if (!neighbors.empty())
        {
            //cout << "added neighbor " << neighbors.front().id << endl;
            path.push_back(maze.find(neighbors.front().id)->second);
        }
        else
        {
            if (path.back() != finish)
            {
                //cout << "removing from path " << path.back().id << endl;
                maze.find(temp.id)->second.onPath = false;
                path.pop_back();
            }
        }
    }
}

instruction solver::generateRotateAmount(int c1, int c2)
{
    if(c1 < c2)
    {
        if( (c2-c1) <= (3+c1-abs(c1-c2)) )
        {
            return instruction(2, (c2-c1));
        }
        else return instruction(2, -(4+c1-abs(c1-c2)));
    }
    else if(c1 > c2)
    {
        if( (c1-c2) <= (3+c2-abs(c1-c2)) )
        {
            return instruction(2, -(c1-c2));
        }
        else return instruction(2, (4+c2-abs(c1-c2)));
    }
    return instruction(2, 0);
}

vector<instruction> solver::generateInstructions()
{
    int dir = direction;
    vector<instruction> inst;
    //cout << "path length: " << path.size() << endl;
    if(path.size() > 0){
    for (vector<cell>::iterator it = path.begin(); it != path.end(); ++it)
    {
        if(*it != path.back())
        {
            cell c1 = *it;
            cell c2 = *(it+1);
            //cout << "c1 *it: " << c1 << endl;
            //cout << "c2 *(it+1): " << c2 << endl;

            //need to turn left
            if(c1.px > c2.px && dir != LEFT)
            {
                //cout << "turning left" << endl;
                inst.push_back(generateRotateAmount(dir, LEFT));
                dir = LEFT;
            }
            //need to turn right
            else if(c1.px < c2.px && dir != RIGHT)
            {
                //cout << "turning right" << endl;
                inst.push_back(generateRotateAmount(dir, RIGHT));
                dir = RIGHT;
            }
            //need to turn up
            else if(c1.py > c2.py && dir != UP)
            {
                //cout << "turning up" << endl;
                inst.push_back(generateRotateAmount(dir, UP));
                dir = UP;
            }
            //need to turn down
            else if(c1.py < c2.py && dir != DOWN)
            {
                //cout << "turning down" << endl;
                inst.push_back(generateRotateAmount(dir, DOWN));
                dir = DOWN;
            }
            //move forward one block'
            inst.push_back(instruction(1, 1));
        }
    }
    direction = dir;
    for(vector<instruction>::iterator it = inst.begin(); it != inst.end(); ++it)
    {
      //cout << "instruction: " << it->command << " value: " << it->value << endl;
    }
    current = path.back();
    //cout << "current: " << current << endl;
  }
    return inst;
}

vector<instruction> solver::update_solver(int dleft, int dforward, int dright)
{

    findNeighbors(dleft, dforward, dright);

    removeVisited();

    path.clear();

    //cout << "unvisited size: " << unvisited.size() << endl;

    if(unvisited.size() > 0)
    {
        resetCells();
        findPath(current, unvisited.back());
        //cout << "path found." << endl;
    }

    for (vector<cell>::iterator it = path.begin(); it != path.end(); ++it)
    {
        //cout << "Path: " << *it << endl;
    }

    updateVisited();

    return generateInstructions();
}

vector<instruction> solver::go_to_end()
{
  path.clear();
  if ( maze.find(1) != maze.end())
  {
    resetCells();
    findPath(current, maze.find(1)->second);
  }
  else
  {
    resetCells();
    findPath(current, maze.find(9)->second);
  }

  return generateInstructions();
}

vector<instruction> solver::go_to_start()
{
  path.clear();
  resetCells();
  findPath(current, maze.find(48)->second);
  return generateInstructions();
}

int solver::getCellId(int x, int y)
{
    return 49-((7*(y))+x);
}

void solver::printCells()
{
    cout << "maze: " << endl;
    for (map<int, cell>::iterator it = maze.begin(); it != maze.end(); ++it)
    {
        cout << it->first << " => " << it->second << endl;
    }
}

void solver::printUnvisited()
{
    cout << "unvisited: " << endl;
    for (vector<cell>::iterator it = unvisited.begin(); it != unvisited.end(); ++it)
    {
        cout << *it << endl;
    }
}

void solver::resetCells()
{
    for (map<int, cell>::iterator it = maze.begin(); it != maze.end(); ++it)
    {
        it->second.traversed = false;
        it->second.onPath = false;
    }
}

void solver::updateVisited()
{
    for (vector<cell>::iterator it = path.begin(); it != path.end(); ++it)
    {
        maze.find(it->id)->second.visited = 1;
    }
}

void solver::removeVisited()
{
    for (vector<cell>::iterator it = unvisited.begin(); it != unvisited.end(); ++it)
    {
        if (maze.find(it->id)->second.visited > 0)
        {
            //cout << "removing " << it->id << " from visited." << endl;
            unvisited.erase(it);
            removeVisited();
            break;
        }
    }
}

ostream& operator<< (ostream &out, const cell &rhs)
{
    out << "ID: " << rhs.id <<  " Visited: " << rhs.visited << " PX: " << rhs.px << " PY: " << rhs.py << endl;

    for (vector<int>::const_iterator it = rhs.neighbors.begin(); it != rhs.neighbors.end(); ++it)
    {
        cout << "Neighbor: " << *it << endl;
    }

    return out;
}
