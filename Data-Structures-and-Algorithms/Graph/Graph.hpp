//
//  Graph.hpp
//  Graph
//
//  Created by YzFENG on 2021/5/18.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <vector>
#include "Edge.hpp"

using std::vector;

class Graph
{
private:
    const int null = -1;
    const int inf = 65535;
    vector<vector<Edge>> graph;
    vector<Edge> BFS(int sourceNode);
    void printPath(int sourceNode, int destNode, vector<Edge> preEdgeVec);
public:
    Graph(int numOfNodes);
    void addEdge(int i, int j, int length=1, bool isDirected=1);
    void printGraph();
    void printBFSPath(int sourceNode, int destNode);
};


#endif /* Graph_hpp */
