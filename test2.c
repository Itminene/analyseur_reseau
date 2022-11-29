#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lecture_trame.h"

int main(int argc, char const *argv[])
{
    FILE *file = fopen("trace1.txt", "r");
    assert(file);

    int octet;
    int cpt = 0;

    while(!feof(file))
    {
        if(fscanf(file, "%x", &octet) != 1)
        {
            printf("Fin du fichier ? %s\n", feof(file) ? "oui" : "non");
            break;
        }

        if(cpt%17 == 0)
            printf("\n");

        printf("%x ", octet);
        cpt++;
    }
    printf("\n");
    fclose(file);

    return 0;
}
