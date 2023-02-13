#ifndef TREE_H
#define TREE_H
#include <stdlib.h>
#include <string.h>

typedef struct Tree_T{
    void *data;
    int data_size;
    struct Tree_T **sons;
    int sons_cnt;
    int max_sons;
}Tree;

Tree *init_tree(void *data , int data_size);
void free_tree(Tree *root);
void add_son(Tree *root , Tree *son);

#endif 
