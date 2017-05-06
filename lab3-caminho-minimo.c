#include <stdlib.h>
#include <stdio.h>

#define INFINITY 1000000

typedef int vertex;

typedef struct fila *Fila;
struct fila{
    int *no;
    int in;
    int out;
    int tam;
    int *dist;
};

typedef struct node *link;
struct node{
    int v;
    int w;
    int custo;
    link next;
    char flag;
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

void mark(Graph G, vertex s){
    G->adj[s]->flag = 1;
}

link NEWVERT (){
    link insertedV = malloc (sizeof *insertedV);
    insertedV->next = NULL;
    return insertedV;
}

Graph GRAPHinit (int V){
    int v;
    Graph G = malloc (sizeof *G);
    G->V = V;
    G->E = 0;
    G->adj = malloc (V*sizeof (link));
    for(v = 0; v < V; v++){
        G->adj[v] = NEWVERT();
        G->adj[v]->flag = 'F';
        G->adj[v]->v = v;
    }
    return G;
}

void GRAPHinsertE (Graph G, Edge e){
    int v1 = e.v1, v2 = e.v2, peso = e.peso;
    G->adj[v1]->next = NEW (v2, G->adj[v1]->next, peso);
    G->adj[v2]->next = NEW (v1, G->adj[v2]->next, peso);
    G->E++;
}
Fila PQinit (int V){
    Fila Q = malloc (sizeof *Q);
    Q->no = malloc(V * sizeof(int));
    Q->dist = malloc(V * sizeof(int));
    Q->in = -1;
    Q->out = -1;
    Q->tam = V;
    return Q;
}
int PQempty(Fila Q){
    if(Q->in == Q->out)
        return 1;
    else
        return 0;
}
void PQfree( Fila Q ){
    free(Q->no);
    free(Q);
}
void PQinsert(Fila Q, int no, int *dist){
    Q->in = (Q->in + 1)%Q->tam;
    Q->no[Q->in] = no;
}
vertex PQdequeue(Fila Q){
    vertex v;
    Q->out = (Q->out + 1)%Q->tam;
    v = Q->no[Q->out];
    Q->no[Q->out] = -1;

    return v;
}
vertex PQdelmin(Fila Q, int *dist){
    int i;
    vertex v;
    v = Q->no[0];
    for(i = 0; i < Q->tam; i++){
        if(dist[Q->no[i]] < dist[Q->no[v]])
            v = Q->no[i];
    }
    Q->
    return v;
}
void PQdec(int w, int *dist){

}
int BFS(Graph G, vertex s){
    Graph G_linha = malloc(sizeof *G_linha);
    int i, v;
    link vertN;
    char *state = malloc(G->V * sizeof(char));
    for(i = 0; i < G->V; i++){
        state[i] = 0;
    }

    Fila Q = PQinit(G->V);

    PQinsert(Q, G->adj[s]->v, NULL);
    state[s] = 1;

    while(!PQempty(Q))
    {
        v = PQdequeue( Q);
        printf("%d -->",v);

        for (vertN = G->adj[v]->next; vertN != NULL; vertN = vertN->next){
            if(state[vertN->v] == 0){
                state[vertN->v] = 1;
                PQinsert(Q, vertN->v, NULL);
            }
        }
    }
    printf("\n");
    return 0;
}
Graph Gera_G_linha(Graph G){
    Graph G_linha = malloc(sizeof *G_linha);
    G_linha = GRAPHinit(G->V);
    int i, v;
    link vertN, aux;
    char *state = malloc(G->V * sizeof(char));
    for(i = 0; i < G->V; i++){
        state[i] = 0;
    }

    Fila Q = PQinit(G->V);

    PQinsert(Q, G->adj[0]->v, NULL);
    state[0] = 1;

    while(!PQempty(Q))
    {
        v = PQdequeue( Q);
        for (vertN = G->adj[v]->next; vertN != NULL; vertN = vertN->next){
            if(state[vertN->v] == 0){
                PQinsert(Q, vertN->v, NULL);
            }
            for (aux = G->adj[vertN->v]->next; aux != NULL; aux = aux->next){
                if(aux->v != v && state[aux->v] == 0){
                    GRAPHinsertE(G_linha, EDGE(G->adj[v]->v, aux->v, vertN->custo + aux->custo));
                }
            }
            state[v] = 1;
        }
    }
    return G_linha;
}

int GRAPHspt3( Graph G, vertex s, vertex *parent, int *dist)
{

   vertex v, w, y; link a; int custo;
   vertex *hook = malloc( G->V * sizeof (vertex));
   parent = malloc( G->V * sizeof (int));
   dist = malloc( G->V * sizeof (int));

   /* inicialização: */
   for (v = 0; v < G->V; v++)
      parent[v] = -1, dist[v] = INFINITY;
   parent[s] = s, dist[s] = 0;
   for (a = G->adj[s]->next; a != NULL; a = a->next) {
      dist[a->v] = a->custo;
      hook[a->v] = s;
   }

   Fila Q = PQinit( G->V);
   for (v = 0; v < G->V; v++)
      if (v != s) PQinsert( Q, v, dist);

   while (!PQempty( Q )) {
      y = PQdelmin(Q, dist);
      if (dist[y] == INFINITY) {printf("ERROR\n"); break; }
      parent[y] = hook[y];
      /* atualização de dist[]: */
      for (a = G->adj[y]->next; a != NULL; a = a->next) {
         w = a->v, custo = a->custo;
         if (!(dist[y] + custo >= dist[w])) {
            dist[w] = dist[y] + custo; /* relaxa y-w */
            if(w == G->V - 1)
                printf("Menor distancia %d\n", dist[w]);
            //PQdec( w, dist);
            hook[w] = y;
         }
      }
   }


   PQfree( Q );
   free( hook);
   return 0;
}

void PrintGraph (Graph G){
    int i;
    link vertN;

    for (i=0; i < (G->V); i++){
        printf("v(%d): ", G->adj[i]->v);
        for (vertN = G->adj[i]->next; vertN != NULL; vertN = vertN->next){
            printf("->(%d)", (vertN->v));
        }
        printf("\n");
    }
}

int main(){
    int  i, X, Y, D;

    int *N, *M;
    N = malloc(sizeof(int));
    M = malloc(sizeof(int));


    scanf("%d %d", N, M);
    Graph G = GRAPHinit((*N));

    for(i = 0; i < *M; i++){
        scanf("%d %d %d", &X, &Y, &D);
        //X--; Y--;
        GRAPHinsertE(G, EDGE(X, Y, D));
    }

    PrintGraph(G);
    printf("\n");
    vertex *parent;
    int *dist;
    GRAPHspt3(G, 0, parent, dist);
    Graph G_linha = Gera_G_linha(G);
    PrintGraph(G_linha);


    free(G);
    return 0;
}
