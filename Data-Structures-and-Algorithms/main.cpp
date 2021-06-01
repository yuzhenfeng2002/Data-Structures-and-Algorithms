//
//  main.cpp
//  Graph
//
//  Created by YzFENG on 2021/5/18.
//

#include <iostream>
#include <cstdlib>
#include "Graph.hpp"
#include "Tree.hpp"

using std::cout;

const int N = 15;
const int MAX = 20;
const int MIN = 0;

int main(int argc, const char * argv[]) {
    // insert code here...
    Graph graph = Graph(9);
    
    graph.addEdge(0, 1, 4, 0);
    graph.addEdge(0, 7, 8, 0);
    graph.addEdge(1, 7, 11, 0);
    graph.addEdge(1, 2, 8, 0);
    graph.addEdge(2, 8, 2, 0);
    graph.addEdge(2, 3, 7, 0);
    graph.addEdge(2, 5, 4, 0);
    graph.addEdge(3, 4, 9, 0);
    graph.addEdge(3, 5, 14, 0);
    graph.addEdge(4, 5, 10, 0);
    graph.addEdge(5, 6, 2, 0);
    graph.addEdge(6, 7, 1, 0);
    graph.addEdge(6, 8, 6, 0);
    graph.addEdge(7, 8, 7, 0);
    
    graph.printGraph();
    
    try {
        graph.printBFSPath(0, 4);
    } catch (const char* msg) {
        std::cout << msg << std::endl;
    }
    
    try {
        graph.topoSort();
    } catch (const char* msg) {
        std::cout << msg << std::endl;
    }
    graph.DFS(0);
    auto SCCs = graph.findSCCs();
    auto krustkalTree = graph.krustkalSpanningTree();
    auto primTree = graph.primSpanningTree(0);
    return 0;
}
