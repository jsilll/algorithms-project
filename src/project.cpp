#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
    int V;
    vector<int> *adj;

public:
    Graph(int V);
    ~Graph();

    void addEdge(int v, int u);
    Graph getTranspose();
    vector<int> getAdjacent(int v);
    vector<int> getSinks();
    vector<int> getSources();
    int findLongestPath(vector<int> sources);
    queue<int> getTopologicalOrder(vector<int> sources);
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

void Graph::addEdge(int v, int u)
{
    adj[v].push_back(u);
}

Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++)
    {
        for (vector<int>::iterator i = this->adj[v].begin(); i != this->adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

vector<int> Graph::getAdjacent(int v)
{
    return this->adj[v];
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
    Graph gt = this->getTranspose();
    return gt.getSinks();
}

queue<int> Graph::getTopologicalOrder(vector<int> sources)
{
    vector<int> in_edges(V, 0);
    queue<int> q, topological_order;

    for (int i = 0; i < V; i++)
    {
        for (vector<int>::iterator j = adj[i].begin(); j != adj[i].end(); j++)
        {
            in_edges[*j]++;
        }
    }

    for (vector<int>::iterator i = sources.begin(); i != sources.end(); ++i)
    {
        q.push(*i);
    }

    int v;
    while (!q.empty())
    {
        v = q.front();
        q.pop();

        topological_order.push(v);

        for (vector<int>::iterator i = adj[v].begin(); i != adj[v].end(); i++)
        {
            if (--in_edges[*i] == 0)
            {
                q.push(*i);
            }
        }
    }

    return topological_order;
}

int Graph::findLongestPath(vector<int> sources)
{

    int res = 1;
    vector<int> dist = vector<int>(V, 0);
    queue<int> topological_order = this->getTopologicalOrder(sources);

    for (vector<int>::iterator i = sources.begin(); i != sources.end(); ++i)
    {
        dist[*i] = 1;
    }

    int v;
    while (topological_order.empty() == false)
    {
        v = topological_order.front();
        topological_order.pop();

        for (vector<int>::iterator i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            dist[*i] = max(dist[*i], dist[v] + 1);
            res = max(res, dist[*i]);
        }
    }

    return res;
}

int main()
{
    int n, m, u, v;

    scanf("%d %d", &n, &m);

    Graph g(n);

    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);
        g.addEdge(u - 1, v - 1);
    }

    vector<int> sources = g.getSources();
    std::cout << sources.size() << " " << g.findLongestPath(sources) << "\n";
    return 0;
}