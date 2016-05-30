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
	int sx, sy, fx, fy, dx, dy;
	TGrafo *Grafo;

	entrada = fopen(argv[1], "r");
	sy = atoi(argv[2]);
	sx = atoi(argv[3]);
	fy = atoi(argv[4]);
	fx = atoi(argv[5]);
	dx = atoi(argv[6]);
	dy = atoi(argv[7]);

	while(fscanf(entrada, "%d %d", &dimy, &dimx) != EOF)
	{
		Grafo = alocaGrafo(dimx, dimy); // Aloca todo o espaco necessário para a estrutura TGrafo, incluindo a matriz do mapa da arena e a matriz de adjacencia do grafo

		casa = 0; // Variavel que identifica qual casa da matriz esta a leitura, sendo assim, e possivel atribuir id's para o futuro grafo que sera construido

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

		Grafo->Origem = Grafo->Mapa[sx][sy].id;  // Armazena o ponto de origem do grafo
		Grafo->Termino = Grafo->Mapa[fx][fy].id; // Armazena o ponto de termino do grafo
		Grafo->NVertices = (dimx*dimy); // Armazena o numero de vertices que o grafo tera

		Grafo = montaMatrizAdj(Grafo, dimx, dimy, dx, dy); // Funcao que constroi a matriz de adjacencia (Grafo) a partir do mapa da arena

		Dijkstra(Grafo); // Funcao que utiliza do Algoritmo de Dijkstra para calcular o menor custo do deslocamento do ponto de origem ao ponto de termino do grafo

		Grafo = desalocaGrafo(Grafo, dimx, dimy); // Funcao que desaloca a estrutura TGrafo previamente alocada
	}

	fclose(entrada);

	return 0;
}
