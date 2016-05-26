#ifndef GRAPH
#define GRAPH

typedef int TPointer;

typedef struct TGrafo
{
	int **Matriz;
	int **Mapa;
	int NVertices;
	int NArestas;
} TGrafo;

typedef enum
{
	BRANCO, CINZA, PRETO
} TCor;

void imprimeMatriz(int **m, int x, int y);

TGrafo *alocaGrafo(int dimx, int dimy);

TGrafo *desalocaGrafo(TGrafo *Grafo, int dimx, int dimy);

#endif
