#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lecture_trame.h"

/* Fonction qui créé une nouvelle cellule de trace initialement vide
   nb_trame correspond au nombre de trames de la trace
   Retourne le pointeur vers la trace en cas de succès et NULL sinon */
Trace *create_cell_trace()
{
    Trace *nv = malloc(sizeof(Trace));
    if(nv == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de la trace");
        return NULL;
    }

    nv->nb_trames = 0;
    nv->premier = NULL;
    nv->dernier = NULL;

    return nv;
}

/* Fonction qui crée une nouvelle cellule de trame initialement vide
   num correspond à un identifiant de la trame (1 pour la première trame
   lue, 2 pour la 2e, etc.)
   Retourne le pointeur vers la trame en cas de succès et NULL sinon */
Trame *create_cell_trame(int num)
{
    Trame *nv = malloc(sizeof(Trame));
    if(nv == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de la trame");
        return NULL;
    }

    nv->num = num;
    nv->premier = NULL;
    nv->dernier = NULL;
    nv->next = NULL;
    nv->before = NULL;

    return nv;
}

/* Fonction qui crée une nouvelle cellule d'octet qui contient la valeur 
   de l'octet et le pointeur vers l'octet suivant (NULL initialement et si
   c'est le dernier) */
Cell_octet *create_cell_octet(int valeur)
{
    Cell_octet *nv = malloc(sizeof(Cell_octet));
    if(nv == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de la Cell_octet");
        return NULL;
    }

    nv->octet = valeur;
    nv->next = NULL;
    nv->before = NULL;

    return nv;
}

/* Fonction qui libère une cellule d'octet 
   Retourne 1 si celle-ci a bien été libérée et 0 sinon */
int free_octet(Cell_octet *octet)
{
    free(octet);
    return 1;
}

/* Fonction qui libère une trame avec tous ses octets
   Retourne 1 si celle-ci a bien été libérée et 0 sinon */
int free_trame(Trame* t)
{
    // Déclarations
    Cell_octet *ite = t->premier;
    Cell_octet *tmp;

    // Parcours de la liste d'octet de la trame
    while(ite != NULL)
    {
        tmp = ite;
        ite = ite->next;
        free_octet(tmp);
    }

    // Libération de la cellule de trame
    free(t);

    return 1;
}

/* Fonction qui libère une trace avec toutes ses trames
   Retourne 1 si celle-ci a bien été libérée et 0 sinon */
int free_trace(Trace *t)
{
    // Déclarations
    Trame *ite = t->premier;
    Trame *tmp;

    // Parcours de la liste de trames de la trace
    while(ite != NULL)
    {
        tmp = ite;
        ite = ite->next;
        free_trame(tmp);
    }

    // Libération de la cellule de trace
    free(t);
    
    return 1;
}

/* Fonction qui ajoute un octet en tête de trame */
void ajout_octet(Cell_octet *octet, Trame *trame)
{
    // Cas où c'est le premier octet
    if(trame->premier == NULL)
    {
        trame->premier = octet;
        trame->dernier = octet;
    }
    else
    {
        trame->dernier->next = octet;
        octet->before = trame->dernier;
        trame->dernier = octet;
    }
}

/* Fonction qui ajoute une trame en tête d'une liste de trames
   dans une trace */
void ajout_trame(Trame *trame, Trace *trace)
{
    // Première trame de la trace
    if(trace->premier == NULL)
    {
        assert(trace->nb_trames == 0);
        trace->premier = trame;
        trace->dernier = trame;
    }
    else
    {
        assert(trace->nb_trames > 0);
        trace->dernier->next = trame;
        trame->before = trace->dernier;
        trace->dernier = trame;
    }

    trace->nb_trames++;
}

/* Fonction qui permet d'afficher les octets de la trame sous
   forme hexadécimal */
void print_trame(Trame *t)
{
    // Déclarations
    Cell_octet *cell_ite = t->premier;
    int i;

    // Parcours de la trame
    while (cell_ite != NULL)
    {
        i = 0;
        printf("    ");
        while(i < 16 && cell_ite != NULL)
        {
            printf("%x ", cell_ite->octet);
            cell_ite = cell_ite->next;
            i++;
        }
        printf("\n");
    }
    printf("\n");
}

/* Fonction qui permet d'afficher le numéro de chaque trame
   de la trace */
void print_trace(Trace *t)
{
    Trame *ite = t->premier;

    // Parcours de la liste de trames
    while(ite != NULL)
    {
        printf("%d\n", ite->num);
        print_trame(ite);
        ite = ite->next;
    }
    printf("\n");
}

/* Fonction qui permet de récupérer une trace à partir d'un 
   fichier 'nom_fic'
   Retourne un pointeur vers la trace en cas de succès et
   NULL sinon */
Trace *get_trace(char *nom_fic)
{
    // Déclarations
    FILE *file;
    Trace *trace = create_cell_trace();
    Trame *trame = NULL;
    Cell_octet *octet;
    int offset, val_octet, num = 0;

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
                fprintf(stderr, "Erreur lors de la lecture de l'octet (trame : %d, offset : %d, octet : %d\n", num, offset, i);
                free(trame);
                free_trace(trace);
                return NULL;
            }

            // Création d'une nouvelle cellule d'octet
            octet = create_cell_octet(val_octet);
            assert(octet);

            // Ajout de l'octet dans la trame courante
            ajout_octet(octet, trame);
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
}