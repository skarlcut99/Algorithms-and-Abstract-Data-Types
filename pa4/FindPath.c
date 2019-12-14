//Sukhveer Karlcut
//skarlcut
//PA4

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[])
{
	int n = 0;
	int x, y, src, dest;
	Graph G = NULL;
	FILE *in, *out;
	if( argc != 3 )
	{
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(in == NULL)
	{
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(out == NULL)
	{
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	fscanf(in, "%d", &n);
	G = newGraph(n);   
	/* Stores vertices into Graph */
	while (fgetc(in) != EOF)
	{
		fscanf(in, "%d", &x);
		fscanf(in, "%d", &y);
		if (x == 0 && y == 0)
			break;
		addEdge(G, x, y);
	}   
	printGraph(out, G);
	fprintf(out, "\n");   
	/* Performs Breadth First Search on selected vertices, finds the distance between the source and its destination, and finally the shortest path between them if one exists */
	while (fgetc(in) != EOF)
	{
		fscanf(in, "%d", &src);
		fscanf(in, "%d", &dest);
		if (src == 0 && dest == 0)
			break;
		List L = newList();
		BFS(G, src);
		getPath(L, G, dest);
		if (getDist(G, dest) != INF)
		{
			fprintf(out, "The distance from %d to %d is %d\n", src, dest, length(L) - 1);
			fprintf(out, "A shortest %d-%d path is: ", src, dest);
			printList(out, L);
			fprintf(out, "\n\n");
		}
		else
		{
			fprintf(out, "The distance from %d to %d is infinity\n", src, dest);
			fprintf(out, "No %d-%d path exists\n", src, dest);
			fprintf(out, "\n");
		}
		freeList(&L);
	}   
	/* free memory */
	freeGraph(&G);   
	/* close files */
	fclose(in);
	fclose(out);   
	return(0);
}
