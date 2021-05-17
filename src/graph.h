#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include "edge.h"
#include "utils.h"

using namespace std;

template <class Edge_Class>
class Graph
{
    int V;
    vector<Edge_Class> *adj;

public:
    Graph(int V)
    {
        this->V = V;
        adj = new vector<Edge_Class>[V];
    }

    ~Graph()
    {
        delete[] adj;
    }

    // Basic Operations
    int getV()
    {
        return V;
    }

    void addEdge(Edge_Class edge)
    {
        adj[edge.getU()].push_back(edge);
    }

    vector<Edge_Class> getAdjacent(int v)
    {
        return adj[v];
    }
};

class W_Graph : public Graph<W_Edge>
{
public:
    W_Graph(int V) : Graph<W_Edge>(V)
    {
    }

    ~W_Graph()
    {
        Graph::~Graph();
    }

    // Basic Operations
    void addEdge(int u, int v, int weight)
    {
        Graph::addEdge(W_Edge(u, v, weight));
    }

    void printGraph()
    {
        for (int u = 0; u < Graph::getV(); u++)
        {
            cout << u << " : ";
            for (vector<W_Edge>::iterator itr = Graph::getAdjacent(u).begin(); itr != Graph::getAdjacent(u).end(); ++itr)
            {
                itr->printEdge();
            }
            cout << endl;
        }
    }

    // Algorithms
    void bfs(int s, int t, vector<int> *d, vector<int> *pi)
    {
        vector<bool> visited(Graph::getV(), false); // -1 white 0 grey 1 black
        queue<int> q;                               // priority queue

        visited[s] = true;
        (*d)[s] = 0;
        q.push(s);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (vector<W_Edge>::iterator itr = Graph::getAdjacent(u).begin(); itr != Graph::getAdjacent(u).end(); ++itr)
            {
                int v = itr->getV();
                if (visited[v] == false)
                {
                    visited[v] = true;
                    q.push(v);
                    (*d)[v] = (*d)[u] + 1;
                    (*pi)[v] = u;

                    if (v == t)
                    {
                        return;
                    }
                }
            }
        }
    }
};

class F_Graph : public Graph<F_Edge>
{
public:
    F_Graph(int V) : Graph(V)
    {
    }

    ~F_Graph()
    {
        Graph::~Graph();
    }

    // Basic Operations
    void addEdge(int u, int v, int capacity)
    {
        Graph::addEdge(F_Edge(u, v, capacity));
    }

    void printGraph()
    {
        for (int u = 0; u < Graph::getV(); u++)
        {
            cout << u << " : ";
            for (vector<F_Edge>::iterator itr = Graph::getAdjacent(u).begin(); itr != Graph::getAdjacent(u).end(); ++itr)
            {
                itr->printEdge();
            }
            cout << endl;
        }
    }

    // Algorithms
    W_Graph buildResidualNetwork()
    {
        W_Graph gf(Graph::getV()); // Construir a rede residual

        for (int u = 0; u < Graph::getV(); u++)
        {
            for (vector<F_Edge>::iterator itr = Graph::getAdjacent(u).begin(); itr != Graph::getAdjacent(u).end(); ++itr)
            {
                int v = itr->getV();
                int f = itr->getFlow();
                int rc = itr->getResidualCapacity();
                if (rc)
                {
                    gf.addEdge(u, v, rc);
                }
                if (f)
                {
                    gf.addEdge(v, u, f);
                }
            }
        }

        return gf;
    }

    int edmondsKarp(int s, int t)
    {
        int total_flow = 0;
        W_Graph gf = this->buildResidualNetwork();

        vector<int> d(Graph::getV(), -1);
        vector<int> pi(Graph::getV(), -1);

        gf.bfs(s, t, &d, &pi);
        while (d[Graph::getV() - 1] != -1) // means we reached the sink
        {
            int max_flow = INT_MAX; // max posible flow to increase after bfs call
            int v = t;
            int u = pi[v];
            vector<F_Edge *> forward_edges;
            vector<F_Edge *> backwards_edges;
            bool found_edge = false;

            cout << "Found Increase Path:" << endl;
            while (u != -1) // Percorrer o caminho do sink para a source
            {
                found_edge = false;

                // Forward Edge
                for (std::size_t i = 0; i < Graph::getAdjacent(u).size(); i++)
                {
                    if (Graph::getAdjacent(u)[i].getV() == v)
                    {
                        max_flow = min(max_flow, Graph::getAdjacent(u)[i].getResidualCapacity());
                        forward_edges.push_back(&Graph::getAdjacent(u)[i]);
                        cout << "(" << Graph::getAdjacent(u)[i].getU() << ", " << Graph::getAdjacent(u)[i].getV() << ")";
                        found_edge = true;
                        break;
                    }
                }

                if (!found_edge)
                {
                    // Backwards Edge
                    for (std::size_t i = 0; i < Graph::getAdjacent(v).size(); i++)
                    {
                        if (Graph::getAdjacent(v)[i].getV() == u)
                        {
                            max_flow = min(max_flow, Graph::getAdjacent(v)[i].getFlow());
                            backwards_edges.push_back(&Graph::getAdjacent(v)[i]);
                            cout << "(" << Graph::getAdjacent(u)[i].getU() << ", " << Graph::getAdjacent(u)[i].getV() << ")";
                            break;
                        }
                    }
                }
                v = u;
                u = pi[v];
            }
            cout << endl;

            total_flow += max_flow;

            // Increase flow in forward edges
            for (std::size_t i = 0; i < forward_edges.size(); i++)
            {
                forward_edges[i]->setFlow(forward_edges[i]->getFlow() + max_flow);
            }

            // Decrease flow in backwards edges
            for (std::size_t i = 0; i < backwards_edges.size(); i++)
            {
                backwards_edges[i]->setFlow(backwards_edges[i]->getFlow() - max_flow);
            }

            // Resetting the vectors
            for (int i = 0; i < Graph::getV(); i++)
            {
                d[i] = -1;
                pi[i] = -1;
            }

            W_Graph gf = this->buildResidualNetwork();
            gf.bfs(s, t, &d, &pi);
        }

        cout << "Fluxo Máximo: " << total_flow << endl;
        cout << "Corte Minimo:" << endl;
        printVector(d);

        return total_flow;
    }
};

#endif