#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "analyse_trame.h"
#include "lecture_trame.h"

/* Fichier test analyse trame */

int main(int argc, char const *argv[])
{
    // Déclarations
    Trace *trace;
    Trame *trame, *paquet = NULL;
    int type;

    printf("========== TEST ETHERNET 1 ==========\n");
    trace = get_trace("trace1.txt");
    assert(trace);

    trame = trace->premier;

    printf("Avant lecture : \n");
    print_trame(trame);

    type = read_ethernet(trame, &paquet);
    printf("type = %x\n", type);

    printf("Après lecture : \n");
    print_trame(paquet);

    // Libération de la trace
    free_trace(trace);

    free(paquet);

    return 0;
}
