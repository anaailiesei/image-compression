#include <string.h>
#include "conditions.h"
#include "structs.h"

// Coreleaza argumentul primit cu tipul de optiune
int options(char *opt)
{
    if (strcmp(opt, "-c1") == 0)
        return c1;
    if (strcmp(opt, "-c2") == 0)
        return c2;
    if (strcmp(opt, "-d") == 0)
        return d;
    return -1;
}

// Verifica daca tipul fisierului .ppm e P6
int ppm_type(char *type)
{
    if (strcmp(type, "P6") != 0)
        return -1;
    return 0;
}

// Verifica daca un numar este puetre a lui 2
int check_power_2(unsigned int size)
{
    while (size % 2 == 0)
        size /= 2;
    if (size == 1)
        return 1;
    return 0;
}
