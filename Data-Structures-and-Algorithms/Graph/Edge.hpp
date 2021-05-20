//
//  Edge.hpp
//  Graph
//
//  Created by YzFENG on 2021/5/18.
//

#ifndef Edge_hpp
#define Edge_hpp

#include <stdio.h>
#include <vector>

class Edge {
private:
    int _nodeIndex;
    int _length;
public:
    Edge(int nodeIndex, int length);
    void printEdge();
    void setNodeIndex(int nodeIndex);
    void setLength(int length);
    int getNodeIndex();
    int getLength();
};


#endif /* Edge_hpp */
