#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "tasks.h"
#include "Doubly_linked_list.h"

char change(char player)
{
    if(player == 'O')
        return 'X';
    else 
        return 'O';
}

int finished(char board[3][3])
{
    int i;
    for(i=0; i<3; i++)
    {
        if(board[i][0] != '-' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
        if(board[0][i] != '-' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }
    if(board[0][0] != '-' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return 1;
    if(board[0][2] != '-' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return 1;
    return 0;
}

Tree *create_states(X_O_State state , char starting_player)
{
    int i,j;
    X_O_State copy;
    Tree *root = init_tree(&state , sizeof(X_O_State));
    if(finished(state.board))
    {
        if(state.player == starting_player)
        {
            (*(X_O_State*)root->data).result = 0;
        }
        else
        {
            (*(X_O_State*)root->data).result = 1;
        }
        return root;
    }
    for(i=0 ; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(state.board[i][j] == '-')
            {
                memcpy(&copy , &state , sizeof(X_O_State));
                copy.board[i][j] = state.player;
                copy.player = change(copy.player);
                copy.depth+=1;
                add_son(root , create_states(copy , starting_player));
            }
        }
    }
    if( root->sons_cnt == 0 )
    {
        (*(X_O_State*)root->data).result = 0;
        return root;
    }
    if(state.player == starting_player)
    {
        (*(X_O_State*)root->data).result = 0;
        for (i=0; i<root->sons_cnt ; i++)
        {
            (*(X_O_State*)root->data).result |= (*(X_O_State*)root->sons[i]->data).result;
        }
    }
    else
    {
        (*(X_O_State*)root->data).result = 1;
        for (i=0; i<root->sons_cnt ; i++)
        {
            (*(X_O_State*)root->data).result &= (*(X_O_State*)root->sons[i]->data).result;
        }
    }
    return root;
}

void print_state(FILE *out , X_O_State state)
{
    int i,j;
    for(i=0; i<3; i++)
    {
        for(j=0; j<state.depth; j++)
            fprintf(out , "\t");
        for(j=0; j<3; j++)
        {
            fprintf(out , "%c" , state.board[i][j]);
            if(j<2)
                fprintf(out," ");
        }
        fprintf(out , "\n");
    }
    fprintf(out , "\n");
}

void print_states(FILE *out , Tree *root)
{
    int i;
    print_state(out , *(X_O_State*)root->data);
    for(i=0; i<root->sons_cnt; i++)
    {
        print_states(out , root->sons[i]);
    }
}

void print_value(FILE *out , X_O_State state)
{
    int j;
    for(j=0; j<state.depth; j++)
        fprintf(out , "\t");
    if(state.result == 0)
    {
        fprintf(out,"F\n");
    }
    else
    {
        fprintf(out,"T\n");
    }
}

void print_states_value(FILE *out , Tree *root)
{
    int i;
    print_value(out , *(X_O_State*)root->data);
    for(i=0; i<root->sons_cnt; i++)
    {
        print_states_value(out , root->sons[i]);
    }
}

void task1(FILE *in , FILE *out)
{
    Tree *states;
    int i,j;
    X_O_State state; 
    fscanf(in , "%c\n" , &state.player);
    for(i=0; i<3; i++)
    {
        for(j=0 ; j<3;j++)
        {
            fscanf(in , " %c\n" , &state.board[i][j]);
        }
    }
    state.result = 0;
    state.depth = 0;
    states = create_states(state , state.player);
    print_states(out , states);
    free_tree(states);
}

void task2(FILE *in , FILE *out)
{
    Tree *states;
    int i,j;
    X_O_State state;
    fscanf(in , "%c\n" , &state.player);
    for(i=0; i<3; i++)
    {
        for(j=0 ; j<3;j++)
        {
            fscanf(in , " %c\n" , &state.board[i][j]);
        }
    }
    state.result = 0;
    state.depth = 0;
    states = create_states(state , state.player);
    print_states_value(out , states);
    free_tree(states);
}

MiniMax_State parse_next(FILE *in , int depth)
{
    char ch=0;
    MiniMax_State state;
    while (ch != '(' && ch != '[')
        fscanf(in , "%c" , &ch);
    if( ch == '[')
    {
        fscanf(in , "%d" , &state.value);
        state.depth = depth;
        state.sons_cnt = 0;
    }
    else
    {
        fscanf(in , "%d" , &state.sons_cnt);
        state.depth = depth;
        state.value = 0;
    }
    return state;
}

Tree *create_minimax(FILE *in)
{
    int i;
    int levels;
    MiniMax_State state;
    fscanf(in , "%d" , &levels);
    state = parse_next(in , 1);
    Tree *root = init_tree(&state , sizeof(MiniMax_State));
    DoublyLinkedList *queue = initList(sizeof(Tree*));
    push_back(queue , &root);
    while( !empty(queue) )
    {
        Tree *node = *(Tree**)front(queue);
        pop_front(queue);
        state = *(MiniMax_State*)node->data;
        for( i=0; i<state.sons_cnt ; i++)
        {
            MiniMax_State new_state = parse_next(in , state.depth+1);
            Tree *son = init_tree(&new_state , sizeof(MiniMax_State));
            add_son(node , son);
            if(new_state.depth < levels)
            {
                push_back(queue , &son);
            }
        }
    }
    freeList(queue);
    return root;
}

int max(int a , int b)
{
    if(a>b) return a;
    return b;
}

int min(int a , int b)
{
    if(a>b) return b;
    return a;
}

void solve_minimax(Tree *root)
{
    int i;
    MiniMax_State *state = (MiniMax_State*)root->data;
    if(root->sons_cnt == 0)
        return;
    for(i=0; i<root->sons_cnt ; i++)
    {
        solve_minimax(root->sons[i]);
    }
    if(state->depth %2 == 1)
    {
        state->value = (*(MiniMax_State*)root->sons[0]->data).value;
        for(i=1 ; i<root->sons_cnt; i++)
        {
            state->value = max(state->value , (*(MiniMax_State*)root->sons[i]->data).value);
        }
    }
    else
    {
        state->value = (*(MiniMax_State*)root->sons[0]->data).value;
        for(i=1 ; i<root->sons_cnt; i++)
        {
            state->value = min(state->value , (*(MiniMax_State*)root->sons[i]->data).value);
        }
    }
}

void print_minimax(FILE *out , Tree *root)
{
    int i;
    MiniMax_State *state = (MiniMax_State*)root->data;
    for(i=1 ; i<state->depth ; i++)
    {
        fprintf(out,"\t");
    }
    fprintf(out , "%d\n" , state->value);
    for(i=0; i<root->sons_cnt ; i++)
    {
        print_minimax(out , root->sons[i]);
    }
}

void task3(FILE *in , FILE *out)
{
    Tree *root = create_minimax(in);
    solve_minimax(root);
    print_minimax(out , root);
    free_tree(root);
}