//
//  graphSearchFunctions.cpp
//  Data-Structures-and-Algorithms
//
//  Created by YzFENG on 2021/5/18.
//

#include "Graph.hpp"

vector<pair<int, int>> Graph::BFS(int sourceNode)
{
    queue<int> nodeQ = queue<int>();
    vector<pair<int, int>> nodeDistanceVec = vector<pair<int, int>>(graph.size(), std::make_pair(null, inf));
    nodeDistanceVec.at(sourceNode).first = 0;
    nodeDistanceVec.at(sourceNode).second = null;
    nodeQ.push(sourceNode);
    while (!nodeQ.empty()) {
        int u = nodeQ.front();
        nodeQ.pop();
        for (int i = 0; i < graph.at(u).size(); i++) {
            int j = graph.at(u).at(i).first;
            if (nodeDistanceVec.at(j).first == null) {
                nodeDistanceVec.at(j).first = u;
                nodeDistanceVec.at(j).second = graph.at(u).at(i).second + nodeDistanceVec.at(u).second;
                nodeQ.push(j);
            }
        }
    }
    return nodeDistanceVec;
}

void Graph::printBFSPath(int sourceNode, int destNode)
{
    auto nodeDistanceVec = BFS(sourceNode);
    printf("The distance between the source and destination is %d.\n",
           nodeDistanceVec.at(destNode).first);
    printf("The path is:\n");
    printPath(sourceNode, destNode, nodeDistanceVec);
    printf("(end)\n");
}

void Graph::printPath(int sourceNode, int destNode, vector<pair<int, int>> nodeDistanceVec)
{
    if (sourceNode == destNode) {
        printf("%d -> ", sourceNode);
        return;
    }
    else if (nodeDistanceVec.at(destNode).first == null)
    {
        throw "No Path!";
    }
    else
    {
        printPath(sourceNode, nodeDistanceVec.at(destNode).first, nodeDistanceVec);
        printf("%d -> ", destNode);
        return;
    }
}

void Graph::DFS(int a)
{
    unsigned int time = 0;
    stack<int> nodeStack = stack<int>();
    vector<int> nodeVec = vector<int>(graph.size(), null); // null means not visited
    vector<pair<int, int>> nodeTimeStamp = vector<pair<int, int>>(graph.size(), pair<int, int>{0, 0});
    list<int> firstTimeList = list<int>();
    list<int> lastTimeList = list<int>();
    bool isAcyclic = true;
    for (int i = 0; i < graph.size(); i++) {
        if (nodeVec.at(i) == null) {
            stack<int> nodeStack = stack<int>();
            nodeStack.push(i);
            firstTimeList.push_front(i);
            nodeTimeStamp.at(i).first = time ++;
            nodeVec.at(i) = visited;
            while (!nodeStack.empty()) {
                auto u = nodeStack.top();
                if (nodeVec.at(u) == discovered) {
                    lastTimeList.push_front(u);
                    nodeTimeStamp.at(u).second = time ++;
                    nodeStack.pop();
                }
                for (int j = 0; j < graph.at(u).size(); j++) {
                    int v = graph.at(u).at(j).first;
                    if (nodeVec.at(v) == null) {
                        nodeStack.push(v);
                        firstTimeList.push_front(v);
                        nodeTimeStamp.at(v).first = time ++;
                        nodeVec.at(v) = visited;
                    }
                    else
                        isAcyclic = false;
                }
                nodeVec.at(u) = discovered;
            }
        }
    }
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
        auto v = graph.at(sourceNode).at(i).first;
        if (nodeVec.at(v).getNodeIndex() == null) {
            DFSVisit(v, time, nodeVec, firstTimeList, lastTimeList);
        }
    }
    nodeVec.at(sourceNode).setNodeIndex(discovered);
    time ++;
    nodeVec.at(sourceNode).setLastTime(time);
    lastTimeList.push_front(sourceNode);
}

bool Graph::isAcyclic()
{
    vector<Edge> nodeVec = vector<Edge>(graph.size(), Edge(null, inf));
    for (int i = 0; i < graph.size(); i++) {
        if (nodeVec.at(i).getNodeIndex() == null) {
            stack<int> nodeStack = stack<int>();
            nodeStack.push(i);
            nodeVec.at(i).setNodeIndex(visited);
            while (!nodeStack.empty()) {
                auto u = nodeStack.top();
                nodeStack.pop();
                for (int j = 0; j < graph.at(u).size(); j++) {
                    int v = graph.at(u).at(j).first;
                    if (nodeVec.at(v).getNodeIndex() == null) {
                        nodeStack.push(v);
                        nodeVec.at(v).setNodeIndex(visited);
                    }
                    else
                        return false;
                }
            }
        }
    }
    return true;
}

list<int> Graph::topoSort()
{
    if (!isAcyclic()) {
        throw "Not Acyclic.";
    }
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
                    int v = transposeG.graph.at(u).at(j).first;
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




