#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

using namespace std;

class Graph {
public:
    Graph(int n, double s);
    void print();
    void addEdge(int u, int v);
    void remEdge(int u, int v);
    int getN();
    vector<vector<int>>& getAdj();

private:
    int n;
    double s;
    vector<vector<int>> adj;
};

void genHam(Graph& g, double s);
void genNonHam(Graph& g);

#endif
