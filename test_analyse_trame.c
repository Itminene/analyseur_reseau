#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "analyse_trame.h"
#include "lecture_trame.h"
#include <string.h>


/* Fichier test analyse trame */

int main(int argc, char const *argv[])
{   
    /*printf("============Test hexa_to bin===============\n");
    char bin[8];
    int num=16;
    hexa_to_bin(num,bin);
    for(int i=0;i<8;i++){
        printf("bin[%d] = %c\n",i,bin[i]);
    }
    
    printf("=========TEST Conversion hexa->decimal======================\n");
    printf("Conversion 4octets->decimal\n");
    int hexa[4];
    hexa[0]=6;
    hexa[1]=116;
    hexa[2]=151;
    hexa[3]=132;
    printf("%x%x%x%x ===> %ld\n",hexa[0],hexa[1],hexa[2],hexa[3],quatres_octets_to_decimal(hexa));
    
    printf("Conversion 2octets->decimal\n");
    int hexa2[2];
    hexa2[0]=16;
    hexa2[1]=16;
    printf("%x%x ===> %d\n",hexa2[0],hexa2[1],deux_octets_to_decimal(hexa2));

    printf("=========TEST Fonctions read()======================\n");*/

    // Déclarations
    Trace *trace=get_trace("trace1.txt");
    assert(trace);
    /*Trame *trame= trace->premier;
   
    
    
    printf("\n========== TEST READ_ETHERNET 1 ==========\n");
    printf("La trame contient paquet ip -> : %d\n",read_ethernet(trame));
   
    printf("=========TEST READ_IP======================\n");
    printf("La trame contient segment tcp ->: %d\n",read_ip(trame));

    printf("=========TEST GET_IP======================\n");
    int ip_src[8];
    int ip_dst[8];
    Trame *segment=NULL;
    printf("Valeur de retour : %d\n",get_ip(trame,&segment,ip_src,ip_dst));
    
    //affichage des tableaux ip src et dst
    for(unsigned  i=0;i<4;i++){
        printf("ip_src[%d]=%d  ip_dst[%d]=%d \n",i,ip_src[i],i,ip_dst[i]);
    }
    printf("1er octet du segment tcp : %0x\n",segment->premier->octet);

    printf("=========TEST READ_TCP======================\n");
    printf("La trame contient donnée http ->: %d\n",read_tcp(segment));

    printf("=========TEST GET_TCP======================\n");
    
    Trame* data;

    Tcp_brut* tcp_brut=get_tcp(segment,&data,ip_src,ip_dst);
    printf("port src : %0x %0x\n",tcp_brut->port_src[0],tcp_brut->port_src[1]);
    printf("port dst : %0x %0x\n",tcp_brut->port_dst[0],tcp_brut->port_dst[1]);
    printf("seq : %0x %0x %0x %0x\n",tcp_brut->seq[0],tcp_brut->seq[1],tcp_brut->seq[2],tcp_brut->seq[3]);
    printf("ack : %0x %0x %0x %0x\n",tcp_brut->ack[0],tcp_brut->ack[1],tcp_brut->ack[2],tcp_brut->ack[3]);
    printf("affichage des flags:\n");
    for(unsigned i=0;i<8;i++){
        printf("flag[%d]= %c\n",i,tcp_brut->flags[i]);
    }
    for(unsigned i=0;i<2;i++){
        printf("win[%d] : %0x\n",i,tcp_brut->win[i]);
    }
    

    printf("=========TEST trame_brut_to_str======================\n");
    Cell_Printable* cp=trame_brut_to_str(trame);
    if(cp==NULL){
        printf("la trame n'est pas printable\n");
    }else{
        print_printable(cp->printable);
    }
    free_cell_printable(cp);
    //free(data);
    //free(segment);
    //free(tcp_brut);*/
    
    printf("=========TEST trame_brut_to_str======================\n");
    
    List_Printable* lp=trace_brut_to_str( trace);
    print_list_cell_printable(lp);
    
    FILE* fichier = NULL;
    fichier = fopen("printf.txt", "w");
    generate_file(fichier,lp);

    free_list_Printable(lp);
    free_trace(trace);
     

    return 0;
}
