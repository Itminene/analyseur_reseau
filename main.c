#include <stdio.h> 
#include <stdlib.h>
#include "test.h"
#include "ethernet.h"

int main()
{ 
    // test.c
    printf("\n_______Affichage de la trace decompose en trame_____________\n");
    FILE *file = fopen("trame.txt", "r");//ouvre fichier contenant la trame
    Trace* t=get_trace(file);
    print_trace(t);
    


    

    //main.c
    printf("\n_______Affichage des données brut de l'entete ethernet de la trame 1_____________");
    Trame* tr1_eth= t->ptrame; //trame a analyser = trame 1 de la trace
    Eth e1;
   
    Trame* tr1_ip= read_ethernet(tr1_eth,&e1);// la fonction retourne un pointeur vers le champs data (soit ip ici)
    t->ptrame=tr1_ip;// comme read_ethernet() supprime l'entete ethernet on change dans ptrame de trace sa valeur
    print_ethernet_brut(e1); 

    
    
    
    
    printf("\n_______Affichage des données brut de l'entete ethernet de la trame 2_____________");
    Trame* tr2_eth= t->next->ptrame; //trame a analyser = trame 2 de la trace
    Eth e2;
   
    Trame* tr2_ip= read_ethernet(tr2_eth,&e2);
    t->next->ptrame=tr2_ip;
    print_ethernet_brut(e2);
    
    free_trace(t);   
    return 0;
}