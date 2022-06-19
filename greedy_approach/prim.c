#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>

#define MAX 20
#define INF 999

uint16_t minimum(uint16_t arr[], uint16_t N) {
    uint16_t index = 0;
    uint16_t min = INF;

    for (uint16_t i = 0; i < N; i++) {
        if (arr[i] < min) {
            min = arr[i];
            index = i;
        }
    }
    return index;
}

void prim(uint16_t G[][MAX], uint16_t MST[][MAX], uint16_t V) {
    uint16_t u, v;
    uint16_t E_t[MAX], path[MAX];
    uint16_t V_t[MAX], no_of_edges;

    E_t[0] = 0;
    V_t[0] = 1;

    for (uint16_t i = 1; i < V; i++) {
        E_t[i] = G[i][0];
        path[i] = 0;
        V_t[i] = 0;
    }

    no_of_edges = V - 1;

    while (no_of_edges > 0) {
        u = minimum(E_t, V);
        while (V_t[u] == 1) {
            E_t[u] = INF;
            u = minimum(E_t, V);
        }

        v = path[u];
        MST[v][u] = E_t[u];
        MST[u][v] = E_t[u];
        no_of_edges--;
        V_t[u] = 1;

        for (uint16_t i = 1; i < V; i++) {
            if (V_t[i] == 0 && G[u][i] < E_t[i]) {
                E_t[i] = G[u][i];
                path[i] = v; 
            }
        }
    }
}

static void test(uint16_t G[][MAX], uint16_t MST[][MAX], uint16_t V) {
    uint16_t test[4][4] = {{0,1,2,3},{1,0,4,6},{2,4,0,5},{3,6,5,0}};
    uint16_t solution[4][4] = {{0,1,2,3},{1,0,0,0},{2,0,0,0},{3,0,0,0}};
    
    V = 4;
    
    for(uint16_t i = 0; i < V; ++i) {
        for(uint16_t j = 0; j < V; ++j) {
            G[i][j] = test[i][j];    
        }
    }
    
    prim(&(*G),&(*MST),V);
    
    for(uint16_t i = 0; i < V; ++i) {
        for(uint16_t j = 0; j < V; ++j) {
            assert(MST[i][j] == solution[i][j]);
        }
    }
}

void user_graph(uint16_t G[][MAX], uint16_t MST[][MAX], uint16_t V) {
    printf("enter number vertices: ");
    scanf("%hd", &V);

    assert(V <= max);
    printf("enter the adj matrix\n");
    uint16_t i, j;
    for (i = 0; i < V; ++i) {
        for (j = 0; j < V; ++j) {
            printf("G[%d][%d]: ", i, j);
            scanf("%hd", &G[i][j]);
            if (G[i][j] == 0)
                G[i][j] = INF;
        }
    }
    prim(&(*G),&(*MST),V);

    printf("minimum spanning tree\n");
    for (i = 0; i < V; ++i) {
        printf("\n");
        for (j = 0; j < V; ++j) {
            printf("%d\t", MST[i][j]);
        }
    }
}

int main(int argc, char const *argv[]) {
    uint16_t G[MAX][MAX];
    uint16_t MST[MAX][MAX];
    uint16_t V;

    if (argc == 2 && strcmp(argv[1], "-test") == 0) {
        test(&(*G),&(*MST),V);
    } else {
        user_graph(&(*G),&(*MST),V);
    }

    return 0;
}
