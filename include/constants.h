#pragma once

using namespace std;

enum DIRECTION {UP=0, RIGHT=1, DOWN=2, LEFT=3};
enum COMMAND {MOVE=0, ROTATE=1, LIGHT=2, NA=-1};

struct data {
  int left;
  int forward;
  int right;
};

struct instruction
{
    COMMAND command;
    int value;
    //command = 1 -> move, command = 2 -> rotate, command = 3 -> light
    //value = (command) number of blocks to move forward, (rotate) number of 90* rotations
    instruction(COMMAND c, int v) : command(c), value(v) {}
    instruction()
    {
      command = NA;
      value = -1;
    }
};
