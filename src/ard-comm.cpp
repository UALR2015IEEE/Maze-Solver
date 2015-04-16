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
    ard = Serial("/dev/ttyUSB0", 155200);
    ard.open();
    return true;
}

void ardComm::move(int p)
{
    ard.write("!"+to_string(p)+"\n");
}

void ardComm::rotate(int r)
{
    ard.write("@"+to_sting(r)+"\n");
}

void ardComm::set_light(int l)
{
    ard.write("^"+to_sting(l)+"\n");
}

bool ardComm::get_button(void)
{
    ard.write("r\n");
    string res = ard.readline();
    return res == "1";
}

data* ardComm::get_status(void)
{
    data* d = new data();
    ard.write("?\n");
    d->left = atoi(ard.read(1));
    d->right = atoi(ard.read(1));
    d->forward = atoi(ard.read(1));
    return d;
}
