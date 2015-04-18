#include <sys/unistd.h>
#include "../include/ard-comm.h"


ardComm::ardComm()
{
    buff = new char[2];
}

ardComm::~ardComm()
{
    //dtor
}


bool ardComm::fopen()
{
    fd1 = open("/dev/ttyUSB0", O_RDWR | O_NONBLOCK);
    fcntl(fd1, F_SETFL, O_NONBLOCK);
    usleep(1000*1000*10);
    return fd1 != -1;
}

void ardComm::move(int p)
{
    stringstream ss;
    ss << p;
    write(fd1, '!'+ss.str().c_str(), 2);
}

void ardComm::rotate(int r)
{
    stringstream ss;
    ss << r;
    write(fd1, '@'+ss.str().c_str(), 2);
}

void ardComm::set_light(int l)
{
    if(l == 0)
    	write(fd1, "^0", 2);
    else if (l == 1)
	write(fd1, "^1", 2);
    else if (l == 2)
	write(fd1, "^2", 2);
}

bool ardComm::get_button(void)
{
    write(fd1, "#", 1);
    read(fd1, buff, 1);
    string res(buff);
    return res == "1";
}

data* ardComm::get_status(void)
{
    data* d = new data();
    write(fd1, "?", 2);
    read(fd1, buff, 3);
    d->left = buff[0];
    d->right = buff[1];
    d->forward = buff[2];
    return d;
}
