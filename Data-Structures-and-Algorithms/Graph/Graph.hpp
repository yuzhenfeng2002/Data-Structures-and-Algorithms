//
//  Graph.hpp
//  Data-Structures-and-Algorithms
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
#include <algorithm>
#include "Edge.hpp"

using std::queue;
using std::stack;
using std::vector;
using std::list;
using std::pair;
using std::tuple;
using std::priority_queue;

class Graph
{
private:
    const int null = -1;
    const int visited = 0;
    const int discovered = 1;
    const int inf = 65535;
    vector<vector<pair<int, int>>> graph; // pair<nodeIndex, length>
    vector<tuple<int, int, int>> edges; // tuple<u, v, length>
    // if it is a directed graph, u means O, v means D
    // else u and v have no difference
    
    vector<tuple<int, int, int>> sortEdgesByWeight();
    Graph transpose(); // return a transpose graph
    
    vector<pair<int, int>> BFS(int sourceNode); // return the vector of pair<prenode, distance from sourceNode>
    pair<list<int>, list<int>> DFS();
    
    void DFSVisit(int sourceNode, int time,
                  vector<DFSEdge> &nodeVec,
                  list<int> &firstTimeList,
                  list<int> &lastTimeList);
    bool isAcyclic();
    void printPath(int sourceNode, int destNode, vector<pair<int, int>> preEdgeVec);
public:
    Graph(int numOfNodes);
    void addEdge(int i, int j, int length=1, bool isDirected=1);
    void printGraph();
    void DFS(int a);
    void printBFSPath(int sourceNode, int destNode);
    list<int> topoSort();
    vector<vector<int>> findSCCs();
    // return the edges pair<u, v> in the spanning tree
    vector<pair<int, int>> krustkalSpanningTree();
    vector<pair<int, int>> primSpanningTree(int seed);
    
    
    
};


#endif /* Graph_hpp */
