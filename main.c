#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "errors.h"
#include "conditions.h"
#include "structs.h"

#define max 255
#define argc12 5
#define argc3 4

int main(int argc, char *argv[])
{
    FILE *f_in = NULL, *f_out = NULL;
    int factor = 0, check = 0;
    char file_type[2] = {0};
    unsigned int width = 0, height = 0, size = 0;
    unsigned char max_color = 0;
    unsigned int i = 0, j = 0;
    Grid *image_matrix = NULL;

    RGB **grid = NULL;
    Tree compression_tree = NULL;
    C1 info;

    // Daca exista 5 argumente (optiunile c1 si c2)
    // Se preiau argumentele pentru factor, f_input si f_output
    if (argc == argc12) {
        f_in = fopen(argv[3], "r");
        if (!f_in)
            error_f_in();

        f_out = fopen(argv[4], "w");
        if (!f_in)
            error_f_out();

        factor = atoi(argv[2]);
        if (factor < 0) {
            close_files(f_in, f_out);
            error_factor();
        }

    // Daca exista 4 argumente (optiunea d)
    // Se preiau argumentele pentru f_input si f_output
    } else if (argc == argc3) {
        f_in = fopen(argv[2], "r");
        if (!f_in)
            error_f_in();

        f_out = fopen(argv[3], "w");
        if (!f_in)
            error_f_out();

    // Daca exista un numar invalid de argumente (<4 sau >5) => eroare
    } else {
        error_arguments();
    }

    // Daca optiunea e invalida => eroare
    if (options(argv[1]) < 0) {
        close_files(f_in, f_out);
        error_invalid_option();
    }

    // Daca se aleg optiunile c1 sau c2
    if ((options(argv[1]) == c1) || (options(argv[1]) == c2)) {
        // Daca tipul fisierului .ppm nu e P6 => eroare
        fscanf(f_in, "%s\n", file_type);
        if (ppm_type(file_type) < 0) {
            close_files(f_in, f_out);
            error_ppm_type();
        }

        // Daca imaginea nu e patratica => eroare
        fscanf(f_in, "%i %i", &height, &width);
        if (height != width) {
            close_files(f_in, f_out);
            error_size();
        }

        // Daca dimensiunea imaginii nu e putere a lui 2 => eroare
        if (check_power_2(height) == 0) {
            close_files(f_in, f_out);
            error_size();
        }

        size = height;

        // Daca valoarea maxima citita pentru culoare nu este 255 => eroare
        fscanf(f_in, "%hhu", &max_color);
        if (max_color != max) {
            close_files(f_in, f_out);
            error_color();
        }

        fseek(f_in, 1, SEEK_CUR);

        // Se aloca memorie pentru matricea imaginii.
        // Daca nu se poate aloca memorie => eroare
        image_matrix = create_image_matrix(size);
        if (!image_matrix) {
            close_files(f_in, f_out);
            error_alocare_memorie();
        }

        // Se completeaza matricea cu valori
        grid = image_matrix->grid;
        for (i = 0; i < size; i++)
            for (j = 0; j < size; j++) {
                fread(&grid[i][j].red, sizeof(unsigned char), 1, f_in);
                fread(&grid[i][j].green, sizeof(unsigned char), 1, f_in);
                fread(&grid[i][j].blue, sizeof(unsigned char), 1, f_in);
            }

        // Se initiaza valorile pt c1 la 0
        initiate_c1_info(&info);

        // Se realizeaza arborele de compresie + informatiile pt cerinta 1
        // Daca este NULL, nu s-a putut aloca memorie => eroare
        compression_tree = make_compression_tree(image_matrix, &info, factor);
        if (!compression_tree) {
            free_image_matrix(image_matrix);
            close_files(f_in, f_out);
            error_alocare_memorie();
        }
    }

    // Daca se alege optiunea c1
    if (options(argv[1]) == c1) {
        // Se calculeaza inaltimea arborelui
        info.depth = tree_depth(compression_tree);

        // Se printeaza rezultatele
        print_c1(f_out, info);
    }

    // Daca se alege optiunea c2
    if (options(argv[1]) == c2) {
        // Se scrie in fisier dimenisunea imaginii
        fwrite(&size, sizeof(unsigned int), 1, f_out);

        // fprintf(f_out, "size = %i\n", size);

        // Se scriu in fisier nodurile din arbore pe nivele
        print_in_level_order(f_out, compression_tree);
    }

    // Daca se alege optiunea d
    if (options(argv[1]) == d) {
        check = 0;
        // Se citeste dimensiunea imaginii
        fread(&size, sizeof(unsigned int), 1, f_in);
        // Se citeste si creeaza arborele de compresie
        compression_tree = read_and_make_tree(f_in, &check);

        if (!compression_tree) {
            close_files(f_in, f_out);
            error_alocare_memorie();
        }
        if (check != 0) {
            if (compression_tree)
                free_tree(compression_tree);
            close_files(f_in, f_out);
        }
        if (check == -1)
            error_alocare_memorie();
        else if (check == 1)
            error_fread();

        // Se aloca memorie pentru matricea imaginii.
        // Daca nu se poate aloca memorie => eroare
        image_matrix = make_matrix_from_tree(compression_tree, size);
        if (!image_matrix) {
            free_tree(compression_tree);
            close_files(f_in, f_out);
            error_alocare_memorie();
        }
        fprintf(f_out, "%s\n", "P6");
        fprintf(f_out, "%i %i\n", size, size);
        fprintf(f_out, "%hhu\n", max);

        grid = image_matrix->grid;
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                fwrite(&grid[i][j].red, sizeof(unsigned char), 1, f_out);
                fwrite(&grid[i][j].green, sizeof(unsigned char), 1, f_out);
                fwrite(&grid[i][j].blue, sizeof(unsigned char), 1, f_out);
            }
        }
    }

    // Se elibereaza toata memoria utilizata si se iese din program
    free_tree(compression_tree);
    free_image_matrix(image_matrix);
    image_matrix = NULL;
    grid = NULL;
    close_files(f_in, f_out);
    return 0;
}
