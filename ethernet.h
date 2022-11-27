#ifndef ETHERNET_H
#define ETHERNET_H

#include "test.h"

//structure contenant en-tete ethernet
typedef struct Eth Eth;
struct Eth
{
    int dst[6];
    int src[6];
    int type[2];
};

Trame*  read_ethernet(Trame* t, Eth* e);
void print_ethernet_brut(Eth e);

#endif