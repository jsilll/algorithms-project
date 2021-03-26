#include <iostream>
#include <vector>
#include <list>
// #include <queue>
// #include <limits.h>
// #include <stack>

using namespace std;

class Graph
{
    int V;
    // maybe usar vector (mais eficiente neste caso acho eu)
    vector<int> *adj;

public:
    Graph(int V);
    ~Graph();
    void addEdge(int u, int v);
    void printGraph();
    Graph getTranspose();
    vector<int> getSinks();
    vector<int> getSources();
    int BFS(int s);
    int getMaxChain();
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

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

void Graph::printGraph()
{
    for (int v = 0; v < this->V; v++)
    {
        std::cout << v << " -> ";
        for (vector<int>::iterator i = this->adj[v].begin(); i != this->adj[v].end(); ++i)
        {
            std::cout << *i << " ";
        }
        std::cout << "\n";
    }
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

int Graph::BFS(int s)
{
    int visited_count = 0;
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    list<int> queue;

    visited[s] = true;
    visited_count++;

    queue.push_back(s);

    while (!queue.empty())
    {
        s = queue.front();
        queue.pop_front();

        for (vector<int>::iterator i = this->adj[s].begin(); i != this->adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                visited_count++;
                queue.push_back(*i);
            }
        }
    }

    return visited_count;
}

int Graph::getMaxChain()
{
    vector<int> sources = this->getSources();
    int l = 0;
    for (vector<int>::iterator i = sources.begin(); i != sources.end(); ++i)
    {
        int chain_size = this->BFS(*i);
        if (chain_size > l)
            l = chain_size;
    }
    return l - 1;
}

int main(int argc, char const *argv[])
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

    std::cout << g.getSources().size() << " " << g.getMaxChain() << "\n";
    return 0;
}