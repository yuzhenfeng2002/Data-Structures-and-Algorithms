//
//  Edge.cpp
//  Graph
//
//  Created by YzFENG on 2021/5/18.
//

#include "Edge.hpp"

Edge::Edge(int nodeIndex, int length)
{
    _nodeIndex = nodeIndex;
    _length = length;
}

void Edge::printEdge()
{
    printf("%d\t\t%d\n", _nodeIndex, _length);
}

void Edge::setNodeIndex(int nodeIndex)
{
    _nodeIndex = nodeIndex;
}
void Edge::setLength(int length)
{
    _length = length;
}
int Edge::getNodeIndex()
{
    return _nodeIndex;
}
int Edge::getLength()
{
    return _length;
}
