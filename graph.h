#ifndef GRAPH
#define GRAPH

typedef int TPointer;

typedef struct MatrizGrafo
{
	int peso; // Peso da aresta
	int id; // Numeração das casas da matriz da entrada
} MatrizGrafo;

typedef struct TGrafo
{
	MatrizGrafo **Matriz;
	int **Mapa;
	int NVertices;
	int NArestas;
} TGrafo;

void imprimeMatriz(int **m, int x, int y);

TGrafo *alocaGrafo(int dimx, int dimy);

TGrafo *desalocaGrafo(TGrafo *Grafo, int dimx, int dimy);

#endif
