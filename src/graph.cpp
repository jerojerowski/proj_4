#include "graph.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <iostream>

using namespace std;

Graph::Graph(int n, double s) : n(n), s(s), adj(n, vector<int>(n, 0)) {}

void Graph::print() {
    for (const auto& row : adj) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void Graph::addEdge(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;
}

void Graph::remEdge(int u, int v) {
    adj[u][v] = 0;
    adj[v][u] = 0;
}

int Graph::getN() {
    return n;
}

vector<vector<int>>& Graph::getAdj() {
    return adj;
}

void genHam(Graph& g, double s) {
    int n = g.getN();
    vector<int> cycle(n);
    iota(cycle.begin(), cycle.end(), 0);
    shuffle(cycle.begin(), cycle.end(), mt19937{random_device{}()});
    for (int i = 0; i < n; ++i) {
        g.addEdge(cycle[i], cycle[(i + 1) % n]);
    }
    int edgeCnt = n;
    int tgtEdges = static_cast<int>((n * (n - 1) / 2) * s);
    while (edgeCnt < tgtEdges) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && g.getAdj()[u][v] == 0) {
            g.addEdge(u, v);
            edgeCnt++;
        }
    }
}

void genNonHam(Graph& g) {
    genHam(g, 0.5);
    int isolated = rand() % g.getN();
    for (int i = 0; i < g.getN(); ++i) {
        g.remEdge(isolated, i);
    }
}
