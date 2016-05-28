#ifndef GRAPH
#define GRAPH

typedef int TPointer;

typedef struct MatrizEntrada
{
	int peso; // Peso da aresta
	int id; // Numeracao das casas da matriz da entrada
} MatrizEntrada;

typedef struct TGrafo
{
	int **Matriz; // Grafo do estilo de matriz de adjacencia
	MatrizEntrada **Mapa; // Matriz de pesos e id's da matriz da entrada (definida no struct MatrizEntrada acima)
	int NVertices; // Numero de vertices totais do grafo
	int NArestas; // Numero de arestas totais do grafo
	int Origem; // ID do vertice origem na matriz mapa
	int Termino; // ID do vertice termino na matriz mapa
} TGrafo;

// Testes:
void imprimeMatriz(MatrizEntrada **m, int x, int y);

void imprimeMatrizAdj(TGrafo *Grafo, int x, int y);

// Funcoes do TP:

TGrafo *alocaGrafo(int dimx, int dimy);

TGrafo *desalocaGrafo(TGrafo *Grafo, int dimx, int dimy);

TGrafo *montaMatrizAdj(TGrafo *Grafo, int dimx, int dimy);

#endif
