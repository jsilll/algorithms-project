#include <iostream>
#include <vector>

using namespace std;

class Graph
{
    int V;
    vector<int> *adj;

public:
    Graph(int V);
    ~Graph();
    void addEdge(int u, int v);
    void printGraph();
    Graph getTranspose();
    vector<int> getSinks();
    vector<int> getSources();
    void DFS(int s, int dp[], bool vis[]);
    int findLongestPath(int n);
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

void Graph::printGraph()
{
    for (int v = 0; v < this->V; v++)
    {
        cout << v << " -> ";
        for (vector<int>::iterator i = this->adj[v].begin(); i != this->adj[v].end(); ++i)
        {
            cout << *i << " ";
        }
        cout << "\n";
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
    Graph gt = this->getTranspose();
    return gt.getSinks();
}

void Graph::DFS(int n, int dp[], bool vis[])
{
    vis[n] = true;
    for (vector<int>::iterator i = this->adj[n].begin(); i != this->adj[n].end(); ++i)
    {
        if (!vis[*i])
            this->DFS(*i, dp, vis);
        dp[n] = max(dp[n], 1 + dp[*i]);
    }
}

int Graph::findLongestPath(int n)
{
    int dp[n];
    for (int i = 0; i < n; i++)
    {
        dp[i] = 0;
    }

    bool vis[n];
    for (int i = 0; i < n; i++)
    {
        vis[i] = false;
    }

    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            this->DFS(i, dp, vis);
        }
    }

    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        ans = max(ans, dp[i]);
    }
    return ans;
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

    cout << g.getSources().size() << " " << g.findLongestPath(n) + 1 << "\n";
    return 0;
}