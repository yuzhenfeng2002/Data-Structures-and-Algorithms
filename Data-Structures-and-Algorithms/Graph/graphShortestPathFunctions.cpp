//
//  graphShortestPathFunctions.cpp
//  Data-Structures-and-Algorithms
//
//  Created by YzFENG on 2021/6/6.
//

#include <stdio.h>
#include "Graph.hpp"


void Graph::printShortestPath(int sourceNode, int destNode, string mode)
{
    vector<pair<int, int>> nodeDistanceVec;
    if (mode == "BFS") {
        nodeDistanceVec = BFS(sourceNode);
    }
    else if (mode == "DAG")
    {
        nodeDistanceVec = DAGShortestPath();
    }
    else if (mode == "Dijkstra")
    {
        nodeDistanceVec = DijkstraShortestPath(sourceNode);
    }
    
    printf("The distance between the source and destination is %d.\n",
           nodeDistanceVec.at(destNode).second);
    printf("The path is:\n");
    printPath(sourceNode, destNode, nodeDistanceVec);
    printf("(end)\n");
}

vector<pair<int, int>> Graph::shortestPathInitialization()
{
    return vector<pair<int, int>>(graph.size(), std::make_pair(null, inf));
}

void Graph::relax(int u, vector<pair<int, int>> &nodeVec)
{
    for (int v = 0; v < graph.at(u).size(); v++) {
        if (nodeVec.at(u).second + graph.at(u).at(v).second < nodeVec.at(v).second) {
            nodeVec.at(v).second = nodeVec.at(u).second + graph.at(u).at(v).second;
            nodeVec.at(v).first = u;
        }
    }
}

vector<pair<int, int>> Graph::DAGShortestPath()
{
    auto result = shortestPathInitialization();
    list<int> topoSortResult;
    try {
        topoSortResult = topoSort();
    } catch (const char* msg) {
        throw "Not a DAG!";
    }
    for (int i = 0; i < graph.size(); i++) {
        int u = topoSortResult.front();
        topoSortResult.pop_front();
        relax(u, result);
    }
    return result;
}

vector<pair<int, int>> Graph::DijkstraShortestPath(int s)
{
    // copied from Prim's minimum spanning tree algorithm
    vector<tuple<int, int, bool>> nodeVec = vector<tuple<int, int, bool>>(graph.size(), tuple<int, int, bool>(inf, null, true)); // tuple<key, π, isInQ>
    
    // initialize the nodeVec and the priority queue
    nodeVec.at(s) = std::make_tuple(0, null, true);
    auto cmp = [=] (tuple<int, int> a, tuple<int, int> b) -> bool {
        return std::get<1>(a) > std::get<1>(b);
    }; // the lambda function to compare tuple<nodeIndex, key> by key
    priority_queue<tuple<int, int>, vector<tuple<int, int>>, decltype(cmp)> nodeQ(cmp); // tuple<nodeIndex, key>
    nodeQ.push(std::make_tuple(s, 0));
    while (!nodeQ.empty()) {
        tuple<int, int> node = nodeQ.top();
        nodeQ.pop();
        int u = std::get<0>(node);
        // if u should not be in Q, just pass
        if (std::get<2>(nodeVec.at(u)) == false) {
            continue;
        }
        std::get<2>(nodeVec.at(u)) = false; // set isInQ false because the node has been included in the tree
        
        for (int j = 0; j < graph.at(u).size(); j++) {
            int v = graph.at(u).at(j).first;
            int length = graph.at(u).at(j).second;

            if (std::get<0>(nodeVec.at(u)) + length < std::get<0>(nodeVec.at(v))) {
                std::get<0>(nodeVec.at(v)) = std::get<0>(nodeVec.at(u)) + length;
                std::get<1>(nodeVec.at(v)) = u;
                nodeQ.push(std::make_tuple(v, std::get<0>(nodeVec.at(v))));
            }
        }
    }
    
    vector<pair<int, int>> result = vector<pair<int, int>>();
    for (int i = 0; i < nodeVec.size(); i++) {
        result.push_back(std::make_pair(std::get<1>(nodeVec.at(i)), std::get<0>(nodeVec.at(i))));
    }
    return result;
}
