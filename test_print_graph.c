#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "analyse_trame.h"
#include "lecture_trame.h"
#include "print_graph.h"
#include <string.h>



int main(int argc, char const *argv[]){
    FILE* fic = NULL;
    fic = fopen("printf.txt", "w");
    int* lire_pos=NULL;

     init_graph(fic,6, 50,lire_pos, 10);

    //printf("cur_pos[%d] = %d\n",j,cur_pos[j]);
    return 0;
}
