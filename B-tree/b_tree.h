#ifndef B_TREE_H
#define B_TREE_H

#define MAX_KEYS 3

struct BTreeNode {
    int num_keys;
    double keys[MAX_KEYS];
    BTreeNode *children[MAX_KEYS + 1];
};

BTreeNode* createNode();
void insert(BTreeNode **root, double key);
void splitChild(BTreeNode *parent, int index);
void insertNonFull(BTreeNode *node, double key);
void insertKey(BTreeNode *node, double key);
bool search(BTreeNode *node, double key);  //aqui se declara la funcion de busqueda para los datos que deseemos encontrar 

#endif
