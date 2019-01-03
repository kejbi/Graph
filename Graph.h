//
// Created by kejbi on 30.12.18.
//

#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <vector>
#include <algorithm>

class Graph{
public:
    using adjVector = std::vector<std::vector<int>>;
    using edge = std::pair<int,int>;
    using edgesVector = std::vector<std::pair<int,int>>;
private:
    adjVector adjacency;
    edgesVector edges;
    int vertices;

    void dfs(int startVertex, adjVector& adjacency, bool visited[]){
        visited[startVertex]=true;

        for(auto neighbour: adjacency[startVertex]){
            if(!visited[neighbour]){
                dfs(neighbour, adjacency, visited);
            }
        }
    }

    bool isExtensiveBridge(edge& edge) {
        auto newAdjacency = adjacency;
        int startVertex = -1;

        for (auto i = 0; i < vertices; ++i) {
            if (i != edge.first && i != edge.second) {
                newAdjacency[i].erase(std::remove_if(newAdjacency[i].begin(), newAdjacency[i].end(), [&edge](int vertex) {
                    return vertex == edge.first || vertex == edge.second;
                }),newAdjacency[i].end());
                startVertex = i;
            }
        }

        if (startVertex == -1) return false;

        bool visited[vertices] = {false};
        dfs(startVertex, newAdjacency, visited);
        auto verticesCounted = std::count_if(visited, visited + vertices, [](bool visit) { return visit; });

        return verticesCounted + 2 != vertices;
    }

public:
    Graph():adjacency(adjVector()),edges(edgesVector()), vertices(0){}

    Graph(int vertices, edgesVector & edges):vertices(vertices), edges(edges),
                                                               adjacency(adjVector(vertices)){
        for(auto edge: edges){
            adjacency[edge.first].push_back(edge.second);
            adjacency[edge.second].push_back(edge.first);
        }
    }

    edgesVector getExtensiveBridges(){
        edgesVector bridges;
        for(auto& edge: edges){
            if(isExtensiveBridge(edge)){
                bridges.push_back(edge);
            }
        }
        return bridges;
    }

    adjVector& getAdjacency(){
        return adjacency;
    }


};

#endif //GRAPHS_GRAPH_H
