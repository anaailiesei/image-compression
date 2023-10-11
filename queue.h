#pragma once

#include "structs.h"

Queue * create_queue(void);
QNode *init_node(TreeNode *root);
int empty_queue(Queue *q);
Queue *enqueue(Queue *q, TreeNode *root, int *check);
void dequeue(Queue *q);
void free_queue(Queue *q);
