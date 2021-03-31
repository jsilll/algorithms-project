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

    void addEdge(int u, int v);
    Graph getTranspose();
    vector<int> getAdjacent(int v);
    vector<int> getSinks();
    vector<int> getSources();
    int findLongestPath(vector<int>);
    queue<int> getTopologicalOrder();
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
    Graph gt = this->getTranspose(); // O(V + E)
    return gt.getSinks();
}

queue<int> Graph::getTopologicalOrder()
{
    vector<int> in_degree(V, 0);
    queue<int> q;

    for (int u = 0; u < V; u++)
    {
        vector<int>::iterator itr;
        for (itr = adj[u].begin(); itr != adj[u].end(); itr++)
        {
            in_degree[*itr]++;
        }
    }

    for (int i = 0; i < V; i++)
    {
        if (in_degree[i] == 0)
        {
            q.push(i);
        }
    }

    queue<int> topological_order;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        topological_order.push(u);

        for (vector<int>::iterator i = adj[u].begin(); i != adj[u].end(); i++)
        {
            if (--in_degree[*i] == 0)
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
    queue<int> topological_order = this->getTopologicalOrder();

    for (vector<int>::iterator i = sources.begin(); i != sources.end(); ++i)
    {
        dist[*i] = 1;
    }

    while (topological_order.empty() == false)
    {
        int u = topological_order.front();
        topological_order.pop();

        if (dist[u] != 0)
        {
            for (vector<int>::iterator i = adj[u].begin(); i != adj[u].end(); ++i)
            {
                dist[*i] = max(dist[*i], dist[u] + 1);
                res = max(res, dist[*i]);
            }
        }
    }

    return res;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    Graph g(n);

    int u, v;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);
        g.addEdge(u - 1, v - 1);
    }

    vector<int> sources = g.getSources();
    std::cout << sources.size() << " " << g.findLongestPath(sources) << "\n";
    return 0;
}
