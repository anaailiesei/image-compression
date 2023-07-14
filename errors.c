/* AILIESEI Ana-Maria 311CD*/

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

// Cand fisierul de input nu se poate deschide
void error_f_in(void)
{
    fprintf(stderr, "Nu s-a putut deschide fisierul de intrare!\n");
    exit(-1);
}

// Cand fisierul de output nu se poate deschide
void error_f_out(void)
{
    fprintf(stderr, "Nu s-a putut deschide fisierul de iesire!\n");
    exit(-1);
}

// Cand optiunea la rulare nu este c1, c2 sau d
void error_invalid_option(void)
{
    fprintf(stderr, "Optiune invalida!\n");
    exit(-1);
}

// Cand factorul e necorespunzator (negativ)
void error_factor(void)
{
    fprintf(stderr, "Factorul trebuie sa fie >= 0!\n");
    exit(-1);
}

// Cand s-a oferit un numar incorect de argumente
void error_arguments(void)
{
    fprintf(stderr, "Numar incorect de argumente!\n");
    exit(-1);
}

// Cand fisierul ppm nu este de tip P6
void error_ppm_type(void)
{
    fprintf(stderr, "Tipul fisierului input .ppm trebuie sa fie P6!\n");
    exit(-1);
}

// Cand imaginea nu e patratica sau dimensiunea ei nu e putere a lui 2
void error_size(void)
{
    fprintf(stderr, "Imaginea trebuie sa fie patratica.\n");
    fprintf(stderr, "Dimensiunea sa fie putere a lui 2\n");
    exit(-1);
}

// Cand valoarea maxima pentru culoare nu este 255
void error_color(void)
{
    fprintf(stderr, "Culorile trebuie sa aiba valoarea maxima 255!\n");
    exit(-1);
}

// Cand nu s-a putut aloca memorie
void error_alocare_memorie(void)
{
    fprintf(stderr, "Nu s-a putut aloca memorie!\n");
    exit(-1);
}

// Cand fisierul binar nu a fost creat corepsunzator
void error_fread(void)
{
    fprintf(stderr, "Fisierul binar nu are formatul corespunzator!\n");
    fprintf(stderr, "fread a esuat.\n");
    exit(-1);
}
