//
//  Graph.cpp
//  Graph
//
//  Created by YzFENG on 2021/5/18.
//

#include "Graph.hpp"
#include <queue>

using std::queue;

Graph::Graph(int numOfNodes)
{
    graph = vector<vector<Edge>>(numOfNodes);
}

void Graph::addEdge(int i, int j, int length, bool isDirected)
{
    graph[i].push_back(Edge(j, length));
    if (!isDirected) {
        graph[j].push_back(Edge(i, length));
    }
}

void Graph::printGraph()
{
    for (int i = 0; i < graph.size(); i++) {
        printf("The %dth node has %lu neighbors: \n", i, graph.at(i).size());
        if (graph.at(i).size() == 0) {
            continue;
        }
        printf("Node\tLength\n");
        for (int j = 0; j < graph.at(i).size(); j++) {
            graph.at(i).at(j).printEdge();
        }
    }
}

vector<Edge> Graph::BFS(int sourceNode)
{
    queue<int> nodeQueue = queue<int>();
    vector<Edge> preNodeVec = vector<Edge>(graph.size(), Edge(null, inf));
    preNodeVec.at(sourceNode).setLength(0);
    preNodeVec.at(sourceNode).setNodeIndex(null);
    nodeQueue.push(sourceNode);
    while (!nodeQueue.empty()) {
        auto u = nodeQueue.front();
        nodeQueue.pop();
        for (int i = 0; i < graph.at(u).size(); i++) {
            int j = graph.at(u).at(i).getNodeIndex();
            if (preNodeVec.at(j).getNodeIndex() == null) {
                preNodeVec.at(j).setNodeIndex(u);
                preNodeVec.at(j).setLength(graph.at(u).at(i).getLength() +
                                           preNodeVec.at(u).getLength());
                nodeQueue.push(j);
            }
        }
    }
    return preNodeVec;
}

void Graph::printPath(int sourceNode, int destNode, vector<Edge> preNodeVec)
{
    if (sourceNode == destNode) {
        printf("%d -> ", sourceNode);
        return;
    }
    else if (preNodeVec.at(destNode).getNodeIndex() == null)
    {
        throw "No Path!";
    }
    else
    {
        printPath(sourceNode, preNodeVec.at(destNode).getNodeIndex(), preNodeVec);
        printf("%d -> ", destNode);
        return;
    }
}

void Graph::printBFSPath(int sourceNode, int destNode)
{
    auto preNodeVec = BFS(sourceNode);
    printf("The distance between the source and destination is %d.\n",
           preNodeVec.at(destNode).getLength());
    printf("The path is:\n");
    printPath(sourceNode, destNode, preNodeVec);
    printf("(end)\n");
}
