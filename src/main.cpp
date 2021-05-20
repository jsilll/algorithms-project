#include "graph.h"

// Driver code
int main(int argc, char const *argv[])
{
    int n, k;
    scanf("%d %d", &n, &k);

    Graph g(n + 2);

    int x, y;
    for (int i = 0; i < n; i++) // Processor <-> Process Edges
    {
        scanf("%d %d", &x, &y);
        // X Processor Edges
        g.setCapacity(0, i + 1, x);
        g.addEdge(0, i + 1);
        g.addEdge(i + 1, 0);
        // Y Processor Edges
        g.setCapacity(i + 1, n + 1, y);
        g.addEdge(n + 1, i + 1);
        g.addEdge(i + 1, n + 1);
    }

    int u, v, c;
    for (int i = 0; i < k; i++) // Process <-> Process Edges
    {
        scanf("%d %d %d", &u, &v, &c);
        g.setCapacity(u, v, c);
        g.setCapacity(v, u, c);
        g.addEdge(u, v);
        g.addEdge(v, u);
    }

    std::cout << g.edmondsKarp(0, n + 1) << endl;

    return 0;
}
