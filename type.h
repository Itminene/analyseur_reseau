#ifndef TYPE_H
#define TYPE_H
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
#endif