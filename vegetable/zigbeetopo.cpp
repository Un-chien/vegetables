#include "zigbeetopo.h"

ZigbeeTopo::ZigbeeTopo()
{      
    cliect_thread1 = new Cliect();
    this->start();
}

ZigbeeTopo::~ZigbeeTopo()
{
}

void ZigbeeTopo::run(){

    while(1)
    {
        mutex.lock();
        cliect_thread1->Api_Cliect_GetZigBeeNwkTopo();
        mutex.unlock();
        usleep(800000);
    }
}
