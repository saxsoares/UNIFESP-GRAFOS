#include <stdlib.h>
#include <stdio.h>

typedef struct node *link;
struct node{
    int v;
    int peso;
    char f;
    link *boss;
    link next;
};

typedef struct graphQ *Graph;
struct graphQ{
    int V;
    int E;
    link *adj;
};

Graph GRAPHinit (int);
void GRAPHinsertE (Graph, int x, int y);
Graph GRAPHcopy (Graph);
void GRAPHdestroy (Graph);

Graph GRAPHinit (int V);
int **MATRIXint (int r, int c, int val);
void GRAPHinsertE (Graph G, int x, int y);

Graph GRAPHinit (int V){
    Graph G = malloc (sizeof *G);
    G->V = V;
    G->E = 0;
    G->adj = malloc (V*sizeof (link));
    return G;
}

link NEWVERT (int time){
    link insertedV = malloc (sizeof *insertedV);
    insertedV->time = time;
    insertedV->next = NULL;
    insertedV->boss = NULL;
    return insertedV;
}

void GRAPHinsertE (Graph G, int v1, int v2, int peso){
    link x = malloc (sizeof *x);
    x->v = v1;
    x->next = G->adj[v2]->next;
    x->boss = (link *)G->adj[v1];
    G->adj[v2]->next = x;
}

int pesquisa(Graph G, int v, link **mapa){
    int t = 0, aux = 0;
    link vertice;
    vertice = (link)mapa[v];
    link auxv1 = ((link)mapa[v])->next;
    if(vertice->f == 'F'){
        vertice->f = 'V';
        for (auxv1 = auxv1 ; auxv1 != NULL; auxv1 = auxv1->next){
            aux = pesquisa(G, ((link)auxv1->boss)->v, mapa);
            if(aux < ((link)auxv1->boss)->time)
                aux = ((link)auxv1->boss)->time;
            if(t < aux)
                t = aux;
        }
    }
    return t;
}

int main(){

    int  i, D, X, Y;
    int *N, *M;

    N = malloc(sizeof(int));
    M = malloc(sizeof(int));
    D = malloc(sizeof(int));
    char op;
    scanf("%d %d", N, M);

    link *mapa[*N];
    Graph G1 = GRAPHinit((*N));
    for(i = 0; i < *N; i++){
        scanf("%d", &time);
        G1->adj[i] = NEWVERT(time);
        G1->adj[i]->v = i;
        G1->adj[i]->f = 'F';
    }

    for(i = 0; i < *M; i++){
        scanf("%d %d %d", &X, &Y, &D);
        X--; Y--;
        GRAPHinsertE(G1, X, Y, D);
    }
}
