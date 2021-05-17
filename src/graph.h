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
    vector<vector<int>> _flow;     // Flow Matrix

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
    int edmondKarp(int s, int t);

    // Print State
    void printCapacityMatrix();
    void printFlowMatrix();
};

Graph::Graph(int v)
{
    _v = v;
    _adj = vector<vector<int>>(v, vector<int>(0));         // adjacency list
    _capacity = vector<vector<int>>(v, vector<int>(v, 0)); // v x v matrix
    _flow = vector<vector<int>>(v, vector<int>(v, 0));     // v x v matrix
}

void Graph::addEdge(int u, int v)
{
    _adj[u].push_back(v);
}

void Graph::setCapacity(int u, int v, int capacity)
{
    _capacity[u][v] = capacity;
}

int Graph::residualNetworkBFS(int s, int t, vector<int> &parent)
{
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});
    while (!q.empty())
    {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();
        for (int next : _adj[cur])
        {
            if (parent[next] == -1)
            {
                // Forwards Edge Case
                if (_capacity[cur][next] - _flow[cur][next])
                {
                    parent[next] = cur;
                    int new_flow = min(flow, _capacity[cur][next] - _flow[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push(make_pair(next, new_flow));
                }
                // Backwards Edge Case
                if (_flow[next][cur])
                {
                    parent[next] = cur;
                    int new_flow = min(flow, _flow[next][cur]);
                    if (next == t)
                        return new_flow;
                    q.push(make_pair(next, new_flow));
                }
            }
        }
    }
    return 0;
}

int Graph::edmondKarp(int s, int t)
{
    int flow = 0;
    int new_flow = 0;
    vector<int> parent(_v, -1);
    int cur = t;
    while ((new_flow = residualNetworkBFS(s, t, parent)))
    {
        flow += new_flow;
        while (cur != s)
        {
            int prev = parent[cur];

            //  Check for back-edge reduction first
            if (_flow[cur][prev] >= new_flow)
            {
                _flow[cur][prev] -= new_flow;
            }
            else
            {
                _flow[prev][cur] += new_flow;
            }

            cur = prev;
        }
        cur = t;
    }
    // Print Parents Vector, corresponds to minimum cut on residual network
    // cout << "Minimum Cut" << endl;
    // for (int p : parent)
    // {
    //     cout << p << " ";
    // }
    // cout << endl;
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

void Graph::printFlowMatrix()
{
    for (int u = 0; u < _v; u++)
    {
        for (int v = 0; v < _v; v++)
        {
            cout << _flow[u][v] << " ";
        }
        cout << endl;
    }
}

#endif