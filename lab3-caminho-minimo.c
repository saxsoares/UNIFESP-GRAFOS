#include <stdlib.h>
#include <stdio.h>

#define INFINITY 1000000

typedef int vertex;

typedef struct node *link;
struct node{
    int v;
    int w;
    int custo;
    link next;
};

typedef struct {
    int v1; int v2;
    int peso;
} Edge;

typedef struct graph *Graph;
struct graph{
    int V;
    int E;
    Edge *edges;
    link *adj;
};



Edge EDGE(int v1, int v2, int peso){
    Edge e ;
    e.v1 = v1;
    e.v2 = v2;
    e.peso = peso;
    return e;
}

link NEW (int v, link next, int peso){
    link x = malloc (sizeof *x);
    x->v = v;
    x->custo = peso;
    x->next = next;

    /// Verificar necessidade e valores
    x->w = INFINITY;
    return x;
}

Graph GRAPHinit (int V){
    int v;
    Graph G = malloc (sizeof *G);
    G->V = V;
    G->E = 0;
    G->adj = malloc (V*sizeof (link));
    for (v=0; v<V; v++)
        G->adj[v] = NULL;
    return G;
}

void GRAPHinsertE (Graph G, Edge e){
    int v1 = e.v1, v2 = e.v2, peso = e.peso;
    G->adj[v1] = NEW (v2, G->adj[v1], peso);
    G->adj[v2] = NEW (v1, G->adj[v2], peso);
    G->E++;
}

int GRAPHedges (Edge a[], Graph G){
    int v, E=0;
    link vertN;
    for (v = 0; v < G->V; v++)
        for (vertN = G->adj[v]; vertN != NULL; vertN = vertN->next)
            if (v < vertN->v) a[E++] = EDGE (v, vertN->v, 1);
    return E;
}

void PrintGraph (Graph G, Edge E[]){
    int i, j;
    link vertN;
    for (i=0; i < (G->E); i++){
        printf("(%d)--%d-->(%d)\n ", E[i].v1, E[i].peso, E[i].v2);
    printf("\n");
    }
}

int GRAPHspt3( Graph G, vertex s, vertex *parent, int *dist)
{
   vertex v, w, y; link a; int custo;
   vertex *hook = malloc( G->V * sizeof (vertex));

   /* inicialização: */
   for (v = 0; v < G->V; v++)
      parent[v] = -1, dist[v] = INFINITY;
   parent[s] = s, dist[s] = 0;
   for (a = G->adj[s]; a != NULL; a = a->next) {
      dist[a->w] = a->custo;
      hook[a->w] = s;
   }

   PQinit( G->V);
   for (v = 0; v < G->V; v++)
      if (v != s) PQinsert( v, dist);

   while (!PQempty( )) {
      y = PQdelmin( dist);
      if (dist[y] == INFINITY) break;
      parent[y] = hook[y];
      /* atualização de dist[]: */
      for (a = G->adj[y]; a != NULL; a = a->next) {
         w = a->w, custo = a->custo;
         if (!(dist[y] + custo >= dist[w])) {
            dist[w] = dist[y] + custo; /* relaxa y-w */
            PQdec( w, dist);
            hook[w] = y;
         }
      }
   }
   PQfree( );
   free( hook);
   return 0;
}

int main(){
    int  i, X, Y, D;

    int *N, *M;
    N = malloc(sizeof(int));
    M = malloc(sizeof(int));


    scanf("%d %d", N, M);
    Graph G1 = GRAPHinit((*N));

    for(i = 0; i < *M; i++){
        scanf("%d %d %d", &X, &Y, &D);
        GRAPHinsertE(G1, EDGE(X, Y, D));
    }


}
