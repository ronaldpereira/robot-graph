#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void imprimeMatriz(MatrizEntrada **m, int x, int y)
{
	int i, j;

	printf("Impressão da matriz entrada e seus pesos:\n");

	for(i = 0; i < x; i++)
	{
		for(j = 0; j < y; j++)
		{
			printf("%d ", m[i][j].peso);
			if(j == y-1)
				printf("\n");
		}
	}

	printf("Impressão da matriz entrada e seus id's:\n");

	for(i = 0; i < x; i++)
	{
		for(j = 0; j < y; j++)
		{
			printf("%d ", m[i][j].id);
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

	Grafo->Mapa = (MatrizEntrada**) malloc(dimx*sizeof(MatrizEntrada*));
	for(i = 0; i < dimx; i++)
		Grafo->Mapa[i] = (MatrizEntrada*) malloc(dimy*sizeof(MatrizEntrada));

	Grafo->Matriz = (int**) calloc((dimx*dimy),sizeof(int*));
	for(i = 0; i < (dimx*dimy); i++)
		Grafo->Matriz[i] = (int*) calloc((dimx*dimy),sizeof(int));

	return Grafo;
}

TGrafo *desalocaGrafo(TGrafo *Grafo, int dimx, int dimy)
{
	int i;

	for(i = 0; i < dimx; i++)
		free(Grafo->Mapa[i]);
	free(Grafo->Mapa);

	for(i = 0; i < (dimx*dimy); i++)
		free(Grafo->Matriz[i]);
	free(Grafo->Matriz);

	free(Grafo);

	return NULL;
}

void imprimeMatrizAdj(TGrafo *Grafo, int x, int y)
{
	int i, j;

	printf("Impressão do Grafo\n");

	for(i = 0; i < (x*y); i++)
	{
		for(j = 0; j < (x*y); j++)
		{
			printf("%d\t", Grafo->Matriz[i][j]);
			if(j == (x*y)-1)
				printf("\n");
		}
	}

	printf("Impressão de atalhos:\n");

	for(i = 0; i < (x*y); i++)
	{
		for(j = 0; j < (x*y); j++)
		{
			if(Grafo->Matriz[i][j] == 0)
				printf("%d --> %d\n", i, j);
		}
	}
}

TGrafo *montaMatrizAdj(TGrafo *Grafo, int dimx, int dimy)
{
	int i, j, k, l;

	for(i = 0; i < dimx; i++)
	{
		for(j = 0; j < dimy; j++)
		{
			if(i + 1 < dimx && (Grafo->Mapa[i+1][j].peso == -1 || Grafo->Mapa[i][j].peso == -1))
			{
				Grafo->Matriz[Grafo->Mapa[i][j].id][Grafo->Mapa[i+1][j].id] = -1;
				Grafo->Matriz[Grafo->Mapa[i+1][j].id][Grafo->Mapa[i][j].id] = -1;
			}

			else
			{
				if(i + 1 < dimx)
				{
					Grafo->Matriz[Grafo->Mapa[i][j].id][Grafo->Mapa[i+1][j].id] = (Grafo->Mapa[i][j].peso + Grafo->Mapa[i+1][j].peso);
					Grafo->Matriz[Grafo->Mapa[i+1][j].id][Grafo->Mapa[i][j].id] = Grafo->Matriz[Grafo->Mapa[i][j].id][Grafo->Mapa[i+1][j].id];
				}
			}

			if(j + 1 < dimy && (Grafo->Mapa[i][j+1].peso == -1 || Grafo->Mapa[i][j].peso == -1))
			{
				Grafo->Matriz[Grafo->Mapa[i][j].id][Grafo->Mapa[i][j+1].id] = -1;
				Grafo->Matriz[Grafo->Mapa[i][j+1].id][Grafo->Mapa[i][j].id] = -1;
			}

			else
			{
				if(j + 1 < dimy)
				{
					Grafo->Matriz[Grafo->Mapa[i][j].id][Grafo->Mapa[i][j+1].id] = (Grafo->Mapa[i][j].peso + Grafo->Mapa[i][j+1].peso);
					Grafo->Matriz[Grafo->Mapa[i][j+1].id][Grafo->Mapa[i][j].id] = Grafo->Matriz[Grafo->Mapa[i][j].id][Grafo->Mapa[i][j+1].id];
				}
			}
		}
	}

	for(i = 0; i < (dimx*dimy); i++)
	{
		for(j = 0; j < (dimx*dimy); j++)
		{
			if(Grafo->Matriz[i][j] == 0)
				Grafo->Matriz[i][j] = -1;
		}
	}

	for(i = 0; i < dimx; i++)
	{
		for(j = 0; j < dimy; j++)
		{
			if(Grafo->Mapa[i][j].peso == 0)
			{
				for(k = 0; k < dimx; k++)
				{
					for(l = 0; l < dimy; l++)
					{
						if(Grafo->Mapa[k][l].peso == 0 && i != k && j != l)
						{
							Grafo->Matriz[Grafo->Mapa[i][j].id][Grafo->Mapa[k][l].id] = 0;
							Grafo->Matriz[Grafo->Mapa[k][l].id][Grafo->Mapa[i][j].id] = 0;
						}
					}
				}
			}
		}
	}

	return Grafo;
}
