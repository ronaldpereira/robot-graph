#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"
#define FALSE 0
#define TRUE 1
#define INFINITO INT_MAX

TGrafo *alocaGrafo(int dimx, int dimy) // Aloca todo o espaco necessário para a estrutura TGrafo, incluindo a matriz do mapa da arena e a matriz de adjacencia do grafo
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

TGrafo *desalocaGrafo(TGrafo *Grafo, int dimx, int dimy) // Funcao que desaloca a estrutura TGrafo previamente alocada
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

TGrafo *montaMatrizAdj(TGrafo *Grafo, int dimx, int dimy, int dx, int dy) // Funcao que constroi a matriz de adjacencia (Grafo) a partir do mapa da arena
{
	int i, j, k, l;
	int pesox, pesoy;

	if(dx == 0 && dy == 0)
	{
		for(i = 0; i < dimx; i++)
		{
			for(j = 0; j < dimy; j++)
			{
				if(i + 1 < dimx && (Grafo->Mapa[i+1][j].peso == -1 || Grafo->Mapa[i][j].peso == -1))
				{
					Grafo->Matriz[Grafo->Mapa[i][j].id][Grafo->Mapa[i+1][j].id] = INFINITO;
					Grafo->Matriz[Grafo->Mapa[i+1][j].id][Grafo->Mapa[i][j].id] = INFINITO;
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
					Grafo->Matriz[Grafo->Mapa[i][j].id][Grafo->Mapa[i][j+1].id] = INFINITO;
					Grafo->Matriz[Grafo->Mapa[i][j+1].id][Grafo->Mapa[i][j].id] = INFINITO;
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
	}

	else
	{
		for(i = 0; i < dimx; i++)
		{
			for(j = 0; j < dimy; j++)
			{
				pesox = 0;
				pesoy = 0;

				for(k = 0; k <= dx; k++) // Dx primeiro
				{
					if(j + k >= dimy)
					{
						pesox = INFINITO;
						break;
					}

					if(Grafo->Mapa[i][j+k].peso == -1)
					{
						pesox = INFINITO;
						break;
					}

					if(k == 0 || k == dx)
						pesox += Grafo->Mapa[i][j+k].peso;

					else
						pesox += 2*Grafo->Mapa[i][j+k].peso;
				}

				if(k >= dx)
					k--;

				for(l = 0; l <= dy; l++)
				{
					if(pesox == INFINITO)
						break;

					if(j + k >= dimy)
					{
						pesoy = INFINITO;
						break;
					}

					if(i + l >= dimx)
					{
						pesoy = INFINITO;
						break;
					}

					if(Grafo->Mapa[i+l][j+k].peso == -1)
					{
						pesox = INFINITO;
						break;
					}

					if(l == 0 || l == dy)
						pesox += Grafo->Mapa[i+l][j+k].peso;

					else
						pesox += 2*Grafo->Mapa[i+l][j+k].peso;
				}

				for(k = 0; k <= dy; k++) // Dy primeiro
				{
					if(i + k >= dimx)
					{
						pesoy = INFINITO;
						break;
					}

					if(Grafo->Mapa[i+k][j].peso == -1)
					{
						pesoy = INFINITO;
						break;
					}

					if(k == 0 || k == dy)
						pesoy += Grafo->Mapa[i+k][j].peso;

					else
						pesoy += 2*Grafo->Mapa[i+k][j].peso;

				}

				if(k >= dx)
					k--;

				for(l = 0; l <= dx; l++)
				{
					if(pesoy == INFINITO)
						break;

					if(i + k >= dimx)
					{
						pesoy = INFINITO;
						break;
					}

					if(j + l >= dimy)
					{
						pesoy = INFINITO;
						break;
					}

					if(Grafo->Mapa[i+k][j+l].peso == -1)
					{
						pesoy = INFINITO;
						break;
					}

					if(l == 0 || l == dx)
						pesoy += Grafo->Mapa[i+k][j+l].peso;

					else
						pesoy += 2*Grafo->Mapa[i+k][j+l].peso;
				}

				if(pesox < pesoy && i+dy < dimx && j+dx < dimy)
				{
					Grafo->Matriz[Grafo->Mapa[i][j].id][Grafo->Mapa[i+dy][j+dx].id] = pesox; // Colocar peso x ligando as arestas [i][j] a [i+dx][j+dy]
					Grafo->Matriz[Grafo->Mapa[i+dy][j+dx].id][Grafo->Mapa[i][j].id] = pesox;
				}

				else if(pesoy < pesox && i+dy < dimx && j+dx < dimy)
				{
					Grafo->Matriz[Grafo->Mapa[i][j].id][Grafo->Mapa[i+dy][j+dx].id] = pesoy; // Colocar peso y ligando as arestas [i][j] a [i+dx][j+dy]
					Grafo->Matriz[Grafo->Mapa[i+dy][j+dx].id][Grafo->Mapa[i][j].id] = pesoy;
				}
			}
		}
	}

	for(i = 0; i < (dimx*dimy); i++)
	{
		for(j = 0; j < (dimx*dimy); j++)
		{
			if(Grafo->Matriz[i][j] == 0)
				Grafo->Matriz[i][j] = INFINITO;
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

int *alocaVetor(int tam) // Funcao que aloca um vetor generico de tamanho tam
{
	int *vetor;

	vetor = (int*) calloc(tam,sizeof(int));

	return vetor;
}

int *desalocaVetor(int *vetor) // Funcao que desaloca o vetor generico previamente alocado
{
	free(vetor);

	return NULL;
}

void Dijkstra(TGrafo *Grafo) // Funcao que utiliza do Algoritmo de Dijkstra para calcular o menor custo do deslocamento do ponto de origem ao ponto de termino do grafo
{
	int *distancia, *adj, *caminho;
	int atual, distancia_parcial, menor_distancia, nova_distancia;
	int i, aux;

	distancia = alocaVetor(Grafo->NVertices);
	adj = alocaVetor(Grafo->NVertices);
	caminho = alocaVetor(Grafo->NVertices);

	for(i = 0; i < Grafo->NVertices; i++)
		distancia[i] = INFINITO;

	adj[Grafo->Origem] = 1;
	distancia[Grafo->Origem] = 0;

	atual = Grafo->Origem;
	aux = Grafo->Origem;

	while(atual != Grafo->Termino)
	{
		menor_distancia = INFINITO;
		distancia_parcial = distancia[atual];

		for(i = 0; i < Grafo->NVertices; i++)
		{
			if(adj[i] == 0)
			{
				if(Grafo->Matriz[atual][i] == INFINITO)
					nova_distancia = INFINITO;
				else
				nova_distancia = distancia_parcial + Grafo->Matriz[atual][i];

				if(nova_distancia < distancia[i])
				{
					distancia[i] = nova_distancia;
					caminho[i] = atual;
				}

				if(distancia[i] < menor_distancia)
				{
					menor_distancia = distancia[i];
					aux = i;
				}
			}
		}

		if(atual == aux)
		{
			printf("-1\n");
			desalocaVetor(distancia);
			desalocaVetor(adj);
			desalocaVetor(caminho);
			return;
		}

		atual = aux;
		adj[atual] = 1;
	}
	printf("%d\n", distancia[aux]);

	desalocaVetor(distancia);
	desalocaVetor(adj);
	desalocaVetor(caminho);
}
