#include <iostream>
#include <vector>
#include "Graph.h"

using namespace std;

int main(int argc, char* argv[]) {
    size_t size;
    pair<size_t,size_t> edge;
    vector<pair<size_t,size_t>> edges;

    cin>>size;

    while(cin){
        cin>>edge.first>>edge.second;
        edges.push_back(edge);
    }

    Graph g(size,edges);

    for(auto &e: g.getExtensiveBridges()){
        cout<<e.first<<" "<<e.second<<endl;
    }
}