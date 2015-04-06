#include "../include/serial.h"

serial::serial()
{

}

serial::~serial()
{
    //dtor
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

bool serial::get_switch(void)
{
    return 0;
}

COMMANDS serial::get_status(void)
{
    COMMANDS c = MOVE;
    return c;
}
