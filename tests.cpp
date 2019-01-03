//
// Created by kejbi on 31.12.18.
//

#define CATCH_CONFIG_MAIN

#include "Graph.h"
#include "catch.h"

TEST_CASE("Graph Constructor"){
    std::vector<std::pair<int,int>> edges = {{1, 2}, {0, 2}};
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
//TEST_CASE("DFS"){
//    std::vector<std::pair<int,int>> edges = {{1, 2}, {0, 2}};
//    Graph g(3, edges);
//    bool visited[3] = {false};
//    g.dfs(0,g.getAdjacency(),visited);
//    REQUIRE(visited[0] == true);
//    REQUIRE(visited[1] == true);
//    REQUIRE(visited[2] == true);
//}
TEST_CASE("Extensive Bridges, empty graph"){
    std::vector<std::pair<int,int>> edges = {};
    Graph g(0, edges);
    auto bridges = g.getExtensiveBridges();
    REQUIRE(bridges == edges);
}
TEST_CASE("Extensive Bridges, not empty graph"){
    std::vector<std::pair<int,int>> edges = {{0,1},{0,2},{0,3},{1,2},{2,3}};
    Graph g(4, edges);
    auto foundBridges = g.getExtensiveBridges();
    std::vector<std::pair<int,int>> requiredBridges = {{0,2}};
    REQUIRE(foundBridges == requiredBridges);
}
TEST_CASE("Extensive Bridges, not empty graph, no bridges"){
    std::vector<std::pair<int,int>> edges = {{0,1},{0,2},{0,3},{1,2},{2,3},{1,3}};
    Graph g(4, edges);
    auto foundBridges = g.getExtensiveBridges();
    std::vector<std::pair<int,int>> requiredBridges = {};
    REQUIRE(foundBridges == requiredBridges);
}