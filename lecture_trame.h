#ifndef LECTURE_TRAME_H
#define LECTURE_TRAME_H

/* Fichier contenant les structures et fonctions nécessaires à la
lecture de la trace */

/* Structure pour une cellule d'octet */
typedef struct Cell_octet Cell_octet;
struct Cell_octet
{
    int octet;
    Cell_octet *next;
    Cell_octet *before;
};

/* Structutre pour une cellule de trame */
typedef struct Trame Trame;
struct Trame
{
    int num; // Le numéro de la trame dans la trace
    Cell_octet *premier; // Premier élément (octet)
    Cell_octet *dernier; // Dernier élément (octet)
    Trame *next; // Trame suivante dans la trace
    Trame *before; // Trame précédente dans la trace
};

/* Structure modélisant la trace 
   Celle-ci contient une liste de trame ainsi qu'un entier
   représentant le nombre de trame dans la trace */
typedef struct Trace Trace;
struct Trace
{
    int nb_trames;
    Trame *premier; // Première trame
    Trame *dernier; // Dernière trame
};

/* Fonctions */

int conversion_char_int_hexa(char c);
int conversion_double_chiffres(char c1, char c2);
Trace *create_cell_trace();
Trame *create_cell_trame(int num);
Cell_octet *create_cell_octet(int valeur);
int free_octet(Cell_octet *octet);
int free_trame(Trame* t);
int free_trace(Trace *t);
void ajout_octet(Cell_octet *octet, Trame *trame);
void ajout_trame(Trame *trame, Trace *trace);
void print_trame(Trame *t);
void print_trace(Trace *t);
Trace *get_trace(char *nom_fic);

#endif