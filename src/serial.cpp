#include "../include/serial.h"

serial::serial()
{

}

serial::~serial()
{
    //dtor
}


bool serial::open()
{
    return true;
}

void serial::move(int p)
{

}

void serial::rotate(int r)
{

}

void serial::set_light(bool l)
{

}

bool serial::get_button(void)
{
    return true;
}

data* serial::get_status(void)
{
    data* d = new data();
    return d;
}
