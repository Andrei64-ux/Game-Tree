#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "tasks.h"

int main(int argc , char **argv)
{
    if(argc != 4) {
        fprintf(stderr , "Usage: %s [-c1 | -c2 | -c3] [fişier_intrare] [fişier_ieşire]\n" , argv[0]);
        return -1;
    }
    FILE *in,*out;
    in = fopen(argv[2],"rt");
    out = fopen(argv[3],"wt");
    if( in == NULL) {
        fprintf(stderr,"I could not open the read file");
        return -1;
    }
    if( out == NULL) {
        fprintf(stderr,"I could not open the write file");
        return -1;
    }
    if(strncmp(argv[1],"-c1",3) == 0) {
        task1(in , out);
    } else if(strncmp(argv[1],"-c2",3) == 0) {
        task2(in , out);
    } else if(strncmp(argv[1],"-c3",3) == 0) { 
        task3(in , out);
    } else {
        fprintf(stderr,"Unknown task\n");
        return -1;
    }
    fclose(in);
    fclose(out);
    return 0;
}
