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
        cout << "saturation> ";
        double sat;
        cin >> sat;
        sat=sat/100;
        Graph::init(nodes, sat);
        genHam(sat);
        Graph::print();
        findHam();
        findEuler();
    } else if (mode == "--non-hamilton") {
        cout << "nodes> ";
        int nodes;
        cin >> nodes;
        Graph::init(nodes, 0.5);
        genNonHam();
        Graph::print();
        findHam();
        findEuler();
    } else {
        cout << "Invalid usage of modes" << endl;
        return 1;
    }

    return 0;
}
