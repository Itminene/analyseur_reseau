#include <stdio.h> 
#include <stdlib.h>
#include "type.h"


Trace* create_cell_trace (int num, Trame* ptrame){
    // creer une nouvelle cellule de trace (une nvle trame)

    Trace* newcelltrace=NULL;
    newcelltrace=malloc(sizeof(Trace));
    newcelltrace->num=num;
    newcelltrace->ptrame=ptrame;
    newcelltrace->next=NULL;
    return newcelltrace;
}

Trame* create_cell_trame (int octet){
    //creer une nouvelle cellule de trame (un nvl octet)

    Trame* newcelltrame=NULL;
    newcelltrame=malloc(sizeof(Trame));
    newcelltrame->octet=octet;
    newcelltrame->next=NULL;
    return newcelltrame;
}

/*void print_cell_trame(Trame* cell){
    //affiche l'octet de la cellule courante de la trame
    printf("%d \n",cell->octet);
}

void print_cell_trace(Trace* cell){
    //affiche le numero de la trame courante dans la trace
    printf("%d \n",cell->num);
}*/
void print_trame(Trame* t)
{
    //affiche les octets de la trame
    while (t != NULL)
    {
        printf("%d ", t->octet);
        t = t->next;
    }
    printf("\n");
}

void print_trace(Trace* t)
{
    //affiche les num de chaque trame
    while (t != NULL)
    {
        printf("%d \n", t->num);
        print_trame(t->ptrame);
        t = t->next;
    }
    printf("\n");
}
Trame* free_trame(Trame* t){
    Trame* tmp;
    while(t!=NULL){
        tmp=t;
        t=t->next;
        free(tmp);
    }
    return NULL;
}

Trace* free_trace(Trace* t){
    Trace* tmp;
    while(t!=NULL){
        tmp=t;
        free_trame(t->ptrame);
        t=t->next;
        free(tmp);
    }
    return NULL;
}

Trace* get_trace(FILE * file){
    //La methode recupere une trace et creer une liste de type Trace qu'elle initialise avec ses Trames
    Trace* trace=NULL;
    Trace* endtrace=NULL;
    
    if(file!=NULL){
        
        int a;//variable de parcourt des offsets
        int j;//variable de parcourt des octets
        int cpt=0;//compteur de trame;
        
        while(!feof(file)){
            
            //lecture de l'offset
            fscanf(file, "%x", &a);
            
            //on verifie qu'on a pas atteint la fin du fichier
            if(feof(file)){
                    fclose(file);
                    return trace;
                }
            //printf("\n %d   ",a);
            if(a==0){//debut d'une trame
                cpt++;
                if(cpt==1){
                    trace=create_cell_trace(cpt,NULL);
                    endtrace=trace;
                }else{
                    endtrace->next=create_cell_trace(cpt,NULL);
                    endtrace=endtrace->next;
                }
            } 
            
            Trame* endtrame;
            //lecture d'une ligne
            for(int i=0;i<16;i++){//16 octets par ligne, donc 16* fscanf
                
                fscanf(file, " %x", &j);//lecture octet par octet
                
                //on verifie qu'on a pas atteint la fin du fichier sinon duplique 16 * le dernier
                if(feof(file)){
                    fclose(file);
                    return trace;
                }
                
                if(i==0){// si c'est le premier octet
                    endtrame=create_cell_trame(j); // on creer une cellule de trame
                    endtrace->ptrame=endtrame;//ptrame de la trace courante point vers la cellule contenant l'octet courant
                }else{//sinon
                    endtrame->next=create_cell_trame(j);
                    endtrame=endtrame->next;
                }

                //printf("%d ",j);
            }
        }

        fclose(file);
    }else{ 
        printf("echec ouverture");
        exit(1);
    }

    fclose(file);
    return trace;
}
int main()
{
    //Test initialisation d'une cellule
    /*int a =5;
    Cell* cell=NULL; //adresse de la cellule
    cell=create_cell(a);
    print_cell(cell);*/

     
    FILE *file = fopen("trame.txt", "r");//ouvre fichier contenant la trame
    Trace* t=NULL;
    t=get_trace(file);
    print_trace(t);
    free_trace(t);
    
    return 0;
}
