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
    vector<pair<int, int>> nodeDistanceVec = shortestPathInitialization(sourceNode);
    nodeDistanceVec.at(sourceNode).first = null;
    nodeDistanceVec.at(sourceNode).second = 0;
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

tuple<bool, list<int>, list<int>> Graph::DFS()
{
    unsigned int time = 0;
    stack<tuple<int, int, int>> nodeStack = stack<tuple<int, int, int>>();
    vector<int> nodeVec = vector<int>(graph.size(), null); // null means not visited
    vector<pair<int, int>> nodeTimeStamp = vector<pair<int, int>>(graph.size(), pair<int, int>{0, 0});
    list<int> firstTimeList = list<int>();
    list<int> lastTimeList = list<int>();
    bool isAcyclic = true;
    for (int i = 0; i < graph.size(); i++) {
        if (nodeVec.at(i) == null) {
            int step = 1;
            int index = 0;
            int u = i;
            while (true) {
                if (step == 1)
                {
                    nodeVec.at(u) = visited;
                    time ++;
                    nodeTimeStamp.at(u).first = time;
                    firstTimeList.push_front(u);
                    step = 2;
                }
                if (step == 2) {
                    if (graph.at(u).size() == 0) {
                        step = 3;
                    }
                    for (int j = 0; j < graph.at(u).size(); j++) {
                        int v = graph.at(u).at(j).first;
                        if (nodeVec.at(v) == null) {
                            if (j >= index) {
                                nodeStack.push(std::make_tuple(u, 2, j + 1));
                                u = v;
                                step = 1;
                                index = 0;
                                break;
                            }
                        }
                        else if (nodeVec.at(v) == visited)
                        {
                            isAcyclic = false;
                        }
                        step = 3;
                    }
                }
                if (step == 3) {
                    nodeVec.at(u) = explored;
                    time ++;
                    nodeTimeStamp.at(u).second = time;
                    lastTimeList.push_front(u);
                    if (nodeStack.empty()) {
                        break;
                    }
                    else
                    {
                        auto node = nodeStack.top();
                        nodeStack.pop();
                        u = std::get<0>(node);
                        step = std::get<1>(node);
                        index = std::get<2>(node);
                    }
                }
            }
        }
    }
    return std::make_tuple(isAcyclic, firstTimeList, lastTimeList);
}

list<int> Graph::topoSort()
{
    auto DFSResult = DFS();
    auto isAcyclic = std::get<0>(DFSResult);
    auto lastTimeList = std::get<2>(DFSResult);
    
    if (!isAcyclic) {
        throw "Not Acyclic.";
    }
    int size = int(lastTimeList.size());
    auto result = lastTimeList;
    
    // print the topological order
    printf("Print the topological order:\n");
    for (int i = 0; i < size; i++) {
        printf("%d -> ", lastTimeList.front());
        lastTimeList.pop_front();
    }
    printf("(end)\n");
    return result;
}

vector<vector<int>> Graph::findSCCs()
{
    auto DFSResult = DFS();
    auto lastTimeList = std::get<2>(DFSResult);
    vector<vector<int>> SCCs = vector<vector<int>>();
    Graph transposeG = transpose();
    
    vector<int> nodeVec = vector<int>(graph.size(), null);
    for (int i = 0; i < graph.size(); i++) {
        int index = lastTimeList.front();
        lastTimeList.pop_front();
        
        if (nodeVec.at(index) == null) {
            vector<int> SCC = vector<int>();
            stack<int> nodeStack = stack<int>();
            nodeStack.push(index);
            nodeVec.at(index) = visited;
            while (!nodeStack.empty()) {
                auto u = nodeStack.top();
                SCC.push_back(u);
                nodeStack.pop();
                for (int j = 0; j < transposeG.graph.at(u).size(); j++) {
                    int v = transposeG.graph.at(u).at(j).first;
                    if (nodeVec.at(v) == null) {
                        nodeStack.push(v);
                        nodeVec.at(v) = visited;
                    }
                }
            }
            SCCs.push_back(SCC);
        }
    }
    
    // print the SCCs
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
