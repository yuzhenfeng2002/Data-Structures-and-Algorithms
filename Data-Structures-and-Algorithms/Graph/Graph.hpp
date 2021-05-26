//
//  Graph.hpp
//  Graph
//
//  Created by YzFENG on 2021/5/18.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include "Edge.hpp"

using std::queue;
using std::stack;
using std::vector;
using std::list;
using std::pair;

class Graph
{
private:
    const int null = -1;
    const int visited = 0;
    const int discovered = 1;
    const int inf = 65535;
    vector<vector<Edge>> graph;
    vector<Edge> BFS(int sourceNode);
    pair<list<int>, list<int>> DFS();
    void DFSVisit(int sourceNode, int time,
                  vector<DFSEdge> &nodeVec,
                  list<int> &firstTimeList,
                  list<int> &lastTimeList);
    Graph transpose();
    void printPath(int sourceNode, int destNode, vector<Edge> preEdgeVec);
public:
    Graph(int numOfNodes);
    void addEdge(int i, int j, int length=1, bool isDirected=1);
    list<int> topoSort();
    vector<vector<int>> findSCCs();
    void printGraph();
    void printBFSPath(int sourceNode, int destNode);
};


#endif /* Graph_hpp */
