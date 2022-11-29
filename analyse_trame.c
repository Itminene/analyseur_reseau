#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "analyse_trame.h"
#include "lecture_trame.h"

/* Fonction qui permet d'analyser une entête ethernet
   Modifie le pointeur du 'paquet' passé en paramètre pour qu'elle pointe vers
   le premier octet des données de la trame et créé une nouvelle cellule de trame
   ATTENTION : une nouvelle allocation est faite
   Affiche les infos de l'entête
   Retourne le type de paquet encapsulé et nombre négatif en cas d'erreur */
int read_ethernet(Trame *trame, Trame **paquet)
{
    assert(trame);

    // Déclaration
    int type, tmp;

    (*paquet) = create_cell_trame(-1);
    assert(paquet);

    (*paquet)->premier = trame->premier;
    (*paquet)->dernier = trame->dernier;

    printf("Ethernet\n");

    // Lecture adresse destination
    printf("Adresse MAC Destination : ");
    for(unsigned i=0; i<6; i++)
    {
        printf("%x ", (*paquet)->premier->octet);
        (*paquet)->premier = (*paquet)->premier->next;
    }
    printf("\n");

    // Lecture adresse source
    printf("Adresse MAC source : ");
    for(unsigned i=0; i<6; i++)
    {
        printf("%x ", (*paquet)->premier->octet);
        (*paquet)->premier = (*paquet)->premier->next;
    }
    printf("\n");

    // Lecture du type
    type = (*paquet)->premier->octet;
    (*paquet)->premier = (*paquet)->premier->next;
    type = type * 16 * 16;

    tmp = (*paquet)->premier->octet;
    (*paquet)->premier = (*paquet)->premier->next;
    type += tmp;

    return type;
}