#ifndef TEST_H
#define TEST_H

//La trace est stockés dans une liste de liste
//Chaque liste contient une trame
//Chaque cellule de la liste trame  contient un octet



//Structure definissant une liste
typedef struct Trame Trame;
struct Trame
{
    int octet;//octet de la trame
    Trame *next;//octet suivant
};


//structure definissant une  liste de liste
typedef struct Trace Trace;
struct Trace
{
    int num;//numero de la trame
    Trame* ptrame;// pointeur vers l'entete de la trame
    Trace* next;//pointeur vers la trace suivante;
};

Trace* create_cell_trace (int num, Trame* ptrame);
Trame* create_cell_trame (int octet);
void print_trame(Trame* t);
void print_trace(Trace* t);
Trame* free_trame(Trame* t);
Trace* free_trace(Trace* t);
Trace* get_trace(FILE * file);
#endif
