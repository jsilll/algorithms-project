#include <iostream>
#include "graph.h"
using namespace std;

int main(int argc, char const *argv[])
{
    int n, k;
    scanf("%d %d", &n, &k);
    F_Graph g(n + 2);

    int x, y;
    for (int i = 0; i < n; i++) // Processor <-> Process Edges
    {
        scanf("%d %d", &x, &y);
        g.addEdge(0, i + 1, x);
        g.addEdge(i + 1, n + 2 - 1, y);
    }

    int u, v, c;
    for (int i = 0; i < k; i++) // Process <-> Process Edges
    {
        scanf("%d %d %d", &u, &v, &c);
        g.addEdge(u, v, c);
        g.addEdge(v, u, c);
    }

    g.edmondsKarp(0, n + 2 - 1);
    g.printGraph();

    return 0;
}
