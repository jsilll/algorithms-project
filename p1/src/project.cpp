#include <iostream>
#include <vector>
// #include <limits.h>
// #include <list>
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
    vector<int> derrubarPontas();
    Graph getTranspose();
    void printGraph();
    vector<int> getSources();
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

vector<int> Graph::getSources()
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

int main(int argc, char const *argv[])
{
    // Ler Cenas de input e decrementar os numeros de cada vertice

    // int k; // numero minimo de intervencoes necessarias para que todos os dominos caiam
    // int l; // tamanho da maior sequencia de dominos a cair

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

    // Para cada source fazer BFS?? E quantos dominos e que se conseguem derrubar em cada caso (guardar o valor maximo de dominos que se derrubariam de entre todas as sources)
    // Mais BFS

    // Fazer o output pedido mas agora incrementando o numero de cada vertice

    return 0;
}