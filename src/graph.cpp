#include "graph.h"
#include <iostream>
#include <numeric>
#include <random>
#include <algorithm>
#include <fstream>
#include <set>
#include <utility>

using namespace std;

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

int Graph::getDeg(int v) {
    int deg = 0;
    for (int j = 0; j < getN(); ++j) {
        deg += getAdj()[v][j];
    }
    return deg;
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

    // Create a Hamiltonian cycle
    for (int i = 0; i < n; ++i) {
        Graph::addEdge(cycle[i], cycle[(i + 1) % n]);
    }

    // Ensure all degrees are even
    vector<int> oddVertices;
    for (int i = 0; i < n; ++i) {
        if (Graph::getDeg(i) % 2 != 0) {
            oddVertices.push_back(i);
        }
    }

    while (!oddVertices.empty()) {
        int v1 = oddVertices.back();
        oddVertices.pop_back();
        int v2 = oddVertices.back();
        oddVertices.pop_back();
        Graph::addEdge(v1, v2);
    }

    const auto& adj = Graph::getAdj();
    int edgeCnt = 0;
    for (const auto& row : adj) {
        edgeCnt += std::accumulate(row.begin(), row.end(), 0);
    }
    edgeCnt /= 2;

    int tgtEdges = static_cast<int>((n * (n - 1) / 2) * s / 100);

    set<pair<int, int>> addedEdges;
    while (edgeCnt < tgtEdges) {
        int u = rand() % n;
        int v = rand() % n;
        int w = rand() % n;

        if (u != v && u != w && v != w && 
            Graph::getAdj()[u][v] == 0 && Graph::getAdj()[v][w] == 0 && Graph::getAdj()[w][u] == 0) {
            
            Graph::addEdge(u, v);
            Graph::addEdge(v, w);
            Graph::addEdge(w, u);

            edgeCnt += 3;
            addedEdges.emplace(min(u, v), max(u, v));
            addedEdges.emplace(min(v, w), max(v, w));
            addedEdges.emplace(min(w, u), max(w, u));
        }
    }

    // Ensure all degrees are even again after adding edges
    oddVertices.clear();
    for (int i = 0; i < n; ++i) {
        if (Graph::getDeg(i) % 2 != 0) {
            oddVertices.push_back(i);
        }
    }

    while (!oddVertices.empty()) {
        int v1 = oddVertices.back();
        oddVertices.pop_back();
        int v2 = oddVertices.back();
        oddVertices.pop_back();
        Graph::addEdge(v1, v2);
    }
}

void genNonHam() {
    double s = 50.0;
    int n = Graph::getN();
    genHam(s);
    int isolatedNode = rand() % n;
    for (int i = 0; i < n; ++i) {
        if (i != isolatedNode && Graph::getAdj()[isolatedNode][i] == 1) {
            Graph::remEdge(isolatedNode, i);
        }
    }
    cout << "Isolated node: " << isolatedNode+1 << endl;
}


void Graph::exportToTikz(const std::string& filename) {
    ofstream outFile(filename);

    outFile << "\\documentclass{standalone}\n";
    outFile << "\\usepackage{tikz}\n";
    outFile << "\\begin{document}\n";
    outFile << "\\begin{tikzpicture}[>=stealth,shorten >=1pt,auto,node distance=1.5cm,thick]\n";
    outFile << "\\tikzstyle{every node}=[circle,fill=white,draw=black,text=black]\n";

    const double radius = 3.0;
    int n = Graph::getN();

    for (int i = 0; i < n; ++i) {
        double angle = 2.0 * M_PI * i / n;
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        outFile << "\\node (" << i + 1 << ") at (" << x << "," << y << ") {" << i + 1 << "};\n";
    }

    const auto& adjacencyMatrix = Graph::getAdj();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) { 
            if (adjacencyMatrix[i][j]) {
                outFile << "\\draw (" << i + 1 << ") -- (" << j + 1 << ");\n";
            }
        }
    }

    outFile << "\\end{tikzpicture}\n";
    outFile << "\\end{document}\n";
    outFile.close();
}
