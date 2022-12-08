#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "analyse_trame_bis.h"
#include "lecture_trame.h"

#define LENIPBRUT 13 //longueur max d'une adresse ip en string

/*----------------Fonctions pour creer une liste de printable------------------*/
Cell_Printable* create_cell_printable(){
    Cell_Printable* nv = malloc(sizeof(Cell_Printable));
    if(nv == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de la Cell_Printable");
        return NULL;
    }

    
    nv->printable= malloc(sizeof(Printable));
    nv->next = NULL;
    nv->before = NULL;

    return nv;
}
List_Printable* create_list_cell_printable()
{

    List_Printable *nv = malloc(sizeof(List_Printable));
    if(nv == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de la trace");
        return NULL;
    }

    nv->nb_printable = 0;
    nv->premier = NULL;
    nv->dernier = NULL;

    return nv;
}
/*-----------------------------------------------------------------------------*/

/*----------------Fonctions pour free une liste de printable------------------*/
int free_cell_printable(Cell_Printable* p){
    if(p!=NULL){
        free(p->printable);
        free(p);
    }
    
    return 1;
}
int free_list_Printable(List_Printable *lp)
{
    if(lp==NULL){
        return 1;
    }
    // Déclarations
    Cell_Printable *ite = lp->premier;
    Cell_Printable *tmp;

    // Parcours de la liste de Cell_Printable de la liste
    while(ite != NULL)
    {
        tmp = ite;
        ite = ite->next;
        free_cell_printable(tmp);
    }

    // Libération de la liste
    free(lp);
    
    return 1;
}
/*-----------------------------------------------------------------------------*/

/*----------------Fonctions pour ajouter dans  une liste de printable------------------*/
void ajout_printable(Cell_Printable* cp,Printable*p){
    cp->printable=p;
}
void ajout_cell_printable(List_Printable* lp,Cell_Printable* cp )
{
    // Première trame de la trace
    if(lp->premier == NULL)
    {
        assert(lp->nb_printable == 0);
        lp->premier = cp;
        lp->dernier = cp;
    }
    else
    {
        assert(lp->nb_printable > 0);
        lp->dernier->next = cp;
        cp->before = lp->dernier;
        lp->dernier = cp;
    }

    lp->nb_printable++;
}
/*-----------------------------------------------------------------------------*/

/*----------------Fonctions pour print une liste de printable------------------*/
void print_printable(Printable* printable){
    assert(printable);
    printf("@ip src : %s\n",printable->ip_src);
    printf("@ip dst : %s\n",printable->ip_dst);
    printf("port src : %s\n",printable->port_src);
    printf("port dst : %s\n",printable->port_dst);
    printf("type : %s\n",printable->type);
    printf("commentaire : %s\n",printable->comment);
}
void print_list_cell_printable(List_Printable* lp){
    if(lp==NULL ){
        printf("ERREUR la list_cell_printable est vide\n");
        return;
    }
    
    Cell_Printable *ite = lp->premier;
    // Parcours de la liste de trames
    printf("\n");
    while(ite != NULL)
    {
        
        print_printable(ite->printable);
        printf("\n");
        ite = ite->next;
    }
    printf("\n");
}
/*-----------------------------------------------------------------------------*/


/*Fonction qui convertit un nb hexa en binaire
Les valeurs binaires sont stockés dans un tableau
ex : 0x01 -> 0000 0001
*/
int hexa_to_bin( int num, char bin[8])
{ 
    //arguments : int correspondant a un nb hexadecimal 0x00
    //             tableau de char qui va contenir les bit de num 
    //return rien modifie directement le tableau en arguemnt
    char hexa[3]; 
    sprintf(hexa,"%x",num);
    if(num<10){
        hexa[1]=hexa[0];
        hexa[0]='0';
    }
    
        switch (hexa[0])
        {
        case '0':
            strcpy(bin,"0000");break;
        case '1':
            strcpy(bin,"0001"); break;
        case '2':
            strcpy(bin,"0010"); break;
        case '3':
            strcpy(bin,"0011"); break;
        case '4':
           strcpy(bin,"0100"); break;
        case '5':
            strcpy(bin,"0101"); break;
        case '6':
            strcpy(bin,"0110"); break;
        case '7':
            strcpy(bin,"0111"); break;
        case '8':
            strcpy(bin,"1000"); break;
        case '9':
            strcpy(bin,"1001"); break;
        case 'A':
            strcpy(bin,"1010"); break;
        case 'B':
            strcpy(bin,"1011"); break;
        case 'C':
            strcpy(bin,"1100"); break;
        case 'D':
            strcpy(bin,"1101"); break;
        case 'E':
            strcpy(bin,"1110"); break;
        case 'F':
           strcpy(bin,"1111"); break;
        case 'a':
            strcpy(bin,"1010"); break;
        case 'b':
            strcpy(bin,"1011"); break;
        case 'c':
            strcpy(bin,"1100"); break;
        case 'd':
            strcpy(bin,"1101"); break;
        case 'e':
            strcpy(bin,"1110"); break;
        case 'f':
            strcpy(bin,"1111"); break;  
        default :
            
            return 0;   
        }
        
        switch (hexa[1])
        {
        case '0':
            strcat(bin,"0000");break;
        case '1':
            strcat(bin,"0001"); break;
        case '2':
            strcat(bin,"0010"); break;
        case '3':
            strcat(bin,"0011"); break;
        case '4':
           strcat(bin,"0100"); break;
        case '5':
            strcat(bin,"0101"); break;
        case '6':
            strcat(bin,"0110"); break;
        case '7':
            strcat(bin,"0111"); break;
        case '8':
            strcat(bin,"1000"); break;
        case '9':
            strcat(bin,"1001"); break;
        case 'A':
            strcat(bin,"1010"); break;
        case 'B':
            strcat(bin,"1011"); break;
        case 'C':
            strcat(bin,"1100"); break;
        case 'D':
            strcat(bin,"1101"); break;
        case 'E':
            strcat(bin,"1110"); break;
        case 'F':
           strcat(bin,"1111"); break;
        case 'a':
            strcat(bin,"1010"); break;
        case 'b':
            strcat(bin,"1011"); break;
        case 'c':
            strcat(bin,"1100"); break;
        case 'd':
            strcat(bin,"1101"); break;
        case 'e':
            strcat(bin,"1110"); break;
        case 'f':
            strcat(bin,"1111"); break;  
        default :
            
            return 0;   
        }
     
    return 1;
}

/*Fonction qui prend en argument un tableaux de 4 octets
Elle convertit le mot de 4 octets hexadecimal en decimal*/
long int quatres_octets_to_decimal(int hexa[4])
{   
    //declaration
    char str_hexa[8];
    char str_tmp[3];
    int int_hexa[8];
    long int res=0;
    
    //Conversion des octets hexa en string
    if(hexa[0]<16){
           sprintf(str_hexa,"0%x",hexa[0]);
        }else{
            sprintf(str_hexa,"%x",hexa[0]);
        }
    for(int i=1;i<4;i++){
        if(hexa[i]<16){
           sprintf(str_tmp,"0%x",hexa[i]);
           strcat(str_hexa,str_tmp);
        }else{
            sprintf(str_tmp,"%x",hexa[i]);
           strcat(str_hexa,str_tmp);
        }
        
    }
    //sprintf(str_hexa,"%0x%0x%0x%0x",hexa[0],hexa[1],hexa[2],hexa[3]);
    
    //Conversion des char en int (y compris lettre hexa)
    for(int i=0;i<strlen(str_hexa);i++){
        int_hexa[i]=conversion_char_int_hexa(str_hexa[i]);
        
    }
    
    int puissance=strlen(str_hexa)-1;
    //printf("res : %d\n",puissance);
    for(int i=0;i<strlen(str_hexa);i++){
        res+=int_hexa[i]*pow(16,puissance);
        //printf("%d*pow(16,%d) = %ld\n",int_hexa[i],puissance,res);
        puissance--;
    }
    
    return res;
}

/*Fonction qui prend en argument un tableaux de deux octets
Elle convertit le mot de 2 octets hexadecimal en decimal*/
int deux_octets_to_decimal(int hexa[2])
{   
    //declaration
    char str_hexa[4];
    char str_tmp[3];
    int int_hexa[4];
    int res=0;
    
    //Conversion des octets hexa en string
    //sprintf(str_hexa,"%x%x",hexa[0],hexa[1]);
    if(hexa[0]<16){
           sprintf(str_hexa,"0%x",hexa[0]);
        }else{
            sprintf(str_hexa,"%x",hexa[0]);
        }
    
    if(hexa[1]<16){
        sprintf(str_tmp,"0%x",hexa[1]);
        strcat(str_hexa,str_tmp);
    }else{
        sprintf(str_tmp,"%x",hexa[1]);
        strcat(str_hexa,str_tmp);
    }
        
    
    //Conversion des char en int (y compris lettre hexa)
    for(int i=0;i<strlen(str_hexa);i++){
        int_hexa[i]=conversion_char_int_hexa(str_hexa[i]);
        
    }

    int puissance=strlen(str_hexa)-1;
    //printf("pow : %d\n",puissance);
    for(int i=0;i<strlen(str_hexa);i++){
        res+=int_hexa[i]*pow(16,puissance);
        //printf("%d*pow(16,%d) = %d\n",int_hexa[i],puissance,res);
        puissance--;
    }
    
    return res;
 
}