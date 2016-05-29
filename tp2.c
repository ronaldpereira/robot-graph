#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"
#define FALSE 0
#define TRUE 1
#define INFINITO INT_MAX

int main(int argc, char *argv[])
{
	FILE *entrada;
	int i, j, ent, casa, dimx, dimy;
	int sx, sy, fx, fy; // dx, dy;
	TGrafo *Grafo;

	entrada = fopen(argv[1], "r");
	sy = atoi(argv[2]);
	sx = atoi(argv[3]);
	fy = atoi(argv[4]);
	fx = atoi(argv[5]);
	// dx = atoi(argv[6]);
	// dy = atoi(argv[7]);

	while(fscanf(entrada, "%d %d", &dimy, &dimx) != EOF)
	{
		Grafo = alocaGrafo(dimx, dimy);

		casa = 0;
		for(i = 0; i < dimx; i++)
		{
			for(j = 0; j < dimy; j++, casa++)
			{
				fscanf(entrada, "%d", &ent);

				if(ent == -1)
					ent = 0;
				else if(ent == 0)
					ent = -1;

				Grafo->Mapa[i][j].peso = ent;
				Grafo->Mapa[i][j].id = casa;
			}
		}

		Grafo->Origem = Grafo->Mapa[sx][sy].id;
		Grafo->Termino = Grafo->Mapa[fx][fy].id;
		Grafo->NVertices = (dimx*dimy);

		// printf("%d --> %d\n", Grafo->Origem, Grafo->Termino); // Teste

		// imprimeMatriz(Grafo->Mapa, dimx, dimy); // Teste

		Grafo = montaMatrizAdj(Grafo, dimx, dimy);

		// imprimeMatrizAdj(Grafo, dimx, dimy); // Teste

		Dijkstra(Grafo);

		Grafo = desalocaGrafo(Grafo, dimx, dimy);
	}

	fclose(entrada);

	return 0;
}
