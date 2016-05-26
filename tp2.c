#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char *argv[])
{
	FILE *entrada;
	int i, j, dimx, dimy;
	TGrafo *Grafo;

	entrada = fopen(argv[1], "r");

	while(fscanf(entrada, "%d %d", &dimy, &dimx) != EOF)
	{
		Grafo = alocaGrafo(dimx, dimy);

		for(i = 0; i < dimx; i++)
			for(j = 0; j < dimy; j++)
				fscanf(entrada, "%d", &(Grafo->Mapa[i][j]));

		imprimeMatriz(Grafo->Mapa, dimx, dimy);

		Grafo = desalocaGrafo(Grafo, dimx, dimy);
	}

	fclose(entrada);

	return 0;
}
