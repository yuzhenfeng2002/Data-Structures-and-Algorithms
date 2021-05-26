//
//  Tree.hpp
//  Data-Structures-and-Algorithms
//
//  Created by YzFENG on 2021/5/6.
//

#ifndef Tree_hpp
#define Tree_hpp

#include <stdio.h>
#include <vector>
#include <string>

using std::vector;
using std::pair;

class Tree
{
public:
    struct node
    {
        node* parent;
        int value;
        node* left;
        node* right;
    };
private:
    node* root;
    int size = 0;
    void insert(node* z);
    void inorderWalk(node* x, int &walkNum);
    void preorderWalk(node* x, int &walkNum);
    void postorderWalk(node* x, int &walkNum);
    pair<int, int> levelWalk(node* x, int &walkNum);
    void print(node* x, int ident, vector<int> &vec_left);
    node* minNode(node* x);
    node* maxNode(node* x);
    node* successor(node* x);
    node* predecessor(node* x);
    void transplant(node* u, node* v);
    void deleteSubtree(node* root);
public:
    Tree();
    void insert(int value);
    void treeWalk(std::string mode);
    void printTree();
    node* search(int key);
    node* findExtremeNode(std::string mode);
    void deleteNode(node* z);
};

#endif /* Tree_hpp */


//Test case:
//Tree tree = Tree();
//for (int i = 0; i < N; i++) {
//    int randNum = rand() % (MAX - MIN + 1) + MIN;
//    cout << "Insert: " << randNum << '\n';
//    tree.insert(randNum);
//}
//tree.treeWalk("in");
//tree.treeWalk("pre");
//tree.treeWalk("post");
//tree.treeWalk("level");
//tree.printTree();
//cout << "The minimum element is: " << tree.findExtremeNode("min") -> value << '\n';
//cout << "The maximum element is: " << tree.findExtremeNode("max") -> value << '\n';
//int randNum = rand() % (MAX - MIN + 1) + MIN;
//cout << "To search and delete " << randNum << ", the result is: \n";
