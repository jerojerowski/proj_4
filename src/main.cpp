#include <iostream>
#include "eulercycle.h"
#include "graph.h"
#include "hamcycle.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " --hamilton or --non-hamilton" << endl;
        return 1;
    }

    string mode = argv[1];

    if (mode == "--hamilton") {
        cout << "nodes> ";
        int nodes;
        cin >> nodes;
        cout << "\nsaturation> ";
        int sat;
        cin >> sat;
        Graph g(nodes, sat);
        genHam(g, sat);
        g.print();
        findHam(g);
        findEuler(g);
    } else if (mode == "--non-hamilton") {
        cout << "nodes> ";
        int nodes;
        cin >> nodes;
        Graph g(nodes, 0.5);
        genNonHam(g);
        g.print();
        findHam(g);
        findEuler(g);
    } else {
        cout << "Invalid usage of modes" << endl;
        return 1;
    }

    return 0;
}
