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
#include <string>
#include <algorithm>

using std::queue;
using std::stack;
using std::vector;
using std::list;
using std::pair;
using std::tuple;
using std::string;
using std::priority_queue;

class Graph
{
private:
    const int null = -1;
    const int visited = -2;
    const int explored = -3;
    const int inf = 65535;
    vector<vector<pair<int, int>>> graph; // pair<nodeIndex, length>
    vector<tuple<int, int, int>> edges; // tuple<u, v, length>
    // if it is a directed graph, u means O, v means D
    // else u and v have no difference
    
    vector<tuple<int, int, int>> sortEdgesByWeight();
    Graph transpose(); // return a transpose graph
    
    vector<pair<int, int>> BFS(int sourceNode); // return the vector of pair<prenode, distance from sourceNode>
    tuple<bool, list<int>, list<int>> DFS(); // return <isAcyclic, firstTimeList, lastTimeList>
    
    vector<pair<int, int>> shortestPathInitialization(int sourceNode);
    bool relax(int u, vector<pair<int, int>> &nodeVec); // judge if all edges connected to u have already been relaxed
    vector<pair<int, int>> DAGShortestPath(int s);
    vector<pair<int, int>> DijkstraShortestPath(int s);
    vector<pair<int, int>> BellmanFordShortestPath(int s);
    pair<vector<vector<int>>, vector<vector<int>>> FloydWarshallShortestPath();

    void printPath(int sourceNode, int destNode, vector<pair<int, int>> preEdgeVec);
public:
    Graph(int numOfNodes);
    void addEdge(int i, int j, int length=1, bool isDirected=1);
    void printGraph();
    
    void printShortestPath(int sourceNode, int destNode, string mode);
    list<int> topoSort(); // return the topological sort
    vector<vector<int>> findSCCs();
    
    // return the edges pair<u, v> in the spanning tree
    vector<pair<int, int>> krustkalSpanningTree();
    vector<pair<int, int>> primSpanningTree(int seed);
};

#endif /* Graph_hpp */
