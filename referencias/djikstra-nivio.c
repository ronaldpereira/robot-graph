#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   4500
#define FALSE           0
#define TRUE            1
#define INFINITO       INT_MAX


typedef int TipoValorVertice;

typedef int TipoPeso;

typedef struct TipoGrafo
{
	TipoPeso Mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
	int  NumVertices;
	int  NumArestas;
} TipoGrafo;

typedef TipoValorVertice TipoApontador;
typedef int TipoIndice;
typedef struct TipoItem
{
	TipoPeso Chave;
} TipoItem;

typedef TipoItem TipoVetor[MAXNUMVERTICES + 1];

TipoApontador Aux;
int  i, NArestas;
short FimListaAdj;
TipoValorVertice V1, V2, Adj;
TipoPeso Peso;
TipoGrafo Grafo;
TipoValorVertice NVertices;
TipoIndice n;   /*Tamanho do heap*/
TipoValorVertice Raiz;

void FGVazio(TipoGrafo *Grafo)
{
	int  i, j;
	for (i = 0; i <= Grafo->NumVertices; i++)
	for (j = 0; j <= Grafo->NumVertices; j++)
	Grafo->Mat[i][j] = 0;
}

void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2, TipoPeso *Peso, TipoGrafo *Grafo)
	{
		Grafo->Mat[*V1][*V2] = *Peso;
	}

short  ExisteAresta(TipoValorVertice Vertice1, TipoValorVertice Vertice2,
	TipoGrafo *Grafo)
	{
		return (Grafo->Mat[Vertice1][Vertice2] > 0);
	}

		/*-- Operadores para obter a lista de adjacentes --*/

short ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{
	TipoApontador Aux = 0;
	short ListaVazia = TRUE;
	while (Aux < Grafo->NumVertices && ListaVazia)
	{
		if (Grafo->Mat[*Vertice][Aux] > 0)
		ListaVazia = FALSE;
		else
		Aux++;
	}
	return (ListaVazia == TRUE);
}

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{
	TipoValorVertice Result;
	TipoApontador Aux = 0;
	short Listavazia = TRUE;
	while (Aux < Grafo->NumVertices && Listavazia)
	{
		if (Grafo->Mat[*Vertice][Aux] > 0)
		{
			Result = Aux; Listavazia = FALSE;
		}
		else  Aux++;
	}
	if (Aux == Grafo->NumVertices)
	printf("Erro: Lista adjacencia vazia (PrimeiroListaAdj)\n");
	return Result;
}

void ProxAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo,
	TipoValorVertice *Adj, TipoPeso *Peso, TipoApontador *Prox,
	short *FimListaAdj)
	{
		/* --Retorna Adj apontado por Prox--*/
		*Adj = *Prox;
		*Peso = Grafo->Mat[*Vertice][*Prox];
		(*Prox)++;
		while (*Prox < Grafo->NumVertices && Grafo->Mat[*Vertice][*Prox] == 0)
		(*Prox)++;
		if (*Prox == Grafo->NumVertices)  *FimListaAdj = TRUE;
	}

void ImprimeGrafo(TipoGrafo *Grafo)

{
	int i, j;
	printf("   ");
	for (i = 0; i < Grafo->NumVertices; i++) printf("%3d", i); putchar('\n');
	for (i = 0; i < Grafo->NumVertices; i++)
	{
		printf("%3d", i);
		for (j = 0; j < Grafo->NumVertices; j++)
		printf("%3d", Grafo->Mat[i][j]);
		putchar('\n');
	}
}

void RefazInd(TipoIndice Esq, TipoIndice Dir, TipoItem *A, TipoPeso *P,
	TipoValorVertice *Pos)

	{
		TipoIndice i = Esq;  int j;  TipoItem x;
		j = i * 2;  x = A[i];
		while (j <= Dir)
		{
			if (j < Dir)
			{
				if (P[A[j].Chave] > P[A[j+1].Chave]) j++;
			}
			if (P[x.Chave] <= P[A[j].Chave])  break;
			A[i] = A[j]; Pos[A[j].Chave] = i;
			i = j;   j = i * 2;
		}
		A[i] = x;  Pos[x.Chave] = i;
	}

void Constroi(TipoItem *A,  TipoPeso *P,  TipoValorVertice *Pos)

{
	TipoIndice Esq;
	Esq = n / 2 + 1;
	while (Esq > 1)
	{
		Esq--;
		RefazInd(Esq, n, A, P, Pos);
	}
}

TipoItem RetiraMinInd(TipoItem *A,  TipoPeso *P,  TipoValorVertice *Pos)
{
	TipoItem Result;
	if (n < 1)
	{
		printf("Erro: heap vazio\n");
		return Result;
	}
	Result = A[1];
	A[1] = A[n]; Pos[A[n].Chave] = 1;
	n--;
	RefazInd(1, n, A, P, Pos);
	return Result;
}

void DiminuiChaveInd(TipoIndice i, TipoPeso ChaveNova, TipoItem *A,
	TipoPeso *P,  TipoValorVertice *Pos)
	{
		TipoItem x;
		if (ChaveNova > P[A[i].Chave])
		{
			printf("Erro: ChaveNova maior que a chave atual\n");
			return;
		}
		P[A[i].Chave] = ChaveNova;
		while (i > 1 && P[A[i / 2].Chave] > P[A[i].Chave])
		{
			x = A[i / 2];
			A[i / 2] = A[i];
			Pos[A[i].Chave] = i / 2;
			A[i] = x;
			Pos[x.Chave] = i;
			i /= 2;
		}
	}

void Dijkstra(TipoGrafo *Grafo, TipoValorVertice *Raiz)
{
	TipoPeso P[MAXNUMVERTICES + 1];
	TipoValorVertice Pos[MAXNUMVERTICES + 1];
	long Antecessor[MAXNUMVERTICES + 1];
	short Itensheap[MAXNUMVERTICES + 1];
	TipoVetor A;
	TipoValorVertice u, v;
	TipoItem temp;
	for (u = 0; u <= Grafo->NumVertices; u++)
	{
		/*Constroi o heap com todos os valores igual a INFINITO*/
		Antecessor[u] = -1; P[u] = INFINITO;
		A[u+1].Chave = u;   /*Heap a ser construido*/
		Itensheap[u] = TRUE;  Pos[u] = u + 1;
	}
	n = Grafo->NumVertices;
	P[*(Raiz)] = 0;
	Constroi(A, P, Pos);
	while (n >= 1)
	{
		/*enquanto heap nao vazio*/
		temp = RetiraMinInd(A, P, Pos);
		u = temp.Chave; Itensheap[u] = FALSE;
		if (!ListaAdjVazia(&u, Grafo))
		{
			Aux = PrimeiroListaAdj(&u, Grafo); FimListaAdj = FALSE;
			while (!FimListaAdj)
			{
				ProxAdj(&u, Grafo, &v, &Peso, &Aux, &FimListaAdj);
				if (P[v] > (P[u] + Peso))
				{
					P[v] = P[u] + Peso; Antecessor[v] = u;
					DiminuiChaveInd(Pos[v], P[v], A, P, Pos);
					printf("Caminho: v[%d] v[%ld] d[%d]",
					v, Antecessor[v], P[v]);
					scanf("%*[^\n]");
					getchar();
				}
			}
		}
	}
}

int main(int argc, char *argv[])
{
	/*-- Programa principal --*/
	int TEMP;

	/* -- NumVertices: definido antes da leitura das arestas --*/
	/* -- NumArestas: inicializado com zero e incrementado a --*/
	/* -- cada chamada de InsereAresta                       --*/
	printf("No. vertices:\n");   /*readln(NVertices);*/
	NVertices = 5;
	printf("No. arestas:\n");   /*eadln(NArestas);*/
	NArestas = 7;
	Grafo.NumVertices = NVertices;
	Grafo.NumArestas = 0;
	FGVazio(&Grafo);   /*1 chamada : G direcionado*/
	/*  for i := 0 to NArestas-1 do
	begin
	write('Insere V1 -- V2 -- Aresta:');
	readln(V1, V2, Peso);
	Grafo.NumArestas := Grafo.NumArestas + 1;
	InsereAresta(V1, V2, Peso, Grafo);*/
	/*
	InsereAresta(V2, V1, Peso, Grafo);*/
	/*2 chamadas: G nao-direcionado*/
	/*
	end;
	*/
	V1 = 0;
	V2 = 1;
	Peso = 1;
	Grafo.NumArestas++;
	InsereAresta(&V1, &V2, &Peso, &Grafo);   /*1 chamada : G direcionado*/
	/*InsereAresta(V2, V1, Peso, Grafo);*/
	/*2 chamadas: G nao-direcionado*/
	V1 = 0;
	V2 = 3;
	Peso = 3;
	Grafo.NumArestas++;
	InsereAresta(&V1, &V2, &Peso, &Grafo);   /*1 chamada : G direcionado*/
	/*InsereAresta(V2, V1, Peso, Grafo);*/
	/*2 chamadas: G nao-direcionado*/
	V1 = 0;
	V2 = 4;
	Peso = 10;
	Grafo.NumArestas++;
	InsereAresta(&V1, &V2, &Peso, &Grafo);   /*1 chamada : G direcionado*/
	/*InsereAresta(V2, V1, Peso, Grafo);*/
	/*2 chamadas: G nao-direcionado*/
	V1 = 1;
	V2 = 2;
	Peso = 5;
	Grafo.NumArestas++;
	InsereAresta(&V1, &V2, &Peso, &Grafo);   /*1 chamada : G direcionado*/
	/*InsereAresta(V2, V1, Peso, Grafo);*/
	/*2 chamadas: G nao-direcionado*/
	V1 = 2;
	V2 = 4;
	Peso = 1;
	Grafo.NumArestas++;
	InsereAresta(&V1, &V2, &Peso, &Grafo);   /*1 chamada : G direcionado*/
	/*InsereAresta(V2, V1, Peso, Grafo);*/
	/*2 chamadas: G nao-direcionado*/
	V1 = 3;
	V2 = 2;
	Peso = 2;
	Grafo.NumArestas++;
	InsereAresta(&V1, &V2, &Peso, &Grafo);   /*1 chamada : G direcionado*/
	/*InsereAresta(V2, V1, Peso, Grafo);*/
	/*2 chamadas: G nao-direcionado*/
	V1 = 3;
	V2 = 4;
	Peso = 6;
	Grafo.NumArestas++;
	InsereAresta(&V1, &V2, &Peso, &Grafo);   /*1 chamada : G direcionado*/
	/*InsereAresta(V2, V1, Peso, Grafo);*/
	/*2 chamadas: G nao-direcionado*/

	ImprimeGrafo(&Grafo);
	scanf("%*[^\n]");
	getchar();
	printf("Raiz:");
	scanf("%d%*[^\n]", &TEMP);
	getchar();
	Raiz = TEMP;
	Dijkstra(&Grafo, &Raiz);
	return 0;
}
