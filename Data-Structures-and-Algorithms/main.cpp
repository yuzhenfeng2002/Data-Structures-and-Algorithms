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
    Graph graph = Graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 0);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
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
    
    return 0;
}
