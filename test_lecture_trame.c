#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lecture_trame.h"

/* Fichier test lecture_trame */

int main(int argc, char const *argv[])
{
    printf("========== TESTS CONVERSIONS ==========\n");

    printf("test 1 : %s\n", conversion_double_chiffres('0', 'a') == 10 ? "succès" : "échec");
    printf("test 2 : %s\n", conversion_double_chiffres('a', '0') == 160 ? "succès" : "échec");
    printf("test 3 : %s\n", conversion_double_chiffres('f', 'f') == 255 ? "succès" : "échec");
    printf("test 4 : %s\n", conversion_double_chiffres('0', '0') == 0 ? "succès" : "échec");
    printf("test 5 : %s\n", conversion_double_chiffres('x', 'a') == -1 ? "succès" : "échec");

    /* Création de 40 cellules d'octets que l'on ajoute à une trame */
    printf("\n========== TEST 1 ==========\n");

    // Déclarations
    Cell_octet *octet;
    Trame *trame = create_cell_trame(1);

    assert(trame);

    for(unsigned i=0; i<40; i++)
    {
        octet = create_cell_octet(i);
        assert(octet);
        ajout_octet(octet, trame);
    }

    /* Affichage de la trame */
    print_trame(trame);

    /* Libération de la trame */
    free_trame(trame);

    printf("\n\n");


    /* Création de 10 trames que l'on ajoute à une trace */
    printf("========== TEST 2 ==========\n");

    // Déclarations
    Trace *trace = create_cell_trace();

    for(unsigned i=1; i<11; i++)
    {
        trame = create_cell_trame(i);
        assert(trame);

        // Ajout d'octet dans la trame courante
        for(unsigned j=0; j<40+i; j++)
        {
            octet = create_cell_octet(j);
            assert(octet);
            ajout_octet(octet, trame);
        }

        // Ajout de la trame dans la trace
        ajout_trame(trame, trace);
    }

    /* Affichage de la trace */
    print_trace(trace);

    /* Libération de la trace */
    free_trace(trace);


    /* Récupération d'une trace à partir d'un fichier */
    printf("========== TEST 3 ==========\n");

    trace = get_trace("trace2.txt");
    assert(trace);

    /* Affichage de la trace */
    print_trace(trace);

    /* Libération de la trace */
    free_trace(trace);


    /* Récupération d'une trace à partir d'un fichier */
    printf("========== TEST 4 ==========\n");

    trace = get_trace("trace1.txt");
    assert(trace);

    /* Affichage de la trace */
    print_trace(trace);

    /* Libération de la trace */
    free_trace(trace);


    /* Récupération d'une trace à partir d'un fichier */
    printf("========== TEST 5 ==========\n");

    trace = get_trace("trace_complete_tcp.txt");
    assert(trace);

    /* Affichage de la trace */
    print_trace(trace);

    /* Libération de la trace */
    free_trace(trace);


    /* Récupération d'une trace à partir d'un fichier */
    printf("========== TEST 6 ==========\n");

    trace = get_trace("trace3.txt");
    assert(trace);

    /* Affichage de la trace */
    print_trace(trace);

    /* Libération de la trace */
    free_trace(trace);

    return 0;
}

