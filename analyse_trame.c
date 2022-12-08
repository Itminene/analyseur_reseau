#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "analyse_trame.h"
#include "analyse_trame_bis.h"
#include "lecture_trame.h"

#define LENIPBRUT 13 //longueur max d'une adresse ip en string

/*Fonction qui test si l'en-tete ethernet encaspule un paquet ipv4 (0x08 00)
    si oui : return 1
    si non : return 0*/
int read_ethernet(Trame* trame){
    assert(trame);

    // Déclaration
    Cell_octet* tmp=trame->premier; //permet de parcourir la trame sans la modifier

    //boucle de parcourt pour arriver a l'octet type
    for(unsigned i=0; i<13; i++)
    {
        tmp = tmp->next;
    }
    
    //Test du type (ipv4=08 00)
    if(tmp->octet==0){
        return 1;
    }

    return 0;
}

/*Fonction qui test si l'en-tete ip encapsule un segment tcp (protocol=6)
    si oui : return 1
    si non : return 0
    ps:La trame passé en argument contient en-tete ethernet*/
int read_ip(Trame* trame){
    assert(trame);

    //Déclaration
    Cell_octet* tmp=trame->premier;//permet de parcourir la trame sans la modifier
 
    for(unsigned i=0; i<23; i++){
        tmp = tmp->next;
    }

    //Test du type (tcp=06 )
    if(tmp->octet==6){
        return 1;
    }
    
    return 0;
    
}

/*Fonction qui test si  trame contient segment tcp 
    si oui : recupere @ip src et dst et les stockent dans les tableaux
             fait pointer "segment" vers debut des données tcp
             return 1 si tout c'est bien passé
    si non : return 0 (trame ne contient pas de segment tcp)*/
int get_ip(Trame* trame,Trame **segment,int src[4],int dst[4]){
        assert(trame);

        if(read_ip(trame)==1){
            //On recupere l'ihl pour connaitre le premier octet des datas tcp
            int ihl;

            (*segment) = create_cell_trame(-1);
            assert(segment);

            (*segment)->premier = trame->premier;
            (*segment)->dernier = trame->dernier;

            //on parcourt jusqu'à l'octet ihl
            for(unsigned i=0; i<14; i++){
            (*segment)->premier = (*segment)->premier->next;
            }

            //Calcul de l'ihl
            ihl=((*segment)->premier->octet)-64;
            ihl=ihl*4;
            
            int vsrc=0;
            int vdst=0;
            for(int i=0;i<ihl;i++){
                if(i>=12 && i<=15){
                    src[vsrc]=(*segment)->premier->octet;
                    src++;
                }
                if(i>=16 && i<=22){
                    dst[vdst]=(*segment)->premier->octet;
                    dst++;
                }
                (*segment)->premier = (*segment)->premier->next;

            }
            return 1;
        }
        return 0;
}


/*La Fonction : -recupère les données tcp brut.
                 et initialise les données de l'en-tete dans la structure tcp_brut
                -Test si le segment encapsule des données
                    Si oui :
                        Si données http-> data pointera vers le premier octet des données http et  retourne 1
                        Si non rempli champ len avec taille données et return 0
                    Si non :
                        return 0    
*/
int get_tcp(Trame* trame,Trame **data,Tcp_brut* tcp_brut,int src[4],int dst[4]){
    printf("On entre dans get_tcp\n");
    assert(trame);
    (*data) = create_cell_trame(-1);
    assert(data);
   
   //declarations
   int thl;// la longueur de l'en tete tcp
   int cpt=0;//numero de l'octet courant 

    assert(tcp_brut);
    (*data)->premier = trame->premier;
    (*data)->dernier = trame->dernier;

    
    for(int i= 0;i<4;i++){
            tcp_brut->ip_src[i]=src[i];
    }
    for(int i= 0;i<4;i++){
        tcp_brut->ip_dst[i]=dst[i];
    }
    
    //On est au debut du segment TCP
        
    //port src
    for(unsigned i=0;i<2;i++){
        tcp_brut->port_src[i]=(*data)->premier->octet;
        (*data)->premier=(*data)->premier->next;
        cpt++;
    }
        
    //port dst
    for(unsigned i=0;i<2;i++){
        tcp_brut->port_dst[i]=(*data)->premier->octet;
        (*data)->premier=(*data)->premier->next;
        cpt++;
    }
        
    //seq
    for(unsigned i=0;i<4;i++){
        tcp_brut->seq[i]=(*data)->premier->octet;
        (*data)->premier=(*data)->premier->next;
         cpt++;
    }
        
    //ack
     for(unsigned i=0;i<4;i++){
        tcp_brut->ack[i]=(*data)->premier->octet;
        (*data)->premier=(*data)->premier->next;
        cpt++;
    }

    //thl =taille de l'en-tete avec les options
    thl=(*data)->premier->octet;
    char thl_tmp[3];
    sprintf(thl_tmp,"%x",thl);
    thl=conversion_char_int_hexa(thl_tmp[0]);
    thl=thl*4;
    (*data)->premier=(*data)->premier->next;
    cpt++;    
    
    //flags
    int flag=(*data)->premier->octet; 
    hexa_to_bin(flag,(tcp_brut->flags));
    (*data)->premier=(*data)->premier->next;
    cpt++;    
        
    //window
     for(unsigned i=0;i<2;i++){
        tcp_brut->win[i]=(*data)->premier->octet;
        (*data)->premier=(*data)->premier->next;
        cpt++;
    } 
    
    for(unsigned i=0;i<4;i++){
        (*data)->premier=(*data)->premier->next;
        cpt++;
    } 

    //options
    //printf("=======%d<%d\n",cpt,thl);
    tcp_brut->mss[0]=-1;
    tcp_brut->mss[1]=-1;
    tcp_brut->ws=-1;
    tcp_brut->sack_perm=-1;
    tcp_brut->tsv[0]=-1;
    tcp_brut->tsv[1]=-1;
    tcp_brut->tsv[2]=-1;
    tcp_brut->tsv[3]=-1;
    tcp_brut->terv[0]=-1;
    tcp_brut->terv[1]=-1;
    tcp_brut->terv[2]=-1;
    tcp_brut->terv[3]=-1;
    tcp_brut->len=-1;
    

    //Si pas de données octet courant ==NULL 
    

    //test si on est a la fin de l'en-tete
    if(cpt<thl){ 
        (*data)=get_options((*data),tcp_brut,&cpt,&thl);
    }
    
    //On est à la fin de l'en tete
    //Si pas de données
    if((*data)->premier==NULL){
        printf("TUUUUUUUUUUUUUUUUUUUUU BEUUUUUUUUUUUUUUUUUUG\n");
        return 0;
    }
    //Si port src ou dst ==80 alors donnée http
    if((tcp_brut->port_src[0]==0 &&tcp_brut->port_src[1]==80)||(tcp_brut->port_dst[0]==0 &&tcp_brut->port_dst[1]==80)){
        return 1;
    }
    
    //On parcourt jusqu'a arriver  a la fin des données
    while((*data)->premier!=NULL){
        (*data)->premier=(*data)->premier->next;
        cpt++;
    }
    tcp_brut->len=cpt+1;
    return 0;
}

/*Fonction qui transforme les données tcp brut en données printable
    return un pointeur vers une structure printable*/
Cell_Printable* tcp_to_str(Tcp_brut* tcp_brut){
    Cell_Printable* cell_printable=create_cell_printable();
    int port_tmp;

    //@ip src et dst
    sprintf(cell_printable->printable->ip_src,"%d.%d.%d.%d", tcp_brut->ip_src[0],tcp_brut->ip_src[1],tcp_brut->ip_src[2],tcp_brut->ip_src[3]) ;
    sprintf(cell_printable->printable->ip_dst,"%d.%d.%d.%d", tcp_brut->ip_dst[0],tcp_brut->ip_dst[1],tcp_brut->ip_dst[2],tcp_brut->ip_dst[3]) ;
    
    //port src et dst
    port_tmp=deux_octets_to_decimal(tcp_brut->port_src);
    sprintf(cell_printable->printable->port_src,"%d",port_tmp);
    
    
    port_tmp=deux_octets_to_decimal(tcp_brut->port_dst);
    sprintf(cell_printable->printable->port_dst,"%d",port_tmp);
    strcpy(cell_printable->printable->type,"");
    //type correspond au flags
    
    if(tcp_brut->flags[7]=='1'){
        strcat(cell_printable->printable->type,"FIN ");
    }
    if(tcp_brut->flags[6]=='1') {
        strcat(cell_printable->printable->type,"SYN ");
    } 
    if(tcp_brut->flags[5]=='1') {
        strcat(cell_printable->printable->type,"RST ");
    }
    if(tcp_brut->flags[4]=='1') {
        strcat(cell_printable->printable->type,"PSH ");
    }
    if(tcp_brut->flags[3]=='1') {
        strcat(cell_printable->printable->type,"ACK ");
    }
    if(tcp_brut->flags[2]=='1') {
        strcat(cell_printable->printable->type,"URG ");
    }

    //Commentaire
    sprintf(cell_printable->printable->comment,"TCP: %s-> %s [ %s]",cell_printable->printable->port_src,cell_printable->printable->port_dst,cell_printable->printable->type);
    
    //Seq
    char val_tmp[30];
    sprintf(val_tmp," Seq=%ld",quatres_octets_to_decimal(tcp_brut->seq));
    strcat(cell_printable->printable->comment,val_tmp);
    //ack
    sprintf(val_tmp," Ack=%ld",quatres_octets_to_decimal(tcp_brut->ack));
    strcat(cell_printable->printable->comment,val_tmp);

    //win
    sprintf(val_tmp," Win=%d",deux_octets_to_decimal(tcp_brut->win));
    strcat(cell_printable->printable->comment,val_tmp);

    //options
    //mss
    if(tcp_brut->mss[0]!=-1){
        sprintf(val_tmp," MSS= %d",deux_octets_to_decimal(tcp_brut->mss));
        strcat(cell_printable->printable->comment,val_tmp);

    }
    if(tcp_brut->ws!=-1){
        if(tcp_brut->ws<16){
            sprintf(val_tmp," WS= 0%d",tcp_brut->ws);
        }else{
            sprintf(val_tmp," WS= %d",tcp_brut->ws);
        }
        strcat(cell_printable->printable->comment,val_tmp);

    }
    if(tcp_brut->sack_perm!=-1){
        sprintf(val_tmp," SACK permitted");
        strcat(cell_printable->printable->comment,val_tmp);

    }
    if(tcp_brut->tsv[0]!=-1 && tcp_brut->tsv[0]!=-1){
        printf("on va afficher timestamps\n");
        sprintf(val_tmp," Time stamps : TSV= %ld TERV= %ld",quatres_octets_to_decimal(tcp_brut->tsv),quatres_octets_to_decimal(tcp_brut->terv));
        strcat(cell_printable->printable->comment,val_tmp);

    }
    //len
    if(tcp_brut->len!=-1){
    sprintf(val_tmp," Len=%d",tcp_brut->len);
    strcat(cell_printable->printable->comment,val_tmp);
    }
    return cell_printable;
    
}
/*Fonction qui recupère une liste d'octet http et les transforme en 
printable avec des infos http*/
Cell_Printable* tcp_to_http(Trame*data,Tcp_brut* tcp_brut){
    printf("On entre dans tcp_to_http\n");
    Cell_Printable* cell_printable=create_cell_printable();
    int port_tmp;
    //@ip src et dst
    printf("On va commencer la boucle de parcourt des octets\n");
    sprintf(cell_printable->printable->ip_src,"%d.%d.%d.%d", tcp_brut->ip_src[0],tcp_brut->ip_src[1],tcp_brut->ip_src[2],tcp_brut->ip_src[3]) ;
    sprintf(cell_printable->printable->ip_dst,"%d.%d.%d.%d", tcp_brut->ip_dst[0],tcp_brut->ip_dst[1],tcp_brut->ip_dst[2],tcp_brut->ip_dst[3]) ;
    
    //port src et dst
    port_tmp=deux_octets_to_decimal(tcp_brut->port_src);
    sprintf(cell_printable->printable->port_src,"%d",port_tmp);
    
    
    port_tmp=deux_octets_to_decimal(tcp_brut->port_dst);
    sprintf(cell_printable->printable->port_dst,"%d",port_tmp);
    
    //Type
    strcpy(cell_printable->printable->type,"HTTP");
    //Commentaire
    strcpy(cell_printable->printable->comment,"HTTP: ");   

    printf("On va commencer la boucle de parcourt des octets\n");
    char c_tmp[2];
    while(data->premier->octet!=13 && data->premier->next->octet!=10){
        printf("%x %x\n",data->premier->octet,data->premier->next->octet);
        sprintf(c_tmp,"%c",data->premier->octet);
        strcat(cell_printable->printable->comment,c_tmp);
        data->premier=data->premier->next;
    } 
    return cell_printable;
}
/*Fonction qui prend en entrée une trame brut (liste d'octets)
    return NULL si la liste n'est pas printable
    sinon return une structure printable*/
Cell_Printable* trame_brut_to_str(Trame* trame){
    //declaration
    int read=read_ethernet(trame);;
    int get;
    Trame *segment;
    Trame *data;
    Tcp_brut* tcp_brut=malloc(sizeof(Tcp_brut));
    Cell_Printable* cp;
    int ip_src[4], ip_dst[4];
    
    if(read==1){//contient paquet ip ?
        printf("top contient paquet ip!!\n");
        read=read_ip(trame);
        
        if(read==1){//contient segment tcp ?
            printf("top contient segment tcp!!\n");
            get=get_ip(trame,&segment,ip_src,ip_dst);
            
            if(get==1){//Tt s'est bien passé lors de la recuperationdes des @ip
                printf("Tt s'est bien passé lors de la recuperationdes des @ip!!\n");
                read=get_tcp(segment,&data,tcp_brut,ip_src,ip_dst);
                printf("test tcp_brut\n");
                
                if(read==1){//contient data http?
                    printf("contient data http -> YES!!\n");
                    printf(" ===================================== %d\n",tcp_brut->ip_src[0]); 
                    printf("contient data http -> YES!!\n");
                    cp=tcp_to_http(data,tcp_brut);
                    free(segment);
                    free(data);
                    free(tcp_brut);
                    return cp;
                }else{
                    printf("contient data http -> NO !!\n");
                    cp=tcp_to_str(tcp_brut);
                    free(segment);
                    free(data);
                    free(tcp_brut);
                    return cp;
                }
            }else{
                printf("La trame ne contient pas de segment tcp");
                free(segment);
                return NULL;
            }
        
        }else{
            return NULL;
        }
    }
    
    return NULL;
}
/*La fonction prend en entrée une trace et retourne une List_Printable*/
List_Printable* trace_brut_to_str(Trace* trace){
    List_Printable* lp=create_list_cell_printable();
    Cell_Printable* cp;
    Trame *ite = trace->premier;

    // Parcours de la liste de trames
    while(ite != NULL)
    {
        cp=trame_brut_to_str(ite);
        if(cp==NULL){
            ite = ite->next;
        }else{
            ajout_cell_printable(lp,cp);
            ite = ite->next;

        }
        
        
    }
    if(lp->nb_printable==0){
        
        return NULL;
    }
    return lp;
} 
 /*La fonctions prend en entrée une trame qui commence aux options TCP
 Elle remplit la structure TCP_brut avec les options*/
Trame* get_options(Trame *options,Tcp_brut* tcp_brut, int *cpt, int *thl){
    //on itiialise toutes les options a -1 ca va nous permettre de tester si des options sont vides
    while(*cpt<*thl){
    printf("tsv=============================%d\n",tcp_brut->tsv[0]);
        if(options->premier->octet==0){
            options->premier=options->premier->next;
            (*cpt)++;
            continue;
        }else{
            if(options->premier->octet==1){
                options->premier=options->premier->next;
                (*cpt)++;
                continue;
            }else{
                if(options->premier->octet==2){
                    options->premier=options->premier->next;
                    (*cpt)++;
                    options->premier=options->premier->next;
                    (*cpt)++;
                    tcp_brut->mss[0]=options->premier->octet;
                    options->premier=options->premier->next;
                    (*cpt)++;
                    tcp_brut->mss[1]=options->premier->octet;
                    options->premier=options->premier->next;
                    (*cpt)++;
                    continue;
                }else{
                    if(options->premier->octet==3){
                        options->premier=options->premier->next;
                        (*cpt)++;
                        options->premier=options->premier->next;
                        (*cpt)++;
                        tcp_brut->ws=options->premier->octet;
                        options->premier=options->premier->next;
                        (*cpt)++;
                        continue;
                    }else{
                        if(options->premier->octet==4){
                            tcp_brut->sack_perm=1;
                            options->premier=options->premier->next;
                            (*cpt)++;
                            options->premier=options->premier->next;
                            (*cpt)++;
                            continue;
                        }else{
                            if(options->premier->octet==8){
                                printf("--------------------------------on va afficher timestamps\n");
                                options->premier=options->premier->next;
                                (*cpt)++;
                                options->premier=options->premier->next;
                                (*cpt)++;
                                for(int i=0;i<4;i++){
                                    tcp_brut->tsv[i]=options->premier->octet;
                                    options->premier=options->premier->next;
                                   (*cpt)++;
                                }
                                for(int i=0;i<4;i++){
                                    tcp_brut->terv[i]=options->premier->octet;
                                    options->premier=options->premier->next;
                                    (*cpt)++;
                                    continue;
                                }
                            }
                        }
                    }
                }
            }
        }
    
    }   
    
    return options;    
}

int generate_file(FILE* fichier,List_Printable*lp){
       
    
    
    if (fichier != NULL)
    {   
        if(lp==NULL ){
        printf("ERREUR la list_cell_printable est vide\n");
        return 0;
        }
    
        Cell_Printable *ite = lp->premier;
        // Parcours de la liste de printable
        char line[10000];
        while(ite != NULL)
        {
            
            generate_line_file(ite->printable,line);
            fputs(line,fichier);
            ite = ite->next;
        }
        fclose(fichier); // On ferme le fichier qui a été ouvert
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier ");
        return 0;
    }
    return 1;
   
}

int generate_line_file(Printable* p, char line[10000]){
    strcpy(line,p->ip_src);
    strcat(line,",");
    strcat(line,p->ip_dst);
    strcat(line,",");
    strcat(line,p->port_src);
    strcat(line,",");
    strcat(line,p->port_dst);
    strcat(line,",");
    strcat(line,p->type);
    strcat(line,",");
    strcat(line,p->comment);
    strcat(line,"\n");
    return 1;
    
}
    


