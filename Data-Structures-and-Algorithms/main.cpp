//
//  main.cpp
//  Data-Structures-and-Algorithms
//
//  Created by YzFENG on 2021/5/16.
//

#include <iostream>
#include <cstdlib>
#include "Tree.hpp"

using std::cout;

const int N = 15;
const int MAX = 20;
const int MIN = 0;

int main(int argc, const char * argv[]) {
    srand(4);
    Tree tree = Tree();
    for (int i = 0; i < N; i++) {
        int randNum = rand() % (MAX - MIN + 1) + MIN;
        cout << "Insert: " << randNum << '\n';
        tree.insert(randNum);
    }
    tree.treeWalk("in");
    tree.treeWalk("pre");
    tree.treeWalk("post");
    tree.treeWalk("level");
    tree.printTree();
    cout << "The minimum element is: " << tree.findExtremeNode("min") -> value << '\n';
    cout << "The maximum element is: " << tree.findExtremeNode("max") -> value << '\n';
    int randNum = rand() % (MAX - MIN + 1) + MIN;
    cout << "To search and delete " << randNum << ", the result is: \n";
    try {
        cout << tree.search(randNum) -> value << '\n';
        tree.deleteNode(tree.search(randNum));
        tree.printTree();
    } catch (const char* msg) {
        cout << msg << '\n';
    }
    return 0;
}
