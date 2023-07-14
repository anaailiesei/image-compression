/* AILIESEI Ana-Maria 311CD */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Creeaza o coada
Queue *create_queue(void)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));

    if (!q)
        return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

// Initializeaza un nod pentru coada
QNode *init_node(TreeNode *root)
{
    QNode *node = (QNode *)malloc(sizeof(QNode));

    if (!node)
        return NULL;

    node->next = NULL;
    node->node = root;
    return node;
}

// Verifica daca o coada este goala
int empty_queue(Queue *q)
{
    if (q->size == 0)
        return 1;
    return 0;
}

// Adauga un nod la finalul cozii
Queue *enqueue(Queue *q, TreeNode *root, int *check)
{
    QNode *node = NULL;

    if (!q)
        q = create_queue();
    if (!q) {
        *check = -1;
        return NULL;
    }

    node = init_node(root);
    if (!node) {
        *check = -1;
        return q;
    }

    if (empty_queue(q)) {
        q->head = node;
        q->head->next = NULL;
        q->tail = node;
        q->tail->next = NULL;
        q->size++;
        return q;
    }

    if (!q->head->next) {
        q->head->next = node;
        q->tail = node;
        q->tail->next = NULL;
        q->size++;
        return q;
    }

    q->tail->next = node;
    q->tail = node;
    q->size++;
    return q;
}

// Elimina un nod de la inceputul listei
void dequeue(Queue *q)
{
    QNode *ptr = NULL;

    if (!q)
        return;
    if (empty_queue(q))
        return;
    if (!q->head->next) {
        free(q->head);
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
        return;
    }

    ptr = q->head;
    q->head = q->head->next;
    q->size--;
    free(ptr);
    return;
}

// Goleste lista si ii da free
void free_queue(Queue *q)
{
    if (!q)
        return;
    if (empty_queue(q)) {
        free(q);
        return;
    }

    while (q->size)
        dequeue(q);
    free(q);
    q = NULL;
}
