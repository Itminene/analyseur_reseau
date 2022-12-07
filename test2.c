#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
//#include "lecture_trame.h"

int conversion_char_int_hexa(char c);
int conversion_double_chiffres(char c1, char c2);
int hexa_to_bin(int num, char (*bin)[8]);


int main(int argc, char const *argv[])
{
    printf("%d\n", conversion_char_int_hexa('a'));
    printf("%d\n", conversion_char_int_hexa('1'));
    printf("%d\n", conversion_char_int_hexa('f'));
    printf("%d\n", conversion_char_int_hexa(';'));

    printf("a = %d et f = %d\n", 'a', 'f');
    printf("0 = %d et 9 = %d\n", '0', '9');

    char bin[8] = {'X', '1', '1', '1', '1', '1', '1', '1'};
    hexa_to_bin(123, &bin);
    printf("bin[0] = %c\n", bin[0]);

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

// Passage en paramètre : hexa_to_bin(num, &bin);

int hexa_to_bin(int num, char (*bin)[8])
{
    // Modification
    (*bin)[0] = '0';

    return 0;
}

