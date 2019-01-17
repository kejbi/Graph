//
// Created by kejbi on 31.12.18.
//

#define CATCH_CONFIG_MAIN

#include "Graph.h"
#include "catch.h"

TEST_CASE("Graph Constructor"){
    std::vector<std::pair<size_t,size_t>> edges = {{1, 2}, {0, 2}};
    Graph g(3, edges);
    auto adj = g.getAdjacency();
    REQUIRE(adj[0].size() == 1);
    REQUIRE(adj[1].size() == 1);
    REQUIRE(adj[2].size() == 2);
    REQUIRE(adj[0][0] == 2);
    REQUIRE(adj[1][0] == 2);
    REQUIRE(adj[2][0] == 1);
    REQUIRE(adj[2][1] == 0);
}
TEST_CASE("Adding edge, size exist"){
    std::vector<std::pair<size_t,size_t>> edges = {{1, 2}, {0, 2}};
    Graph g(3, edges);
    std::pair<size_t, size_t> edge(0,1);
    g.addEdge(edge);
    auto adj=g.getAdjacency();
    REQUIRE(adj[0].size() == 2);
    REQUIRE(adj[1].size() == 2);
    REQUIRE(adj[1][1] == 0);
    REQUIRE(adj[0][1] == 1);
}
TEST_CASE("Extensive Bridges, empty graph"){
    std::vector<std::pair<size_t,size_t>> edges = {};
    Graph g(0, edges);
    auto bridges = g.getExtensiveBridges();
    REQUIRE(bridges == edges);
}
TEST_CASE("Extensive Bridges, not empty graph"){
    std::vector<std::pair<size_t,size_t>> edges = {{0,1},{0,2},{0,3},{1,2},{2,3}};
    Graph g(4, edges);
    auto foundBridges = g.getExtensiveBridges();
    std::vector<std::pair<size_t,size_t>> requiredBridges = {{0,2}};
    REQUIRE(foundBridges == requiredBridges);
}
TEST_CASE("Extensive Bridges, not empty graph, no bridges"){
    std::vector<std::pair<size_t,size_t>> edges = {{0,1},{0,2},{0,3},{1,2},{2,3},{1,3}};
    Graph g(4, edges);
    auto foundBridges = g.getExtensiveBridges();
    std::vector<std::pair<size_t,size_t>> requiredBridges = {};
    REQUIRE(foundBridges == requiredBridges);
}
TEST_CASE("Extensive Bridges, not empty graph, 3 bridges"){
    std::vector<std::pair<size_t,size_t>> edges = {{0,1},{0,2},{0,3},{1,2},{2,3},{4,3}};
    Graph g(5, edges);
    auto foundBridges = g.getExtensiveBridges();
    std::vector<std::pair<size_t,size_t>> requiredBridges = {{0,2}, {0,3}, {2,3}};
    REQUIRE(foundBridges == requiredBridges);
}
TEST_CASE("Extensive Bridges, not empty graph - only one edge, no bridges"){
    std::vector<std::pair<size_t,size_t>> edges = {{0,1}};
    Graph g(2, edges);
    auto foundBridges = g.getExtensiveBridges();
    std::vector<std::pair<size_t,size_t>> requiredBridges = {};
    REQUIRE(foundBridges == requiredBridges);
}

TEST_CASE("Extensive Bridges, not empty graph - 3 size, no bridges"){
    std::vector<std::pair<size_t,size_t>> edges = {{0,1},{0,2}};
    Graph g(3, edges);
    auto foundBridges = g.getExtensiveBridges();
    std::vector<std::pair<size_t,size_t>> requiredBridges = {};
    REQUIRE(foundBridges == requiredBridges);
}
TEST_CASE("Extensive Bridges, not empty graph - without edges, no bridges"){
    std::vector<std::pair<size_t,size_t>> edges = {};
    Graph g(4, edges);
    auto foundBridges = g.getExtensiveBridges();
    std::vector<std::pair<size_t,size_t>> requiredBridges = {};
    REQUIRE(foundBridges == requiredBridges);
}
TEST_CASE("Adding vertex"){
    std::vector<std::pair<size_t,size_t>> edges = {{0,1},{0,2},{0,3},{1,2},{2,3},{1,3}};
    Graph g(4, edges);
    std::vector<size_t> empty = {};
    g.addVertex();
    REQUIRE(g.getSize() == 5);
    REQUIRE(g.getAdjacency()[4]==empty);
}
TEST_CASE("Adding edge"){
    std::vector<std::pair<size_t,size_t>> edges = {{0,1},{0,2},{0,3},{1,2},{2,3},{1,3},{1,4}};
    Graph g(5, edges);
    std::pair<size_t,size_t> edge = {2,4};
    g.addEdge(edge);
    REQUIRE(g.getSize() == 5);
    REQUIRE(g.getAdjacency()[2].back()==4);
    REQUIRE(g.getAdjacency()[4].back()==2);
}
TEST_CASE("Adding edge - new verticles"){
    std::vector<std::pair<size_t,size_t>> edges = {{0,1},{0,2},{0,3},{1,2},{2,3},{1,3}};
    Graph g(4, edges);
    std::pair<size_t,size_t> edge = {5,4};
    g.addEdge(edge);
    REQUIRE(g.getSize() == 6);
    REQUIRE(g.getAdjacency()[5].back()==4);
    REQUIRE(g.getAdjacency()[4].back()==5);
}
TEST_CASE("Adding edge - more than 2 new verticles"){
    std::vector<std::pair<size_t,size_t>> edges = {{0,1},{0,2},{0,3},{1,2},{2,3},{1,3}};
    Graph g(4, edges);
    std::pair<size_t,size_t> edge = {6,5};
    std::vector<size_t> empty = {};
    g.addEdge(edge);
    REQUIRE(g.getSize() == 7);
    REQUIRE(g.getAdjacency()[6].back()==5);
    REQUIRE(g.getAdjacency()[5].back()==6);
    REQUIRE(g.getAdjacency()[4]==empty);
}
TEST_CASE("Removing vertex"){
    std::vector<std::pair<size_t,size_t>> edges = {{0,1},{0,2},{0,3},{1,2},{2,3},{1,3}};
    Graph g(4, edges);
    std::vector<size_t> adj0 = {1,2};
    std::vector<size_t> adj1 = {0,2};
    std::vector<size_t> adj2 = {1,0};
    std::vector<std::pair<size_t,size_t>> newEdges = {{0,1},{1,2},{0,2}};
    g.pop(0);
    REQUIRE(g.getSize() == 3);
    REQUIRE(g.getAdjacency()[0]==adj0);
    REQUIRE(g.getAdjacency()[1]==adj1);
    REQUIRE(g.getAdjacency()[2]==adj2);
    REQUIRE(g.getEdges()==newEdges);
}
