#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
//#include "lecture_trame.h"

int conversion_char_int_hexa(char c);
int conversion_double_chiffres(char c1, char c2);

int main(int argc, char const *argv[])
{
    printf("%d\n", conversion_char_int_hexa('a'));
    printf("%d\n", conversion_char_int_hexa('1'));
    printf("%d\n", conversion_char_int_hexa('f'));
    printf("%d\n", conversion_char_int_hexa(';'));

    printf("a = %d et f = %d\n", 'a', 'f');
    printf("0 = %d et 9 = %d\n", '0', '9');

    /*FILE *file = fopen("trace2.txt", "r");
    assert(file);

    int octet, cpt = 0;
    char c;

    while()

    printf("\n");
    fclose(file);*/

    return 0;
}

/* Fonction qui permet de convertir un caractère représentant
   un nombre héxadécimal (lettre en minuscules) en entier
   Retourne l'entier obtenu ou -1 si le caractère n'est pas un entier   */
int conversion_char_int_hexa(char c)
{
    switch(c)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'a':
            return 10;
        case 'b':
            return 11;
        case 'c':
            return 12;
        case 'd':
            return 13;
        case 'e':
            return 14;
        case 'f':
            return 15;
        default:
            return -1;
    }
}

/* Fonction qui permet de retourner la valeur d'un nombre
   hexadécimal écrit sur deux chiffres
   Retourne -1 en cas d'échec */
int conversion_double_chiffres(char c1, char c2)
{
    int a = conversion_char_int_hexa(c1);
    int b = conversion_char_int_hexa(c2);

    if(a < 0 || b < 0)
        return -1;
    
    return a * 10 + b;
}

/* Fonction qui permet de récupérer une trace à partir d'un 
   fichier 'nom_fic'
   Retourne un pointeur vers la trace en cas de succès et
   NULL sinon */
/*Trace *get_trace(char *nom_fic)
{
    // Déclarations
    FILE *file;
    Trace *trace = create_cell_trace();
    Trame *trame = NULL;
    Cell_octet *octet;
    int offset, val_octet, num = 0;
    int fin = 0;
    char c;

    file = fopen(nom_fic, "r");
    if(file == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du ficher %s\n", nom_fic);
        free_trace(trace);
        return NULL;
    }

    while(!feof(file)) // On boucle tant que l'on est pas à la fin du fichier
    {
        // Lecture d'une ligne

        // Lecture de l'offset
        if(fscanf(file, "%x", &offset) != 1)
        {
            //if(feof(file)) // Cas où l'on est à la fin du fichier
                //break;

            fprintf(stderr, "Erreur lors de la lecture de l'offset\n");
            free_trace(trace);
            return NULL;
        }

        if(offset == 0) // C'est une nouvelle trame
        {
            if(trame != NULL) // On ajoute la trame si ce n'est pas le tout premier tour de boucle
            {
                // Ajout de la trame précédente à la trace
                ajout_trame(trame, trace);
            }

            // Création d'une nouvelle trame
            trame = create_cell_trame(++num);
            assert(trame);
        }

        // On parcourt la ligne
        while(c = fgetc(file) != '\n')

        if(fin)
        {
            fin = 0;
            break;
        }
    }

    // Ajout de la dernière trame
    ajout_trame(trame, trace);

    if(fclose(file) == EOF)
    {
        fprintf(stderr, "Erreur lors de la fermeture du fichier %s", nom_fic);
        free_trace(trace);
        return NULL;
    }

    return trace;
}*/


/* Fonction qui permet de récupérer une trace à partir d'un 
   fichier 'nom_fic'
   Retourne un pointeur vers la trace en cas de succès et
   NULL sinon */
/*Trace *get_trace(char *nom_fic)
{
    // Déclarations
    FILE *file;
    Trace *trace = create_cell_trace();
    Trame *trame = NULL;
    Cell_octet *octet;
    int offset, val_octet, num = 0;
    int fin = 0;

    file = fopen(nom_fic, "r");
    if(file == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du ficher %s\n", nom_fic);
        free_trace(trace);
        return NULL;
    }

    while(!feof(file)) // On boucle tant que l'on est pas à la fin du fichier
    {
        // Lecture de l'offset
        if(fscanf(file, "%x", &offset) != 1)
        {
            if(feof(file)) // Cas où l'on est à la fin du fichier
                break;

            fprintf(stderr, "Erreur lors de la lecture de l'offset\n");
            free_trace(trace);
            return NULL;
        }

        if(offset == 0) // C'est une nouvelle trame
        {
            if(trame != NULL) // On ajoute la trame si ce n'est pas le tout premier tour de boucle
            {
                // Ajout de la trame précédente à la trace
                ajout_trame(trame, trace);
            }

            // Création d'une nouvelle trame
            trame = create_cell_trame(++num);
            assert(trame);
        }

        // On parcourt la ligne cad 16 octets
        for(unsigned i=0; i<16; i++)
        {
            // Lecture de l'octet courant
            if(fscanf(file, "%x", &val_octet) != 1)
            {
                // La ligne n'est pas remplie : fin de la trame
                fin = 1;
                break;

                //fprintf(stderr, "Erreur lors de la lecture de l'octet (trame : %d, offset : %d, octet : %d\n", num, offset, i);
                //free(trame);
                //free_trace(trace);
                //return NULL;
            }

            // Création d'une nouvelle cellule d'octet
            octet = create_cell_octet(val_octet);
            assert(octet);

            // Ajout de l'octet dans la trame courante
            ajout_octet(octet, trame);
        } 

        if(fin)
        {
            fin = 0;
            break;
        }
    }

    // Ajout de la dernière trame
    ajout_trame(trame, trace);

    if(fclose(file) == EOF)
    {
        fprintf(stderr, "Erreur lors de la fermeture du fichier %s", nom_fic);
        free_trace(trace);
        return NULL;
    }

    return trace;
}*/
