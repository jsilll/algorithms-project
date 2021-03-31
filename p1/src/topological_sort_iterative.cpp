#include <iostream>
#include <limits.h>
#include <list>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
    int V;

    vector<int> *adj;
    vector<int> topologicalSort();

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

vector<int> Graph::topologicalSort()
{
    // Create a vector to store indegrees of all
    // vertices. Initialize all indegrees as 0.
    vector<int> in_degree(V, 0);

    // Traverse adjacency lists to fill indegrees of
    // vertices.  This step takes O(V+E) time
    for (int u = 0; u < V; u++)
    {
        vector<int>::iterator itr;
        for (itr = adj[u].begin(); itr != adj[u].end(); itr++)
            in_degree[*itr]++;
    }

    // Create a queue and enqueue all vertices with
    // indegree 0
    queue<int> q;
    for (int i = 0; i < V; i++)
        if (in_degree[i] == 0)
            q.push(i);

    // Initialize count of visited vertices
    int cnt = 0;

    // Create a vector to store result (A topological
    // ordering of the vertices)
    vector<int> top_order;

    // One by one dequeue vertices from queue and enqueue
    // adjacents if indegree of adjacent becomes 0
    while (!q.empty())
    {
        // Extract front of queue (or perform dequeue)
        // and add it to topological order
        int u = q.front();
        q.pop();
        top_order.push_back(u);

        // Iterate through all its neighbouring nodes
        // of dequeued node u and decrease their in-degree
        // by 1
        vector<int>::iterator itr;
        for (itr = adj[u].begin(); itr != adj[u].end(); itr++)

            // If in-degree becomes zero, add it to queue
            if (--in_degree[*itr] == 0)
                q.push(*itr);

        cnt++;
    }

    return top_order;
}

int Graph::findLongestPath(int s)
{
    vector<int> top_order;
    int dist[V];

    top_order = this->topologicalSort();

    for (int i = 0; i < V; i++)
        dist[i] = INT_MIN;
    dist[s] = 0;

    while (top_order.empty() == false)
    {
        int u = top_order.front();
        top_order.erase(top_order.begin());

        if (dist[u] != INT_MIN)
        {
            for (vector<int>::iterator i = adj[u].begin(); i != adj[u].end(); ++i)
            {
                dist[*i] = max(dist[*i], dist[u] + 1);
            }
        }
    }

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
        // tem de ser a partir das sources
        res = max(res, g.findLongestPath(*i)); // O ((V + E) * S)
    }
    std::cout << sources.size() << " " << res + 1 << "\n";
    return 0;
}
