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
    REQUIRE(g.getVertices() == 5);
    REQUIRE(g.getAdjacency()[4]==empty);
}