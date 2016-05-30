#ifndef GRAPH
#define GRAPH

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
	int Origem; // ID do vertice origem na matriz mapa
	int Termino; // ID do vertice termino na matriz mapa
} TGrafo;

// Funcoes do TAD:

TGrafo *alocaGrafo(int dimx, int dimy); // Aloca todo o espaco necessário para a estrutura TGrafo, incluindo a matriz do mapa da arena e a matriz de adjacencia do grafo

TGrafo *desalocaGrafo(TGrafo *Grafo, int dimx, int dimy); // Funcao que desaloca a estrutura TGrafo previamente alocada

TGrafo *montaMatrizAdj(TGrafo *Grafo, int dimx, int dimy, int dx, int dy); // Funcao que constroi a matriz de adjacencia (Grafo) a partir do mapa da arena

int *alocaVetor(int tam); // Funcao que aloca um vetor generico de tamanho tam

int *desalocaVetor(int *vetor); // Funcao que desaloca o vetor generico previamente alocado

void Dijkstra(TGrafo *Grafo); // Funcao que utiliza do Algoritmo de Dijkstra para calcular o menor custo do deslocamento do ponto de origem ao ponto de termino do grafo

#endif
