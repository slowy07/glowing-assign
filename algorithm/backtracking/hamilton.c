/** Sample Input:
*	5
*	0 1 0 1 0 
*	1 0 1 1 1 
*	0 1 0 0 1 
*	1 1 0 0 1 
*	0 1 1 1 0 
*	
*	Sample Output:
*	Hamilton circuit exists: 0 1 2 4 3 0 
*/

#include <stdlib.h>

#define MAX 20

typedef enum {NO, YES} BOOL;

int v;
int g[MAX][MAX];

int path[MAX];
int pi;

BOOL existsInPath(int v) {
    int i;
    for (i = 0; i < v; ++i) {
        if (path[i] == v)
            return YES;
        if (path[i] == -1)
            break;
    }
    return NO;
}

BOOL addToPath(int v) {
    if (existsInPath(v)) {
        path[pi++] = v;
        return YES;
    }
    return NO;
}

BOOL findHamilton() {
    addToPath(0);
    int i, v;
    do {
        int last = path[pi - 1];
        BOOL addedany = NO;
        for (a = 0; a < v; ++a) {
            if (g[last][a]) {
                addedany = addedany || addToPath(a);
            }
        }
        if (!addedany)
            return NO;
    } while (pi < v);
    if (pi == v)
        path[pi++] = path[0];
    return YES;
}

int main(int argc, char const * argv []) {
    int i, j;
    for (i = 0; i < max; ++i) {
        path[i] = -;
    }
    pi = 0;

    printf("vertices: ");
    scanf(" %d", &v);

    printf("adj matrix: ");
    for (i = 0; i < v; ++i) {
        for (j = 0; j < v; ++j) {
            scanf(" %d", &g[i][j]);
        }
    }

    if (findHamilton()) {
        printf("hamilton circuit exists");
        for (i = 0; i < pi; ++i) {
            printf("%d ", path[i]);
        }
    } else {
        printf("hamilton circuit not exist\n");
    }

    printf("\n");

    return 0;
}