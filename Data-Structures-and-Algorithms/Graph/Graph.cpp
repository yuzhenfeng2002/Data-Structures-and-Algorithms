//
//  Graph.cpp
//  Graph
//
//  Created by YzFENG on 2021/5/18.
//

#include "Graph.hpp"

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

pair<list<int>, list<int>> Graph::DFS()
{
    list<int> firstTimeList = list<int>();
    list<int> lastTimeList = list<int>();
    vector<DFSEdge> nodeVec = vector<DFSEdge>(graph.size(), DFSEdge(null, inf));
    unsigned int time = 0;
    for (int i = 0; i < graph.size(); i++) {
        if (nodeVec.at(i).getNodeIndex() == null) {
            DFSVisit(i, time, nodeVec, firstTimeList, lastTimeList);
        }
    }
    return pair<list<int>, list<int>>{firstTimeList, lastTimeList};
}

void Graph::DFSVisit(int sourceNode, int time,
                     vector<DFSEdge> &nodeVec,
                     list<int> &firstTimeList,
                     list<int> &lastTimeList)
{
    nodeVec.at(sourceNode).setNodeIndex(visited);
    time ++;
    nodeVec.at(sourceNode).setFirstTime(time);
    firstTimeList.push_front(sourceNode);
    for (int i = 0; i < graph.at(sourceNode).size(); i++) {
        auto v = graph.at(sourceNode).at(i).getNodeIndex();
        if (nodeVec.at(v).getNodeIndex() == null) {
            DFSVisit(v, time, nodeVec, firstTimeList, lastTimeList);
        }
    }
    nodeVec.at(sourceNode).setNodeIndex(discovered);
    time ++;
    nodeVec.at(sourceNode).setLastTime(time);
    lastTimeList.push_front(sourceNode);
}

list<int> Graph::topoSort()
{
    auto DFSResult = DFS();
    list<int> result = list<int>(DFSResult.second);
    int size = int(result.size());
    // print
    printf("Print the topological order:\n");
    for (int i = 0; i < size; i++) {
        printf("%d -> ", result.front());
        result.pop_front();
    }
    printf("(end)\n");
    return result;
}

Graph Graph::transpose()
{
    Graph transposeGraph = Graph(int(graph.size()));
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph.at(i).size(); j++) {
            transposeGraph.addEdge(graph.at(i).at(j).getNodeIndex(), i);
        }
    }
    return transposeGraph;
}

vector<vector<int>> Graph::findSCCs()
{
    vector<vector<int>> SCCs = vector<vector<int>>();
    auto DFSResult = DFS();
    list<int> lastTimeListTG = list<int>(DFSResult.second);
    Graph transposeG = transpose();
    
    vector<Edge> nodeVec = vector<Edge>(graph.size(), Edge(null, inf));
    for (int i = 0; i < graph.size(); i++) {
        int index = lastTimeListTG.front();
        lastTimeListTG.pop_front();
        
        if (nodeVec.at(index).getNodeIndex() == null) {
            vector<int> SCC = vector<int>();
            stack<int> nodeStack = stack<int>();
            nodeStack.push(index);
            nodeVec.at(index).setNodeIndex(visited);
            while (!nodeStack.empty()) {
                auto u = nodeStack.top();
                SCC.push_back(u);
                nodeStack.pop();
                for (int j = 0; j < transposeG.graph.at(u).size(); j++) {
                    int v = transposeG.graph.at(u).at(j).getNodeIndex();
                    if (nodeVec.at(v).getNodeIndex() == null) {
                        nodeStack.push(v);
                        nodeVec.at(v).setNodeIndex(visited);
                    }
                }
            }
            SCCs.push_back(SCC);
        }
    }
    
    // print
    printf("Print the SCCs:\n");
    for (int i = 0; i < SCCs.size(); i++) {
        printf("SCC %d: ", i+1);
        for (int j = 0; j < SCCs.at(i).size(); j++) {
            printf("%d ", SCCs.at(i).at(j));
        }
        printf("\n");
    }
    return SCCs;
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
