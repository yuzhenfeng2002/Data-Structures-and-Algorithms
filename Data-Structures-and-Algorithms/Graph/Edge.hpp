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
protected:
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

class DFSEdge : public Edge {
protected:
    int firstTime;
    int lastTime;
public:
    DFSEdge(int nodeIndex, int length);
    void setFirstTime(int firstT);
    void setLastTime(int lastT);
};

#endif /* Edge_hpp */
