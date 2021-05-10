#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> graph;
vector<vector<int>> graph_t;

void readGraph()
{
    int n, m;
    scanf("%d,%d", &n, &m);

    graph = vector<vector<int>>(n, vector<int>());
    graph_t = vector<vector<int>>(n, vector<int>());

    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u - 1].push_back(v - 1);
        graph_t[v - 1].push_back(u - 1);
    }
}

void printGraph(vector<vector<int>> g)
{
    for (std::vector<std::vector<int>>::size_type i = 0; i < g.size(); i++)
    {
        for (std::vector<std::vector<int>>::size_type j = 0; j < g[i].size(); j++)
        {
            std::cout << i + 1 << ' ' << g[i][j] + 1 << '\n';
        }
    }
}

std::vector<int>::size_type computeMaxOut(vector<vector<int>> g)
{
    std::vector<int>::size_type max = 0;
    for (std::vector<std::vector<int>>::size_type i = 0; i < g.size(); i++)
    {
        if (g[i].size() > max)
        {
            max = g[i].size();
        }
    }

    return max;
}

vector<int> computeOutHistogram(vector<vector<int>> g)
{
    std::vector<int>::size_type max = computeMaxOut(g);
    vector<int> hist = vector<int>(max + 1, 0);

    for (std::vector<std::vector<int>>::size_type i = 0; i < g.size(); i++)
    {
        hist[g[i].size()]++;
    }

    for (std::vector<std::vector<int>>::size_type i = 0; i < hist.size(); i++)
    {
        std::cout << hist[i] << " ";
    }
    std::cout << "\n";

    return hist;
}

vector<vector<int>> computeTransposedGraph(vector<vector<int>> g)
{
    vector<vector<int>> g_t = vector<vector<int>>(g.size(), vector<int>());

    for (std::vector<std::vector<int>>::size_type i = 0; i < g.size(); i++)
    {
        for (std::vector<std::vector<int>>::size_type j = 0; j < g[i].size(); j++)
        {
            g_t[g[i][j]].push_back(i);
        }
    }

    return g_t;
}

int main()
{
    readGraph();
    printGraph(graph);
    std::cout << "Histograma 1" << '\n';
    computeOutHistogram(graph);
    std::cout << "Histograma 2" << '\n';
    computeOutHistogram(graph_t);
}