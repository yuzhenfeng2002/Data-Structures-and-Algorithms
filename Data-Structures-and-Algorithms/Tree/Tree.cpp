//
//  Tree.cpp
//  Data-Structures-and-Algorithms
//
//  Created by YzFENG on 2021/5/6.
//

#include "Tree.hpp"
#include <queue>

using std::queue;

Tree::Tree()
{
    root = NULL;
}

void Tree::insert(node* z)
{
    node* y = NULL;
    node* x = root;
    while (x != NULL) {
        y = x;
        if (z -> value < x -> value) {
            x = x -> left;
        }
        else
        {
            x = x -> right;
        }
    }
    if (y == NULL) {
        root = z;
    }
    else
    {
        z -> parent = y;
        if (z -> value < y -> value) {
            y -> left = z;
        }
        else
        {
            y -> right = z;
        }
    }
    size ++;
}

void Tree::insert(int value)
{
    node* newNode = new node;
    newNode -> value = value;
    newNode -> parent = newNode -> left = newNode -> right = NULL;
    insert(newNode);
}

void Tree::treeWalk(std::string mode)
{
    int walkNum = 0;
    if (mode == "in") {
        printf("---------------------\n");
        printf("Inorder walk the tree\n");
        inorderWalk(root, walkNum);
    }
    else if (mode == "pre")
    {
        printf("----------------------\n");
        printf("Preorder walk the tree\n");
        preorderWalk(root, walkNum);
    }
    else if (mode == "post")
    {
        printf("-----------------------\n");
        printf("Postorder walk the tree\n");
        postorderWalk(root, walkNum);
    }
    else if (mode == "level")
    {
        printf("------------------------\n");
        printf("Levelorder walk the tree\n");
        auto depth = levelWalk(root, walkNum);
        printf("The min depth: %d, the max depth: %d\n", depth.first, depth.second);
    }
}

void Tree::inorderWalk(node* x, int &walkNum)
{
    if (x) {
        inorderWalk(x -> left, walkNum);
        walkNum ++;
        printf("The %dth node: %d\n", walkNum, x -> value);
        inorderWalk(x -> right, walkNum);
    }
}

void Tree::preorderWalk(node* x, int &walkNum)
{
    if (x) {
        walkNum ++;
        printf("The %dth node: %d\n", walkNum, x -> value);
        preorderWalk(x -> left, walkNum);
        preorderWalk(x -> right, walkNum);
    }
}

void Tree::postorderWalk(node* x, int &walkNum)
{
    if (x) {
        postorderWalk(x -> left, walkNum);
        postorderWalk(x -> right, walkNum);
        walkNum ++;
        printf("The %dth node: %d\n", walkNum, x -> value);
    }
}

pair<int, int> Tree::levelWalk(node* x, int &walkNum)
{
    const int null = -1;
    queue<node*> nodeQueue = queue<node*>();
    int levelNum = 0;
    pair<int, int> result{null, null};
    nodeQueue.push(x);
    while (nodeQueue.size() != 0) {
        printf("****************\n");
        printf("The %dth level: \n", levelNum);
        levelNum ++;
        int levelSize = int(nodeQueue.size());
        for (int i = 0; i < levelSize; i++) {
            auto levelNode = nodeQueue.front();
            nodeQueue.pop();
            walkNum ++;
            printf("The %dth node: %d\n", walkNum, levelNode -> value);
            if (levelNode -> left != NULL) {
                nodeQueue.push(levelNode -> left);
            }
            if (levelNode -> right != NULL) {
                nodeQueue.push(levelNode -> right);
            }
            if (levelNode -> left == NULL &&
                levelNode -> right == NULL &&
                result.first == null) {
                result.first = levelNum;
            }
        }
    }
    result.second = levelNum;
    return result;
}

void Tree::print(node *x, int ident, vector<int> &vecLeft)
{
    if (ident > 0)
    {
        for(int i = 0; i < ident - 1; ++i)
        {
            printf(vecLeft.at(i) ? "│   " : "    ");
        }
        printf(vecLeft.at(ident-1) ? "├── " : "└── ");
    }

    if (!x)
    {
        printf("(null)\n");
        return;
    }

    printf("%d\n", x -> value);
    if(!(x -> left) && !(x -> right))
    {
        return;
    }

    vecLeft.at(ident) = 1;
    print(x -> left, ident + 1, vecLeft);
    vecLeft.at(ident) = 0;
    print(x -> right, ident + 1, vecLeft);
}

void Tree::printTree()
{
    vector<int> vecLeft = vector<int>(size, 0);
    print(root, 0, vecLeft);
}

Tree::node* Tree::search(int key)
{
    node* toBeReturned = root;
    while (toBeReturned != NULL && toBeReturned -> value != key) {
        if (key < toBeReturned -> value) {
            toBeReturned = toBeReturned -> left;
        }
        else
        {
            toBeReturned = toBeReturned -> right;
        }
    }
    if (toBeReturned == NULL) {
        throw "Not Found.";
    }
    else
    {
        return toBeReturned;
    }
}

Tree::node* Tree::minNode(node* x)
{
    node* toBeReturned = x;
    while (toBeReturned -> left) {
        toBeReturned = toBeReturned -> left;
    }
    return toBeReturned;
}

Tree::node* Tree::maxNode(node* x)
{
    node* toBeReturned = x;
    while (toBeReturned -> right) {
        toBeReturned = toBeReturned -> right;
    }
    return toBeReturned;
}

Tree::node* Tree::findExtremeNode(std::string mode)
{
    if (mode == "min") {
        return minNode(root);
    }
    else if (mode == "max")
    {
        return maxNode(root);
    }
    else
    {
        throw "Mode string WRONGly input.";
    }
}

Tree::node* Tree::successor(node* x)
{
    if (x -> right != NULL) {
        return minNode(x);
    }
    auto y = x -> parent;
    while (y != NULL && x == y -> right) {
        x = y;
        y = y -> parent;
    }
    return y;
}

Tree::node* Tree::predecessor(node* x)
{
    if (x -> left != NULL) {
        return maxNode(x);
    }
    auto y = x -> parent;
    while (y != NULL && x == y -> left) {
        x = y;
        y = y -> parent;
    }
    return y;
}

void Tree::transplant(node* u, node* v)
{
    if (u -> parent == NULL) {
        root = v;
    }
    else if (u == u -> parent -> left)
    {
        u -> parent -> left = v;
    }
    else
    {
        u -> parent -> right = v;
    }
    if (v != NULL) {
        v -> parent = u -> parent;
    }
}

void Tree::deleteNode(node *z)
{
    if (z -> left == NULL) {
        transplant(z, z -> right);
    }
    else if (z -> right == NULL)
    {
        transplant(z, z -> left);
    }
    else
    {
        auto y = minNode(z -> right);
        if (y -> parent != z) {
            transplant(y, y -> right);
            y -> right = z -> right;
            y -> right -> parent = y;
        }
        transplant(z, y);
        y -> left = z -> left;
        y -> left -> parent = y;
    }
    delete z;
}

void Tree::deleteSubtree(node* subtreeRoot)
{
    if (subtreeRoot == NULL)
        return;
    deleteSubtree(subtreeRoot -> left);
    deleteSubtree(subtreeRoot -> right);
    if (subtreeRoot -> parent == NULL) {
        root = NULL;
    }
    if (subtreeRoot -> parent -> left == subtreeRoot) {
        subtreeRoot -> parent -> left = NULL;
    }
    else
    {
        subtreeRoot -> parent -> right = NULL;
    }
    delete subtreeRoot;
}
