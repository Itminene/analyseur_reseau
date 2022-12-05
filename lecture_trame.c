#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lecture_trame.h"


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
    
    return a * 16 + b;
}

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
    char c, c2;

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
            if(feof(file)) // Cas où l'on est à la fin du fichier
                break;

            fprintf(stderr, "Erreur lors de la lecture de l'offset\n");
            free_trace(trace);
            return NULL;
        }

        if(offset == 0) // C'est une nouvelle trame
        {
            fprintf(stderr, "Nouvelle Trame ! (%d)\n", num + 1);
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

        // Les 3 espaces
        for(unsigned i=0; i<3; i++)
        {
            c = fgetc(file);
            if(c != ' ')
                fprintf(stderr, "Problème de format (espace)\n");
        }

        // On lit au moins un octet, au plus 16 octets
        for(unsigned i=0; i<16; i++)
        {
            // Lecture de l'octet courant
            c = fgetc(file);

            // Ce n'est pas un chiffre en hexa : plus d'octet à lire sur cette ligne
            if((c < '0' || c > '9') && (c < 'a' || c > 'f'))
            {
                //fprintf(stderr, "Ce n'est pas un chiffre en hexa (c = '%c')\n", c);
                break;
            }
            
            c2 = fgetc(file);

            //fprintf(stderr, "c = %c, c2 = %c\n", c, c2);

            // Initialisation valeur octet
            val_octet = conversion_double_chiffres(c, c2);
            //fprintf(stderr, "val_octet = %d\n", val_octet);
            assert(val_octet >= 0 && val_octet <= 255);

            // Création d'une nouvelle cellule d'octet
            octet = create_cell_octet(val_octet);
            assert(octet);

            // Ajout de l'octet dans la trame courante
            ajout_octet(octet, trame);

            // Lecture de l'espace
            c = fgetc(file);
        }

        // Lecture jusqu'à la fin de la ligne ou du fichier
        while(c != '\n' && !feof(file))
        {
            c = fgetc(file);
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