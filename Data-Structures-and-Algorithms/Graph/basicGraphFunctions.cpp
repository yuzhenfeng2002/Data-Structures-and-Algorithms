//
//  basicGraphFunctions.cpp
//  Data-Structures-and-Algorithms
//
//  Created by YzFENG on 2021/6/1.
//

#include "Graph.hpp"

Graph::Graph(int numOfNodes)
{
    graph = vector<vector<pair<int, int>>>(numOfNodes);
    edges = vector<tuple<int, int, int>>();
}

void Graph::addEdge(int i, int j, int length, bool isDirected)
{
    graph[i].push_back(std::make_pair(j, length));
    if (!isDirected) {
        graph[j].push_back(std::make_pair(i, length));
    }
    edges.push_back(tuple<int, int, int>{i, j, length});
}

vector<tuple<int, int, int>> Graph::sortEdgesByWeight()
{
    vector<tuple<int, int, int>> result = vector<tuple<int, int, int>>(edges);
    sort(result.begin(), result.end(), [=](tuple<int, int, int> a, tuple<int, int, int> b) -> bool {
        return std::get<2>(a) < std::get<2>(b);
    });
    return result;
}

Graph Graph::transpose()
{
    Graph graphTranspose = Graph(int(graph.size()));
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph.at(i).size(); j++) {
            graphTranspose.addEdge(graph.at(i).at(j).first, i);
        }
    }
    return graphTranspose;
}

void Graph::printGraph()
{
    for (int i = 0; i < graph.size(); i++) {
        printf("Node %d: ", i);
        if (graph.at(i).size() == 0) {
            printf("no neighbour.\n");
            continue;
        }
        for (int j = 0; j < graph.at(i).size(); j++) {
            printf("%d(%d) ", graph.at(i).at(j).first, graph.at(i).at(j).second);
        }
        printf("\n");
    }
}
