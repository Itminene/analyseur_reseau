#ifndef ANALYSE_TRAME_BIS_H
#define ANALYSE_TRAME_BIS_H

#include "lecture_trame.h"
typedef struct Tcp_brut Tcp_brut;
struct Tcp_brut
{
    int ip_src[4];
    int ip_dst[4];
    int port_src[2];
    int port_dst[2];
    int seq[4];
    int ack[4];
    char flags[8];
    int win[2];
    int mss[2];
    int ws;
    int sack_perm;
    int tsv[4];
    int terv[4];
    int len;
};

typedef struct  Printable Printable ;
struct Printable
{
    char ip_src[200];
    char ip_dst[200];
    int pos_src;
    int pos_dst;
    char port_src[7];
    char port_dst[7];
    char type[30];
    char comment[100];
};
typedef struct  Cell_Printable Cell_Printable ;
struct Cell_Printable
{
    
    Printable * printable;
    Cell_Printable *next;
    Cell_Printable *before; 
    
};

typedef struct  List_Printable List_Printable ;
struct List_Printable
{
    int nb_printable;
    Cell_Printable *premier; 
    Cell_Printable *dernier; 
};
long int quatres_octets_to_decimal(int hexa[4]);
int deux_octets_to_decimal(int hexa[2]);

Cell_Printable* create_cell_printable();
List_Printable* create_list_cell_printable();
int free_cell_printable(Cell_Printable* p);
int free_list_Printable(List_Printable *lp);
void ajout_printable(Cell_Printable* cp,Printable*p);
void ajout_cell_printable(List_Printable* lp,Cell_Printable* cp );
void print_printable(Printable* printable);
void print_list_cell_printable(List_Printable* lp);

int hexa_to_bin( int num, char bin[8]);

#endif