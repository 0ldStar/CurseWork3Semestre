//
// Created by 777 on 14.12.2021.
//

#ifndef COURSEWORK_3_SEMESTER_TREE_H
#define COURSEWORK_3_SEMESTER_TREE_H

#include "MiddleNode.h"
#include "Node.h"
#include "FNode.h"
#include <fstream>
#include <iostream>
#include <cstring>
//#pragma pack (pop)
using namespace std;

class Tree : public fstream {
public:
    Tree();

    Tree(Tree &a);

    ~Tree();

    void toBinary();

    void LoadTree();

//    void printTree();

    void insert(char *str);

    friend ostream &operator<<(ostream &os, Tree &tree);

    Tree &operator<<(char *str);

//    Tree &operator>>(ostream &of);

    Tree &operator<<(ifstream &is);

    friend istream &operator>>(istream &os, Tree &tree);

private:
    long long PutTree(Node *q);

    Node *GetTree(long long pos);

    int addNode(Node **node, char *str);

    void freeNode(Node *node);

    void copyNode(Node *node, char *str, int mode);

    int checkNode(Node **node, char *str);

    void createNode(Node **node, char *str);

    void printNode(Node *node, ostream &os);

    Node *root;
    int level;
    int peakCount;
};


#endif //COURSEWORK_3_SEMESTER_TREE_H
