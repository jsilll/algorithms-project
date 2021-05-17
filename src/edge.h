#ifndef EDGE_H
#define EDGE_H

class Edge
{
    int u;
    int v;

public:
    Edge(int _u, int _v)
    {
        u = _u;
        v = _v;
    }
    int getU() { return u; }
    int getV() { return v; }
    void printEdge()
    {
        return;
    }
};

class W_Edge : public Edge
{
    int weight;

public:
    W_Edge(int _u, int _v, int _w) : Edge(_u, _v)
    {
        weight = _w;
    }
    int getW() { return weight; }
};

class F_Edge : public Edge
{
private:
    int c;
    int f;

public:
    F_Edge(int _u, int _v, int _c, int _f = 0) : Edge(_u, _v)
    {
        c = _c;
        f = _f;
    }

    int getCapacity() { return c; }
    int getFlow() { return f; }
    int getResidualCapacity()
    {
        return c - f;
    }
    void setFlow(int _f)
    {
        f = _f;
    }
};

#endif