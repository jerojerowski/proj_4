#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <random>
#include <numeric>
#include <algorithm>

using namespace std;

class Graph {
public:
    static void init(int nodes, double sat);
    static void print();
    static void addEdge(int u, int v);
    static void remEdge(int u, int v);
    static int getN();
    static int getDeg(int v);
    static void exportToTikz(const std::string& filename);
    static vector<vector<int>>& getAdj();
     static int n;
    static double s;
    static vector<vector<int>> adj;

private:
};

void genHam(double s);
void genNonHam();

#endif // GRAPH_H
