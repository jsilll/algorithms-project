#include <iostream>
#include <limits.h>
#include <list>
#include <stack>

using namespace std;

class Graph
{
    int V;
    list<int> *adj;

public:
    Graph(int V);
    ~Graph();
    void addEdge(int u, int v);
    list<int> derrubarPontas();
    Graph getTranspose();
    void printGraph();
    list<int> getSources();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

Graph::~Graph()
{
    delete[] adj;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < this->V; v++)
    {
        for (list<int>::iterator i = this->adj[v].begin(); i != this->adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

void Graph::printGraph()
{
    for (int v = 0; v < this->V; v++)
    {
        std::cout << v << " -> ";
        for (list<int>::iterator i = this->adj[v].begin(); i != this->adj[v].end(); ++i)
        {
            std::cout << *i << " ";
        }
        std::cout << "\n";
    }
}

list<int> Graph::getSources()
{
    list<int> res;
    for (int v = 0; v < this->V; v++)
    {
        if (this->adj[v].empty())
        {
            res.push_back(v);
        }
    }
    return res;
}

int main(int argc, char const *argv[])
{

    // Ler Cenas de input e decrementar os numeros de cada vertice

    Graph g(7);
    g.addEdge(2, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(5, 4);
    g.addEdge(5, 1);
    g.addEdge(4, 6);
    g.addEdge(1, 6);

    Graph gt = g.getTranspose(); // O(V + E)

    g.printGraph();
    std::cout << "\n";
    gt.printGraph();

    std::cout << "\n";
    for (auto v : gt.getSources()) // O(V)
    {
        std::cout << v << "\n";
    }

    // Para cada source fazer BFS

    // Fazer o output pedido mas agora incrementando o numero de cada vertice

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

// list<int> Graph::derrubarPontas()
// {
//     Graph gt(this->V);
//     for (int i = 0; i < this->V; i++)
//     {
//         std::cout << i << "\n";
//         for (int j = 0; j < sizeof(adj[i]); j++)
//         {

//             std::cout << j << " ";
//         }
//     }

//     // std::list<AdjListNode>::iterator it;
//     // for (it = (*this->adj).begin(); it != (*this->adj).end(); it++)
//     // {
//     // }
// }
