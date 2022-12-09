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
    Trame *trame, *paquet = create_cell_trame(-1);
    assert(paquet);
    int type;

    printf("========== TEST ETHERNET TRACE 1 ==========\n");
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


    printf("========== TEST ETHERNET TRACE 3 ==========\n");
    trace = get_trace("trace3.txt");
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


    printf("========== TEST ETHERNET TRACE COMPLETE TCP ==========\n");
    trace = get_trace("trace_complete_tcp.txt");
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


    printf("\n\n Toutes les trames :\n\n");
    trace = get_trace("trace_complete_tcp.txt");
    assert(trace);

    trame = trace->premier;

    while(trame != NULL)
    {
        type = read_ethernet(trame, &paquet);
        printf("type = %x\n", type);

        trame = trame->next;
    }

    // Libération de la trace
    free_trace(trace);

    // Libération du pointeur de paquet
    free(paquet);


    printf("========== TEST ETHERNET TRACE COMPLETE TCP ==========\n");
    trace = get_trace("trace_complete_tcp.txt");
    assert(trace);


    return 0;
}
