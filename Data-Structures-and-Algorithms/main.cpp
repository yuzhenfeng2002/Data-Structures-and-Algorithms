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

int main(int argc, const char * argv[]) {
    // insert code here...
    Graph graph = Graph(5);
    
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 8);
    graph.addEdge(0, 4, -4);
    graph.addEdge(1, 3, 1);
    graph.addEdge(1, 4, 7);
    graph.addEdge(2, 1, 4);
    graph.addEdge(3, 0, 2);
    graph.addEdge(3, 2, -5);
    graph.addEdge(4, 3, 6);
    
    graph.printGraph();
    
    try {
        graph.printShortestPath(0, 1, "BellmanFord");
    } catch (const char* msg) {
        std::cout << msg << std::endl;
    }
    try {
        graph.printShortestPath(0, 1, "FloydWarshall");
    } catch (const char* msg) {
        std::cout << msg << std::endl;
    }
    return 0;
}
