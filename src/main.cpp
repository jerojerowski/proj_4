#include <iostream>
#include "eulercycle.h"
#include "graph.h"
#include "hamcycle.h"
#include "hamgraph.h"
#include "nonhamgraph.h"


using namespace std;


main(int argc, char* argv[]){
    if(argc!=2){
        cout<<"Usage: "<<argv[0]<<" --hamilton or --non-hamilton"<<endl;
        return 1;
    }

    string mode=argv[1];

    if(mode=="--hamilton"){
        cout<<"nodes> ";
        int nodes;
        cin>>nodes;
        cout<<"\nsaturation> ";
        int sat;
        cin>>sat;
        Graph Graph(nodes,sat);
        hamilton(sat);
    } 
    else if(mode=="--non-hamilton"){
        cout<<"nodes> ";
        int nodes;
        cin>>nodes;
        Graph Graph(nodes,50);
        non_hamilton();
    }
    else{
        cout<<"Invalid usage of modes";
        exit(0);
    }

    printGraph();
}