#include <iostream>
#include <limits.h>
#include <list>
#include <stack>

using namespace std;

class AdjListNode
{
    int v;

public:
    AdjListNode(int _v)
    {
        v = _v;
    }
    int getV() { return v; }
};

class Graph
{
    int V;
    list<AdjListNode> *adj;

public:
    Graph(int V);
    ~Graph();
    void addEdge(int u, int v);
    list<int> derrubarPontas();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<AdjListNode>[V];
}

Graph::~Graph()
{
    delete[] adj;
}

void Graph::addEdge(int u, int v)
{
    AdjListNode node(v);
    adj[u].push_back(node); // Add v to u's list
}

list<int> Graph::derrubarPontas()
{
    Graph gt(this->V);
    for (int i = 0; i < this->V; i++)
    {
        std::cout << i << "\n";
        for (int j = 0; j < sizeof(adj[i]); j++)
        {

            std::cout << j << " ";
        }
    }

    // std::list<AdjListNode>::iterator it;
    // for (it = (*this->adj).begin(); it != (*this->adj).end(); it++)
    // {
    // }
}

int main(int argc, char const *argv[])
{
    Graph g(7);
    g.addEdge(2, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(5, 4);
    g.addEdge(5, 1);
    g.addEdge(4, 6);
    g.addEdge(2, 6);

    std::cout << "Hello World\n";

    return 0;
}

/*
Todos os vértices que só tenham arcos de partida vao ter que ser derrubados 1 a 1 (K')
No mínimo temos que derrubar K' vértices

Podemos simplificar o problema se derrubarmos logo todos os vertices sem arcos de chegada

Objetivo:
k corresponde ao número mínimo de intervençoes necessárias para garantir 
que todos os dominós caem e l corresponde ao tamanho da maior sequência de dominós a cair.

1a Parte - Derrubar o Domino pelas pontas
2a Parte - Arranjar a maneira mais eficiente de derrubar o resto

*/