//
// Created by kejbi on 30.12.18.
//

#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <vector>
#include <algorithm>
#include <stdexcept>

class Graph{
public:
    using adjVector = std::vector<std::vector<size_t>>;
    using edge = std::pair<size_t,size_t>;
    using edgesVector = std::vector<std::pair<size_t,size_t>>;
private:
    adjVector adjacency;
    edgesVector edges;
    size_t size;

    size_t dfs(size_t startVertex, bool visited[]){
        visited[startVertex]=true;
        size_t counter = 1;
        for(auto neighbour: adjacency[startVertex]){
            if(!visited[neighbour]){
                counter+=dfs(neighbour, visited);
            }
        }
        return counter;
    }


    bool isExtensiveBridge(edge& edge) {
        bool foundVertex = false;
        size_t startVertex=0;

        for (size_t i = 0; i < size; ++i) {
            if (i != edge.first && i != edge.second) {
                foundVertex=true;
                startVertex = i;
                break;
            }
        }

        if (!foundVertex) return false;
        bool visited[size] = {false};
        visited[edge.first]=true;
        visited[edge.second]=true;

        return dfs(startVertex,visited) + 2 != size;
    }
    bool addingLonelyVertices(size_t vertex1, size_t vertex2){
        if(vertex1>size-1){
            for(size_t i=size; i<=vertex1; ++i){
                adjacency.emplace_back(std::vector<size_t>{});
            }
            adjacency[vertex1].push_back(vertex2);
            size=vertex1+1;
            return true;
        }
        return false;
    }

public:
    Graph():adjacency(adjVector()),edges(edgesVector()), size(0){}

    Graph(size_t size, edgesVector & edges):size(size), edges(edges),
                                                               adjacency(adjVector(size)){
        for(auto edge: edges){
            adjacency[edge.first].push_back(edge.second);
            adjacency[edge.second].push_back(edge.first);
        }
    }

    void addVertex(){
        ++size;
        adjacency.emplace_back(std::vector<size_t>{});
    }

    void addEdge(edge& edge){
//        if(edge.first>size && edge.second>size) throw std::out_of_range("");
        edges.push_back(edge);
        if(!addingLonelyVertices(edge.first, edge.second)){
            adjacency[edge.first].push_back(edge.second);
        }
        if(!addingLonelyVertices(edge.second, edge.first)){
            adjacency[edge.second].push_back(edge.first);
        }
    }

    void pop(size_t vertex){
        auto it = adjacency.begin();
        adjacency.erase(it+vertex);
        for(auto &item: adjacency){
            auto i = item.begin();
            while(i!=item.end()){
                if(*i==vertex){
                    i=item.erase(i);
                    continue;
                }
                if(*i>vertex){
                    --(*i);
                }
                ++i;
            }
        }
        auto i = edges.begin();
        while(i!=edges.end()){
            if((*i).first == vertex || (*i).second == vertex){
                i=edges.erase(i);
                continue;
            }
            if((*i).first > vertex){
                --((*i).first);
            }
            if((*i).second > vertex){
                --((*i).second);
            }
            ++i;
        }
        --size;
    }

    size_t getSize(){
        return size;
    }

    edgesVector& getEdges(){
        return edges;
    }

    adjVector& getAdjacency(){
        return adjacency;
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



};

#endif //GRAPHS_GRAPH_H
