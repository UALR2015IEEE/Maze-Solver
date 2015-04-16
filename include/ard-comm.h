#ifndef SERIAL_H
#define SERIAL_H

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <fstream>
#include <fcntl.h
#include "constants.h"
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
        int fd1;
        int fd2;
        char * buff = new char[2];
        int wr, rd, nbytes, tries;
};

#endif // SERIAL_H
