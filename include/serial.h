#ifndef SERIAL_H
#define SERIAL_H

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

#include "constants.h"

using namespace std;

class serial
{
    public:
        serial();
        virtual ~serial();

        void move(int p);
        void rotate(int r);
        void set_light(bool l);

        bool get_switch(void);
        COMMANDS get_status();

    private:

};

#endif // SERIAL_H
