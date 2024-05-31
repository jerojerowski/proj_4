#include <iostream>


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
        hamilton(nodes,sat);
    } 
    else if(mode=="--non-hamilton"){
        cout<<"nodes> ";
        int nodes;
        cin>>nodes;
        non_hamilton(nodes);
    }
    else{
        cout<<"Invalid usage of modes";
        exit(0);
    }


    





    
}