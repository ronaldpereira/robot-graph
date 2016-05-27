#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char *argv[])
{
	FILE *entrada;
	int i, j, dimx, dimy;
	int sx, sy, fx, fy, dx, dy;
	TGrafo *Grafo;

	entrada = fopen(argv[1], "r");
	sx = atoi(argv[2]);
	sy = atoi(argv[3]);
	fx = atoi(argv[4]);
	fy = atoi(argv[5]);
	dx = atoi(argv[6]);
	dy = atoi(argv[7]);

	printf("%d %d %d %d %d %d\n", sx, sy, fx, fy, dx, dy);

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
