#include <iostream>
#include "eulercycle.h"
#include "graph.h"
#include "hamcycle.h"

using namespace std;

bool checkEvenDegrees() {
    for (int i = 0; i < Graph::getN(); ++i) {
        int deg = accumulate(Graph::getAdj()[i].begin(), Graph::getAdj()[i].end(), 0);
        if (deg % 2 != 0) {
            return false;
        }
    }
    return true;
}

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
        Graph::init(nodes, sat);
        genHam(sat);
    } else if (mode == "--non-hamilton") {
        cout << "nodes> ";
        int nodes;
        cin >> nodes;
        Graph::init(nodes, 50);
        genNonHam();
    } else {
        cout << "Invalid usage of modes" << endl;
        return 1;
    }

    while(true){
        cout<<"action> ";
        string action;
        cin>>action;
        if(action=="Print"){
            Graph::print();
        }
        else if(action=="Ham"){
            findHam();
        }
        else if(action=="Euler"){
            findEuler();
        }
        else if(action=="exit"){
            cout<<"Exiting program"<<endl;
            exit(0);
        }
        else if(action=="Even"){
             if(checkEvenDegrees()) cout<<"All are even"<<endl;
        }
        else if(action=="Tikz"){
            string filename;
            cout<<"File name> ";
            cin>>filename;
            Graph::exportToTikz(filename);
        }
        else cout<<"Incorect command"<<endl;
    }

    return 0;
}
