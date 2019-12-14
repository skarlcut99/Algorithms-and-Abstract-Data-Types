//Sukhveer Karlcut
//ID: skarlcut
//pa2
//
//Lex.c tests methods from List.c and uses them to alphabetize lines of a file

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#define MAX_LEN 1000

int main(int argc, char * argv[]){
        int temp = 0;
        int count = 0;
        FILE *in;
        FILE *out;
        char str[MAX_LEN];
        char** arr;
        if( argc != 3 ){
                printf("Usage: %s <input file> <output file>\n", argv[0]);
                exit(1);
        }

        in = fopen(argv[1], "r");
        out = fopen(argv[2], "w");
        if( in==NULL ){
                printf("Unable to open file %s for reading\n", argv[1]);
                exit(1);
        }
        if( out==NULL ){
                printf("Unable to open file %s for writing\n", argv[2]);
                exit(1);
        }
	//read file
        while (fgets(str, MAX_LEN, in ) != NULL)
                count++;
        rewind(in);
        arr = malloc((count) * sizeof(char*));
        for(int i = 0; i < count; i ++)
                arr[i] = malloc((MAX_LEN) * sizeof(char));
        while(fgets(str, sizeof(str), in) != NULL)
        {
                strcpy(arr[temp], str);
                temp ++;
       	}
	//alphabetize char** array
        List l = newList();
        append(l, 0);
        for(int i = 1; i < count; i ++)
        {
                moveFront(l);
                int x = i;
                while(x > 0 && strcmp(arr[i], arr[get(l)]) >= 0)
                {
                        moveNext(l);
                        x--;
                }
                if(index(l) >= 0)
                        insertBefore(l, i);
                else
                        append(l, i);
        }
	//print to output file
        moveFront(l);
        temp = 0;
        while(temp < count) {
            fprintf(out, "%s", arr[get(l)]);
            moveNext(l);
            temp++;
        }
	//free memory
        fclose(out);
	for(int i = 0; i < count; i ++)
		free(arr[i]);
	free(arr);
        freeList(&l);
        return(0);
}

