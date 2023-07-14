/* AILIESEI Ana-Maria 311CD*/

#pragma once

// Structura pentru un pixel
typedef struct RGB {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} RGB;

// Structura pentru un patrat
typedef struct Square {
    unsigned int size;
    unsigned int coord_x;
    unsigned int coord_y;
} Square;

// Structura pentru o matrice de pixeli
typedef struct Grid {
    RGB **grid;
    unsigned int size;
} Grid;

// Structura pentru quadtree
typedef struct Tree {
    unsigned char type;
    struct Tree *left_up, *right_up;
    struct Tree *right_down, *left_down;
    RGB pixel;
} TreeNode, *Tree;

// Enumeratie pentru optiunile alese la rulare
enum options {
    c1, c2, d
};

// Structura pentru informatiile necesare primei cerinte
typedef struct cerinta1 {
    unsigned int max_block_size;
    unsigned int nr_blocks;
    unsigned int depth;
} C1;

// Structura pentru un nod din coada
typedef struct que_node {
    struct que_node *next;
    TreeNode *node;
} QNode;

// structura pentru o coada
typedef struct queue {
    QNode *head;
    QNode *tail;
    unsigned int size;
} Queue;
