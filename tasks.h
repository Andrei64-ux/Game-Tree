#ifndef TASKS_H
#define TASKS_H
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

typedef struct X_O_State_T{
    char board[3][3];
    int result;
    int depth;
    char player;
}X_O_State;

typedef struct MiniMax_State_T{
    int value;
    int sons_cnt;
    int depth;
}MiniMax_State;

void task1(FILE *in , FILE *out);
void task2(FILE *in , FILE *out);
void task3(FILE *in , FILE *out);

#endif 