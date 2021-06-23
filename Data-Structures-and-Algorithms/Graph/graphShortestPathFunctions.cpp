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
        nodeDistanceVec = DAGShortestPath(sourceNode);
    }
    else if (mode == "Dijkstra")
    {
        nodeDistanceVec = DijkstraShortestPath(sourceNode);
    }
    else if (mode == "BellmanFord")
    {
        nodeDistanceVec = BellmanFordShortestPath(sourceNode);
    }
    else if (mode == "FloydWarshall")
    {
        auto result = FloydWarshallShortestPath();
        for (int i = 0; i < graph.size(); i++) {
            nodeDistanceVec.push_back(std::make_pair(result.second.at(sourceNode).at(i),
                                                     result.first.at(sourceNode).at(i)));
        }
    }
    
    printf("The distance between the source and destination is %d.\n",
           nodeDistanceVec.at(destNode).second);
    printf("The path is:\n");
    printPath(sourceNode, destNode, nodeDistanceVec);
    printf("(end)\n");
}

vector<pair<int, int>> Graph::shortestPathInitialization(int sourceNode)
{
    auto result = vector<pair<int, int>>(graph.size(), std::make_pair(null, inf));
    result.at(sourceNode).second = 0;
    return result;
}

bool Graph::relax(int u, vector<pair<int, int>> &nodeVec)
{
    bool isRelaxed = true;
    for (int i = 0; i < graph.at(u).size(); i++) {
        int v = graph.at(u).at(i).first;
        if (nodeVec.at(u).second + graph.at(u).at(i).second < nodeVec.at(v).second) {
            nodeVec.at(v).second = nodeVec.at(u).second + graph.at(u).at(i).second;
            nodeVec.at(v).first = u;
            isRelaxed = false;
        }
    }
    return isRelaxed;
}

vector<pair<int, int>> Graph::DAGShortestPath(int s)
{
    auto result = shortestPathInitialization(s);
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

vector<pair<int, int>> Graph::BellmanFordShortestPath(int s)
{
    auto result = shortestPathInitialization(s);
    int i = 0;
    for (i = 0; i < graph.size(); i++) {
        bool isRelaxed = true;
        for (int u = 0; u < graph.size(); u++) {
            isRelaxed = relax(u, result) && isRelaxed;
        }
        if (isRelaxed) {
            break;
        }
    }
    if (i == graph.size()) {
        throw "Cannot find a shortest path!";
    }
    return result;
}

pair<vector<vector<int>>, vector<vector<int>>> Graph::FloydWarshallShortestPath()
{
    // initialize
    auto distance = vector<vector<int>>(int(graph.size()),
                                        vector<int>(int(graph.size()), inf));
    auto pi = vector<vector<int>>(int(graph.size()),
                                        vector<int>(int(graph.size()), inf));
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph.at(i).size(); j++) {
            auto edge = graph.at(i).at(j);
            distance.at(i).at(edge.first) = edge.second;
            pi.at(i).at(edge.first) = i;
        }
        distance.at(i).at(i) = 0;
        pi.at(i).at(i) = i;
    }
    
    // iterate
    for (int k = 0; k < graph.size(); k++) {
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph.size(); j++) {
                if (distance.at(i).at(j) >
                    distance.at(i).at(k) + distance.at(k).at(j)) {
                    distance.at(i).at(j) = distance.at(i).at(k) + distance.at(k).at(j);
                    pi.at(i).at(j) = pi.at(k).at(j);
                }
            }
        }
    }
    
    return std::make_pair(distance, pi);
}
