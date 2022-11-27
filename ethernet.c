#include <stdio.h> 
#include <stdlib.h>
#include "test.h"
#include "ethernet.h"
// Ce fichier analyse les trames ethernet

Trame*  read_ethernet(Trame* t, Eth* e){
//La fonction prend entrée une trame et la structure qui va contenir en tete ethernet
//Elle retourne la trame (=liste chainée d'octet) sans son entete ethernet
    
    int i=0; // compteur de parcours de la liste chainée
    int j=0;
    int k=0;
    int l=0;
    Trame* tmp;
    while(i<=14){
        while(j<=5){
            e->dst[j]=t->octet;
            j++;
            i++;
            tmp=t;
            t=t->next;
            free(tmp);
        } 
        while(k<=5){
            e->src[k]=t->octet;
            k++;
            i++;
            tmp=t;
            t=t->next;
            free(tmp);
        }   
        while(l<=1){
            e->type[l]=t->octet;
            l++;
            i++;
            tmp=t;
            t=t->next;
            free(tmp);
        }   
        
        break;
    }
   
    
    return t;
}

void print_ethernet_brut(Eth e){ 
    //affiche les donnees brut en int de l'en tete ethernet
    printf("\n@MAC DST : ");
    for(int i=0; i<=5;i++){
        printf("%d ",e.dst[i]);
    }

    printf("\n@MAC SRC : ");
    for(int j=0; j<=5;j++){
        printf("%d ",e.src[j]);
    }
    printf("\ntype : ");
    for(int k=0; k<=1;k++){
        printf("%d ",e.type[k]);
    }
    printf("\n");
}

