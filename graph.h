#ifndef GRAPH
#define GRAPH

typedef int TPointer;

typedef int** TMatriz;

typedef struct TGrafo
{
  TMatriz Matriz;
  int NVertices;
  int NArestas;
} TGrafo;

typedef enum
{
  BRANCO, CINZA, PRETO
} TCor;

#endif
