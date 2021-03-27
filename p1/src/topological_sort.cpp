#include <iostream>
#include <limits.h>
#include <list>
#include <stack>
#include <vector>

#define NINF INT_MIN
using namespace std;

class Graph
{
    int V;

    vector<int> *adj;
    void topologicalSort(int v, bool visited[], stack<int> &Stack);

public:
    Graph(int V);
    ~Graph();

    void addEdge(int u, int v);
    Graph getTranspose();
    vector<int> getSinks();
    vector<int> getSources();

    int findLongestPath(int s);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new vector<int>[V];
}

Graph::~Graph()
{
    delete[] adj;
}

void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
}

Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < this->V; v++)
    {
        for (vector<int>::iterator i = this->adj[v].begin(); i != this->adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

vector<int> Graph::getSinks()
{
    vector<int> res;
    for (int v = 0; v < this->V; v++)
    {
        if (this->adj[v].empty())
        {
            res.push_back(v);
        }
    }
    return res;
}

vector<int> Graph::getSources()
{
    Graph gt = this->getTranspose(); // O(V + E)
    return gt.getSinks();
}

void Graph::topologicalSort(int v, bool visited[], stack<int> &Stack) // DFS traversal and adding to the stack by closing order
{
    visited[v] = true;

    for (vector<int>::iterator i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if (!visited[*i])
            topologicalSort(*i, visited, Stack);
    }

    Stack.push(v);
}

int Graph::findLongestPath(int s)
{
    stack<int> Stack;
    int dist[V];

    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSort(i, visited, Stack);

    for (int i = 0; i < V; i++)
        dist[i] = NINF;
    dist[s] = 0;

    while (Stack.empty() == false)
    {
        int u = Stack.top();
        Stack.pop();

        if (dist[u] != NINF)
        {
            for (vector<int>::iterator i = adj[u].begin(); i != adj[u].end(); ++i)
            {
                dist[*i] = max(dist[*i], dist[u] + 1);
            }
        }
    }

    delete[] visited;

    int res = 0;
    for (int i = 0; i < V; i++)
    {
        res = max(res, dist[i]);
    }
    return res;
}

int main()
{

    int n, m;
    scanf("%d %d", &n, &m);
    Graph g(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        g.addEdge(u - 1, v - 1);
    }

    int res = 0;
    vector<int> sources = g.getSources();
    for (vector<int>::iterator i = sources.begin(); i != sources.end(); ++i)
    {
        res = max(res, g.findLongestPath(*i)); // O ((V + E)^2)
    }

    std::cout << sources.size() << " " << res + 1 << "\n";

    return 0;
}
