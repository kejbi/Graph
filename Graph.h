//
// Created by kejbi on 30.12.18.
//

#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <vector>

class Graph{
public:
    using adjVector = std::vector<std::vector<int>>;
private:
    adjVector adjacency;
    int vertices;

    void dfs(int startVertex, adjVector& adjacency, bool visited[]){
        visited[startVertex]=true;

        for(auto neighbour: adjacency[startVertex]){
            if(!visited[neighbour]){
                dfs(neighbour, adjacency, visited);
            }
        }
    }





public:
    Graph():adjacency(adjVector()), vertices(0){}

    Graph(int vertices, std::vector<std::pair<int,int>>& edges):vertices(vertices),
                                                               adjacency(adjVector(vertices)){
        for(auto edge: edges){
            adjacency[edge.first].push_back(edge.second);
            adjacency[edge.second].push_back(edge.first);
        }
    }

    adjVector& getAdjacency(){
        return adjacency;
    }


};

#endif //GRAPHS_GRAPH_H
