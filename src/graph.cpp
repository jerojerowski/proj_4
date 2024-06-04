#include "graph.h"

int Graph::n = 0;
double Graph::s = 0.0;
vector<vector<int>> Graph::adj;

void Graph::init(int nodes, double sat) {
    n = nodes;
    s = sat;
    adj = vector<vector<int>>(n, vector<int>(n, 0));
}

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

void genHam(double s) {
    int n = Graph::getN();
    vector<int> cycle(n);
    iota(cycle.begin(), cycle.end(), 0);
    shuffle(cycle.begin(), cycle.end(), mt19937{random_device{}()});

    for (int i = 0; i < n; ++i) {
        Graph::addEdge(cycle[i], cycle[(i + 1) % n]);
    }

    int edgeCnt = n;
    int tgtEdges = static_cast<int>((n * (n - 1) / 2) * s / 100);

    while (edgeCnt < tgtEdges) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && Graph::getAdj()[u][v] == 0) {
            Graph::addEdge(u, v);
            edgeCnt++;
        }
    }

    // Ensure every vertex has an even degree
    for (int i = 0; i < n; ++i) {
        int deg = accumulate(Graph::getAdj()[i].begin(), Graph::getAdj()[i].end(), 0);
        if (deg % 2 != 0) {
            for (int j = 0; j < n; ++j) {
                if (i != j && Graph::getAdj()[i][j] == 0) {
                    Graph::addEdge(i, j);
                    break;
                }
            }
        }
    }
}

void genNonHam() {
    genHam(50);
    int isolated = rand() % Graph::getN();
    for (int i = 0; i < Graph::getN(); ++i) {
        Graph::remEdge(isolated, i);
    }
}
