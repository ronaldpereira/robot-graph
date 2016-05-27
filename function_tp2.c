#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void imprimeMatriz(int **m, int x, int y)
{
	int i, j;

	for(i = 0; i < x; i++)
	{
		for(j = 0; j < y; j++)
		{
			printf("%d ", m[i][j]);
			if(j == y-1)
				printf("\n");
		}
	}
}

TGrafo *alocaGrafo(int dimx, int dimy)
{
	TGrafo *Grafo;
	int i;

	Grafo = (TGrafo*) malloc(sizeof(TGrafo));

	Grafo->Mapa = (int**) malloc(dimx*sizeof(int*));
	for(i = 0; i < dimx; i++)
		Grafo->Mapa[i] = (int*) malloc(dimy*sizeof(int*));

	Grafo->Matriz = (MatrizGrafo**) malloc(dimx*sizeof(MatrizGrafo*));
	for(i = 0; i < dimx; i++)
		Grafo->Matriz[i] = (MatrizGrafo*) malloc(dimy*sizeof(MatrizGrafo*));

	return Grafo;
}

TGrafo *desalocaGrafo(TGrafo *Grafo, int dimx, int dimy)
{
	int i;

	for(i = 0; i < dimx; i++)
		free(Grafo->Mapa[i]);
	free(Grafo->Mapa);

	for(i = 0; i < dimx; i++)
		free(Grafo->Matriz[i]);
	free(Grafo->Matriz);

	free(Grafo);

	return NULL;
}
