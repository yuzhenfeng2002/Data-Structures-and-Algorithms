//
//  generateSpanningTree.cpp
//  Data-Structures-and-Algorithms
//
//  Created by YzFENG on 2021/6/1.
//

#include "Graph.hpp"

vector<pair<int, int>> Graph::krustkalSpanningTree()
{
    vector<pair<int, int>> result = vector<pair<int, int>>();
    vector<vector<int>> edgesOfSet = vector<vector<int>>(graph.size());
    vector<int> setOfAnEdge = vector<int>();
    int costSum = 0;
    // initialization
    for (int i = 0; i < graph.size(); i++) {
        setOfAnEdge.push_back(i);
        edgesOfSet.at(i).push_back(i);
    }
    vector<tuple<int, int, int>> edges = sortEdgesByWeight();
    
    for (int i = 0; i < edges.size(); i++) {
        int u = std::get<0>(edges.at(i));
        int v = std::get<1>(edges.at(i));
        int setIndex1 = setOfAnEdge.at(u);
        int setIndex2 = setOfAnEdge.at(v);
        
        if (setIndex1 != setIndex2) {
            costSum += std::get<2>(edges.at(i));
            result.push_back(pair<int, int>{u, v});
            // union the two sets
            for (int j = 0; j < edgesOfSet.at(setIndex1).size(); j++) {
                int edgeIndex = edgesOfSet.at(setIndex1).at(j);
                setOfAnEdge.at(edgeIndex) = setIndex2;
                edgesOfSet.at(setIndex2).push_back(edgeIndex);
            }
            edgesOfSet.at(setIndex1).clear();
        }
    }
    
    printf("The sum of cost is: %d\n", costSum);
    for (int i = 0; i < result.size(); i++) {
        printf("<%d, %d>\t", result.at(i).first, result.at(i).second);
    }
    printf("\n");
    
    return result;
}

vector<pair<int, int>> Graph::primSpanningTree(int seed)
{
    vector<tuple<int, int, bool>> nodeVec = vector<tuple<int, int, bool>>(graph.size(), tuple<int, int, bool>(inf, null, true)); // tuple<key, π, isInQ>
    int costSum = 0;
    
    // initialize the nodeVec and the priority queue
    nodeVec.at(seed) = std::make_tuple(0, null, true);
    auto cmp = [=] (tuple<int, int> a, tuple<int, int> b) -> bool {
        return std::get<1>(a) > std::get<1>(b);
    }; // the lambda function to compare tuple<nodeIndex, key> by key
    priority_queue<tuple<int, int>, vector<tuple<int, int>>, decltype(cmp)> nodeQ(cmp); // tuple<nodeIndex, key>
    nodeQ.push(std::make_tuple(seed, std::get<0>(nodeVec.at(seed))));
    while (!nodeQ.empty()) {
        tuple<int, int> node = nodeQ.top();
        nodeQ.pop();
        int u = std::get<0>(node);
        // if u should not be in Q, just pass
        if (std::get<2>(nodeVec.at(u)) == false) {
            continue;
        }
        std::get<2>(nodeVec.at(u)) = false; // set isInQ false because the node has been included in the tree
        costSum += std::get<1>(node);
        
        for (int j = 0; j < graph.at(u).size(); j++) {
            int v = graph.at(u).at(j).first;
            int length = graph.at(u).at(j).second;
            if (std::get<2>(nodeVec.at(v)) == true && std::get<0>(nodeVec.at(v)) > length) {
                std::get<1>(nodeVec.at(v)) = u;
                std::get<0>(nodeVec.at(v)) = length;
                nodeQ.push(std::make_tuple(v, length));
            }
        }
    }
    
    vector<pair<int, int>> result = vector<pair<int, int>>();
    
    printf("The sum of cost is: %d\n", costSum);
    for (int i = 0; i < nodeVec.size(); i++) {
        int pi = std::get<1>(nodeVec.at(i));
        if (pi != null) {
            result.push_back(std::make_pair(pi, i));
            printf("<%d, %d>\t", pi, i);
        }
    }
    printf("\n");
    
    return result;
}
