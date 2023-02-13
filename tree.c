#include "tree.h"

Tree *init_tree(void *data , int data_size)
{
    Tree *new_root = (Tree*)malloc(sizeof(Tree));
    new_root->data = malloc(data_size);
    memcpy(new_root->data , data , data_size);
    new_root->data_size = data_size;
    new_root->sons_cnt = 0;
    new_root->max_sons = 1;
    new_root->sons = (Tree**)malloc(sizeof(Tree*));
    return new_root;
}

void add_son(Tree *root , Tree *son)
{
    if(root->sons_cnt == root->max_sons)
    {
        root->max_sons = root->max_sons*2;
        root->sons = (Tree**)realloc(root->sons , root->max_sons*sizeof(Tree*));
    }
    root->sons[root->sons_cnt] = son;
    root->sons_cnt++;
}

void free_tree(Tree *root)
{
    int i;
    for(i=0 ; i<root->sons_cnt ; i++)
    {
        free_tree(root->sons[i]);
    }
    free(root->sons);
    free(root->data);
    free(root);
}