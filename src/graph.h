#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
    int _v;                        // Number of vertices in graph
    vector<vector<int>> _adj;      // Adjacency List
    vector<vector<int>> _capacity; // Capacity Matrix
public:
    Graph(int _v);
    ~Graph() {}
    // Getters
    int getV();
    vector<int> getAdjacent(int u);
    // Setters
    void addEdge(int u, int v);
    void setCapacity(int u, int v, int capacity);
    // Algorithms
    int residualNetworkBFS(int s, int t, vector<int> &parent);
    int edmondsKarp(int s, int t);
    // Print State
    void printCapacityMatrix();
    void printFlowMatrix();
};

Graph::Graph(int v)
{
    _v = v;
    _adj = vector<vector<int>>(v, vector<int>(0));         // adjacency list
    _capacity = vector<vector<int>>(v, vector<int>(v, 0)); // v x v matrix
}

void Graph::addEdge(int u, int v)
{
    _adj[u].push_back(v);
}

void Graph::setCapacity(int u, int v, int capacity)
{
    _capacity[u][v] = capacity;
}

int Graph::residualNetworkBFS(int s, int t, vector<int> &parent) // O(V + E)
{
    fill(parent.begin(), parent.end(), -1);
    parent[s] = 0; // Source is it's own parent
    queue<pair<int, int>> q;
    q.push(make_pair(s, INT_MAX));
    while (!q.empty())
    {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();
        for (int v : _adj[u])
        {
            if (parent[v] == -1 && _capacity[u][v])
            {
                int new_flow = min(flow, _capacity[u][v]);
                parent[v] = u;
                if (v == t)
                {
                    return new_flow;
                }
                q.push(make_pair(v, new_flow));
            }
        }
    }
    return 0;
}

int Graph::edmondsKarp(int s, int t)
{
    int flow = 0;
    int new_flow = 0;
    vector<int> parent(_v, -1);
    while ((new_flow = residualNetworkBFS(s, t, parent))) // O((V + E + E) x f*)
    {
        flow += new_flow;
        for (int u = t; u != s; u = parent[u])
        {
            _capacity[parent[u]][u] -= new_flow;
            _capacity[u][parent[u]] += new_flow;
        }
    }
    return flow;
}

void Graph::printCapacityMatrix()
{
    for (int u = 0; u < _v; u++)
    {
        for (int v = 0; v < _v; v++)
        {
            cout << _capacity[u][v] << " ";
        }
        cout << endl;
    }
}

#endif