#pragma once
#include <stdio.h>
#include "structs.h"
#include "queue.h"

void close_files(FILE *f_in, FILE *f_out);
Grid *create_image_matrix(unsigned int size);
void free_image_matrix(Grid *image);
RGB mean_color(RGB **grid, Square block);
double similarity_score(RGB **grid, Square block, RGB mean);
Square split_left_up(Square block);
Square split_right_up(Square block);
Square split_right_down(Square block);
Square split_left_down(Square block);
Tree construct_tree(Tree root, Grid *image, Square block,
                    int *check, C1 *info, int factor);
void free_tree(Tree root);
void initiate_c1_info(C1 *info);
Tree make_compression_tree(Grid *image, C1 *info, int factor);
unsigned int maximum(unsigned int a, unsigned int b);
unsigned int tree_depth(Tree root);
void print_c1(FILE *f_out, C1 info);
void print_node(FILE *f_out, TreeNode *node);
void print_current_level(FILE *f_out, Tree root, unsigned int level);
void print_in_level_order(FILE *f_out, Tree root);
Tree read_and_make_tree(FILE *f_in, int *check);
void put_block_in_matrix(Grid *image, TreeNode *node, Square block);
void decompression(Grid *image, Tree root, Square block);
Grid *make_matrix_from_tree(Tree root, unsigned int size);
Tree insert_node(Tree root, TreeNode *node, Queue *q, int *check);
