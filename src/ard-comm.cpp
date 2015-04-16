#include <sys/unistd.h>
#include "../include/ard-comm.h"


ardComm::ardComm()
{

}

ardComm::~ardComm()
{
    //dtor
}


bool ardComm::open()
{
    fcntl(fd1, F_SETFL, O_NONBLOCK);
    fd1 = open("/dev/ttyUSB0", O_RDWR | O_NONBLOCK);
    usleep(1000*1000*100);
    return fd1 != -1;
}

void ardComm::move(int p)
{
    write(fd1, "!"+to_string(p)+"\n", 3);
}

void ardComm::rotate(int r)
{
    write(fd1, "@"+to_sting(r)+"\n", 3);
}

void ardComm::set_light(int l)
{
    write(fd1, "^"+to_sting(l)+"\n", 3);
}

bool ardComm::get_button(void)
{
    write(fd1, "r\n", 2);
    string res = read(fd1, buff, 1);
    return res == "1";
}

data* ardComm::get_status(void)
{
    data* d = new data();
    write(fd1, "?\n", 2);
    d->left = atoi(read(fd1, buff, 1));
    d->right = atoi(read(fd1, buff, 1));
    d->forward = atoi(read(fd1, buff, 1));
    return d;
}
