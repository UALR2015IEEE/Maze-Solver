#ifndef SERIAL_H
#define SERIAL_H

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include "constants.h"
#include "serial.h"
#include "string.h"

using namespace std;

class ardComm
{
    public:
        ardComm();
        virtual ~ardComm();

        bool open();
        void move(int p);
        void rotate(int r);
        void set_light(int l);

        bool get_button(void);
        data* get_status();

    private:
        Serial ard;
};

#endif // SERIAL_H
