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
    usleep(1000*1000);
    return fd1 != -1;
}

void ardComm::move(int p)
{
    write(fd1, '!'+to_string(p).c_str(), 3);
}

void ardComm::rotate(int r)
{
    write(fd1, '@'+to_string(r).c_str(), 3);
}

void ardComm::set_light(int l)
{
    write(fd1, '^'+to_string(l).c_str(), 3);
}

bool ardComm::get_button(void)
{
    write(fd1, "r", 1);
    cout << "button >";
    read(fd1, buff, 1);
    string res(buff);
    cout << res << buff << endl;
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
