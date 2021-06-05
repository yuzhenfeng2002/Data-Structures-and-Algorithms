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
    Graph graph = Graph(6);
    
    graph.addEdge(0, 1, 1, 0);
    graph.addEdge(0, 3, 1, 0);
    graph.addEdge(1, 4, 1, 0);

    graph.addEdge(4, 3, 1, 0);
    graph.addEdge(2, 5, 1, 0);
    graph.addEdge(2, 4, 1, 0);
    
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
    auto SCCs = graph.findSCCs();
    
    auto krustkalTree = graph.krustkalSpanningTree();
    auto primTree = graph.primSpanningTree(0);
    return 0;
}
