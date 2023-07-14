/* AILIESEI Ana-Maria 311CD*/

#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

/*
Inchide fisierele deschise
*/
void close_files(FILE *f_in, FILE *f_out)
{
    if (f_in)
        fclose(f_in);
    if (f_out)
        fclose(f_out);
}

///////////// CERINTA 1 ///////////////

/*
Aloca memorie pentru matricea imaginii
Returneaza matricea creata
*/
Grid *create_image_matrix(unsigned int size)
{
    unsigned int i = 0, j = 0, k = 0;

    RGB **grid = NULL;
    Grid *image = NULL;

    image = malloc(sizeof(Grid));
    if (!image)
        return NULL;

    grid = malloc(size * sizeof(RGB *));
    if (!grid) {
        free(image);
        return NULL;
    }

    for (i = 0; i < size; i++) {
        grid[i] = malloc(size * sizeof(RGB));

        if (!grid[i]) {
            for (j = 0; j < i; j++)
                free(grid[j]);
            free(grid);
            free(image);
            return NULL;
        }
    }
    image->grid = grid;
    image->size = size;
    return image;
}

/*
Elibereaza memoria pentru matricea imaginii
*/
void free_image_matrix(Grid *image)
{
    unsigned int i = 0, j = 0;

    for (i = 0; i < image->size; i++)
        free(image->grid[i]);
    free(image->grid);
    free(image);
    image = NULL;
}

/*
Creeaza un arbore cuaternar
Nodul creat e de tip 1 (by default e nod frunza)
*/
Tree create_tree(RGB pixel)
{
    Tree root = malloc(sizeof(TreeNode));

    if (!root)
        return NULL;

    root->type = 1;
    root->left_up = NULL;
    root->right_up = NULL;
    root->right_down = NULL;
    root->left_down = NULL;
    root->pixel = pixel;
    return root;
}

/*
Calculeaza culoarea medie in RGB pentru un block
*/
RGB mean_color(RGB **grid, Square block)
{
    unsigned long long sum_red = 0, sum_green = 0, sum_blue = 0;
    unsigned int x = block.coord_x;
    unsigned int y = block.coord_y;
    unsigned int size = block.size;
    unsigned int i = 0, j = 0;
    RGB mean;

    for (i = x; i < (size + x); i++)
        for (j = y; j < (size + y); j++) {
            sum_red += grid[i][j].red;
            sum_green += grid[i][j].green;
            sum_blue += grid[i][j].blue;
        }
    mean.red = (unsigned char)(sum_red / (size * size));
    mean.green = (unsigned char)(sum_green / (size * size));
    mean.blue = (unsigned char)(sum_blue / (size * size));
    return mean;
}

/*
Calculeaza scorul de similaritate
*/
double similarity_score(RGB **grid, Square block, RGB mean)
{
    unsigned long long sum = 0;
    unsigned int diff_red = 0, diff_green = 0, diff_blue = 0;
    unsigned int x = block.coord_x;
    unsigned int y = block.coord_y;
    unsigned int size = block.size;
    unsigned int i = 0, j = 0;
    double score = 0;

    for (i = x; i < (x + size); i++)
        for (j = y; j < (y + size); j++) {
            if (mean.red >= grid[i][j].red)
                diff_red = mean.red - grid[i][j].red;
            else
                diff_red = grid[i][j].red - mean.red;
            if (mean.green >= grid[i][j].green)
                diff_green = mean.green - grid[i][j].green;
            else
                diff_green = grid[i][j].green - mean.green;
            if (mean.blue >= grid[i][j].blue)
                diff_blue = mean.blue - grid[i][j].blue;
            else
                diff_blue = grid[i][j].blue - mean.blue;
            sum += diff_red * diff_red;
            sum += diff_green * diff_green;
            sum += diff_blue * diff_blue;
        }
    score = (double)(sum / (size * size * 3));
    return score;
}

/*
Separa un bloc si returneaza blocul din stanga sus
*/
Square split_left_up(Square block)
{
    Square left_up;

    left_up.size = block.size / 2;
    left_up.coord_x = block.coord_x;
    left_up.coord_y = block.coord_y;

    return left_up;
}

/*
Separa un bloc si returneaza blocul din dreapta sus
*/
Square split_right_up(Square block)
{
    Square right_up;

    right_up.size = block.size / 2;
    right_up.coord_x = block.coord_x;
    right_up.coord_y = block.coord_y + right_up.size;

    return right_up;
}

/*
Separa un bloc si returneaza blocul din drepata jos
*/
Square split_right_down(Square block)
{
    Square right_down;

    right_down.size = block.size / 2;
    right_down.coord_x = block.coord_x + right_down.size;
    right_down.coord_y = block.coord_y + right_down.size;

    return right_down;
}

/*
Separa un bloc si returneaza blocul din stanga jos
*/
Square split_left_down(Square block)
{
    Square left_down;

    left_down.size = block.size / 2;
    left_down.coord_x = block.coord_x + left_down.size;
    left_down.coord_y = block.coord_y;

    return left_down;
}

/*
Construieste un arbore de compresie si preia informatiile necesare pentru cerinta 1
*/
Tree construct_tree(Tree root, Grid *image, Square block,
                    int *check, C1 *info, int factor)
{
    RGB mean = mean_color(image->grid, block);
    double score = similarity_score(image->grid, block, mean);
    Square left_up, right_up, right_down, left_down;

    if (!root)
        root = create_tree(mean);
    if (!root) {
        *check = -1;
        return root;
    }

    if ((int)score <= factor) {
        info->nr_blocks++;
        if (info->max_block_size < block.size)
            info->max_block_size = block.size;
        return root;
    } else {
        root->type = 0;
        left_up = split_left_up(block);
        right_up = split_right_up(block);
        right_down = split_right_down(block);
        left_down = split_left_down(block);
        root->left_up = construct_tree(root->left_up, image, left_up,
                                       check, info, factor);
        root->right_up = construct_tree(root->right_up, image, right_up,
                                        check, info, factor);
        root->right_down = construct_tree(root->right_down, image, right_down,
                                          check, info, factor);
        root->left_down = construct_tree(root->left_down, image, left_down,
                                         check, info, factor);
    }
    return root;
}

/*
Elibereaza memoria pentru un arbore cuaternar
*/
void free_tree(Tree root)
{
	if (!root)
		return;

	free_tree(root->left_up);
	free_tree(root->right_up);
    free_tree(root->right_down);
    free_tree(root->left_down);

	free(root);
}

/*
Initializeaza valorile din structura cu informatii pentru prima cerinta
*/
void initiate_c1_info(C1 *info)
{
    info->depth = 0;
    info->max_block_size = 0;
    info->nr_blocks = 0;
}

/*
Realizeaza arborele de compresie
*/
Tree make_compression_tree(Grid *image, C1 *info, int factor)
{
    Square block;
    Tree root = NULL;
    int check = 0;

    block.coord_x = 0;
    block.coord_y = 0;
    block.size = image->size;

    root = construct_tree(root, image, block, &check, info, factor);

    if (check != 0)
        free_tree(root);

    return root;
}

/*
returneaza amximul dintre doua numere
*/
unsigned int maximum(unsigned int a, unsigned int b)
{
    if (a > b)
        return a;
    return b;
}

/*
Calculeaza inaltimea arborelui cuaternar
*/
unsigned int tree_depth(Tree root)
{
    if (!root)
        return 0;

    unsigned int left_up = tree_depth(root->left_up);
    unsigned int right_up = tree_depth(root->right_up);
    unsigned int right_down = tree_depth(root->right_down);
    unsigned int left_down = tree_depth(root->left_down);
    unsigned int max = 0;

    max = maximum(left_up, right_up);
    max = maximum(max, right_down);
    max = maximum(max, left_down);

    return max + 1;
}

/*
Printeaza intr-un fisier binar informatiile aferente primei cerinte
*/
void print_c1(FILE *f_out, C1 info)
{
    if (!f_out)
        return;
    fprintf(f_out, "%i\n", info.depth);
    fprintf(f_out, "%i\n", info.nr_blocks);
    fprintf(f_out, "%i\n", info.max_block_size);
}

///////////// CERINTA 2 ///////////////

/*
Printeaza un nod
*/
void print_node(FILE *f_out, TreeNode *node)
{
    int size = sizeof(unsigned char);

    if (!node)
        return;

    fwrite(&node->type, size, 1, f_out);
    if (node->type == 1) {
        fwrite(&node->pixel.red, size, 1, f_out);
        fwrite(&node->pixel.green, size, 1, f_out);
        fwrite(&node->pixel.blue, size, 1, f_out);
    }
}

/*
Printeaza un intreg nivel din arborele cuaternar
*/
void print_current_level(FILE *f_out, Tree root, unsigned int level)
{
    if (!root)
        return;

    if (level == 1) {
        print_node(f_out, root);
        return;
    } else if (level > 1) {
        print_current_level(f_out, root->left_up, level - 1);
        print_current_level(f_out, root->right_up, level - 1);
        print_current_level(f_out, root->right_down, level - 1);
        print_current_level(f_out, root->left_down, level - 1);
    }
}

/*
Printeaza nodurile dintr-un arbore cuaternar in ordinea nivelelor
*/
void print_in_level_order(FILE *f_out, Tree root)
{
    unsigned int depth = tree_depth(root);
    int i = 0;

    for (i = 0; i < depth; i++)
        print_current_level(f_out, root, i + 1);
}

///////////// CERINTA 2 ///////////////

/*
Insereaza un nod in arborele cuaternar
*/
Tree insert_node(Tree root, TreeNode *node, Queue *q, int *check)
{
    TreeNode *current = NULL;

    if (q->head)
        current = q->head->node;

    if (!root) {
        root = node;
    } else if (!current->left_up) {
        current->left_up = node;
    } else if (!current->right_up) {
        current->right_up = node;
    } else if (!current->right_down) {
        current->right_down = node;
    } else {
        current->left_down = node;
        dequeue(q);
    }
    if (node->type == 0)
        enqueue(q, node, check);
    return root;
}

/*
Citeste arborele din fisierul binar si il reface
*/
Tree read_and_make_tree(FILE *f_in, int *check)
{
    unsigned char type = 0;
    int size = sizeof(unsigned char);
    Tree root = NULL;
    TreeNode *node = NULL;
    RGB pixel;
    Queue *q = NULL;
    unsigned long return_fread = 1;

    q = create_queue();
    if (!q) {
        *check = -1;
        return root;
    }

    while (return_fread) {
        if (*check != 0) {
            free_queue(q);
            return root;
        }

        return_fread = fread(&type, size, 1, f_in);
        if (return_fread != 1) {
            free_queue(q);
            return root;
        }

        if (type == 1) {
            return_fread = fread(&pixel.red, size, 1, f_in);
            if (return_fread != 1) {
                *check = 1;
                free_queue(q);
                return root;
            }

            return_fread = fread(&pixel.green, size, 1, f_in);
            if (return_fread != 1) {
                *check = 1;
                free_queue(q);
                return root;
            }

            return_fread = fread(&pixel.blue, size, 1, f_in);
            if (return_fread != 1) {
                *check = 1;
                free_queue(q);
                return root;
            }
        } else if (type == 0) {
            pixel.red = 0;
            pixel.green = 0;
            pixel.blue = 0;
        }
        node = create_tree(pixel);
        if (!node) {
            *check = -1;
            return root;
        }

        node->type = type;
        root = insert_node(root, node, q, check);
    }
    free_queue(q);
    return root;
}

/*
Insereaza un nod in matricea imagine
*/
void put_block_in_matrix(Grid *image, TreeNode *node, Square block)
{
    unsigned int i = 0, j = 0;
    unsigned int size = block.size;
    unsigned int x = block.coord_x;
    unsigned int y = block.coord_y;

    for (i = x; i < (x + size); i++)
        for (j = y; j < (y + size); j++)
            image->grid[i][j] = node->pixel;
}

/*
Transforma arborele cuaternar in matricea imagine
*/
void decompression(Grid *image, Tree root, Square block)
{
    Square left_up, right_up, right_down, left_down;

    if (!root)
        return;

    if (root->type == 1) {
        put_block_in_matrix(image, root, block);
        return;
    }

    left_up = split_left_up(block);
    right_up = split_right_up(block);
    right_down = split_right_down(block);
    left_down = split_left_down(block);

    decompression(image, root->left_up, left_up);
    decompression(image, root->right_up, right_up);
    decompression(image, root->right_down, right_down);
    decompression(image, root->left_down, left_down);
}

/*
Functia care realizeaza matricea imagine
*/
Grid *make_matrix_from_tree(Tree root, unsigned int size)
{
    Grid *image = create_image_matrix(size);
    Square block;

    if (!image)
        return NULL;

    block.coord_x = 0;
    block.coord_y = 0;
    block.size = image->size;

    decompression(image, root, block);

    return image;
}
