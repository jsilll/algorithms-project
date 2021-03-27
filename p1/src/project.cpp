#include <iostream>
#include <vector>
#include <list>
#include <bits/stdc++.h>

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
    int BFS(int s, int dp[]);
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

int Graph::BFS(int s, int dp[])
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
            dp[s] = max(dp[s], 1 + dp[*i]);
        }
    }

    return visited_count;
}

int Graph::findLongestPath(int n)
{
    int dp[n];
    memset(dp, 0, sizeof(int) * n);

    bool vis[n];
    memset(vis, false, sizeof(bool) * n);

    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            this->BFS(i, dp);
            // this->DFS(i, dp, vis);
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

    std::cout << g.getSources().size() << " " << g.findLongestPath(n) + 1 << "\n";
    return 0;
}