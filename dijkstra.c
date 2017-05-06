#include<stdio.h>
#include<stdlib.h>


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
    //Edge *edges;
    link *adj;
};

link NEW (int v, link next, int peso){
    link x = malloc (sizeof *x);
    x->v = v;
    x->custo = peso;
    x->next = next;

    /// Verificar necessidade e valores
    x->w = INFINITY;
    return x;
}

void GRAPHinsertE (Graph G, Edge e){
    int v1 = e.v1, v2 = e.v2, peso = e.peso;
    G->adj[v1] = NEW (v2, G->adj[v1], peso);
    G->adj[v2] = NEW (v1, G->adj[v2], peso);
    G->E++;
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
