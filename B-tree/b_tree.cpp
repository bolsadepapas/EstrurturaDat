#include "b_tree.h"
#include <iostream>
#include <cstdlib>

BTreeNode* createNode() {
    BTreeNode *newNode = new BTreeNode;
    newNode->num_keys = 0;
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        newNode->children[i] = nullptr;
    }
    return newNode;
}

void insert(BTreeNode **root, double key) {
    if (*root == nullptr) {
        *root = createNode();
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
    } else {
        if ((*root)->num_keys == MAX_KEYS) {
            BTreeNode *newRoot = createNode();
            newRoot->children[0] = *root;
            splitChild(newRoot, 0);
            *root = newRoot;
        }
        insertNonFull(*root, key);
    }
}

void splitChild(BTreeNode *parent, int index) {
    BTreeNode *child = parent->children[index];
    BTreeNode *newChild = createNode();
    newChild->num_keys = MAX_KEYS / 2;

    for (int i = 0; i < MAX_KEYS / 2; i++) {
        newChild->keys[i] = child->keys[i + MAX_KEYS / 2 + 1];
    }

    if (child->children[0] != nullptr) {
        for (int i = 0; i < MAX_KEYS / 2 + 1; i++) {
            newChild->children[i] = child->children[i + MAX_KEYS / 2 + 1];
        }
    }

    child->num_keys = MAX_KEYS / 2;
    for (int i = parent->num_keys; i >= index + 1; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = newChild;

    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[index] = child->keys[MAX_KEYS / 2];
    parent->num_keys++;
}

void insertNonFull(BTreeNode *node, double key) {
    int i = node->num_keys - 1;
    if (node->children[0] == nullptr) {
        insertKey(node, key);
        return;
    }

    while (i >= 0 && node->keys[i] > key) {
        i--;
    }
    i++;
    if (node->children[i]->num_keys == MAX_KEYS) {
        splitChild(node, i);
        if (node->keys[i] < key) {
            i++;
        }
    }
    insertNonFull(node->children[i], key);
}

void insertKey(BTreeNode *node, double key) {
    int i = node->num_keys - 1;
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i + 1] = node->keys[i];
        i--;
    }
    node->keys[i + 1] = key;
    node->num_keys++;
}

// Implementación de la función de búsqueda
bool search(BTreeNode *node, double key) {
    int i = 0;
    while (i < node->num_keys && key > node->keys[i]) {
        i++;
    }

    if (i < node->num_keys && node->keys[i] == key) {
        return true;
    }

    if (node->children[0] == nullptr) {
        return false;
    }

    return search(node->children[i], key);
}

