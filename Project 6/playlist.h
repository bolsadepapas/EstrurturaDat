#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <random> 
#include <map>

struct Cancion {
    int order_id;
    std::string artist_name;
    std::string track_name;
    std::string track_id;
    int popularity;
    int year;

    Cancion() : order_id(0), popularity(0), year(0) {}
};

class BTreeNode {
    int t;
    Cancion *keys;
    BTreeNode **children;
    int n;
    bool leaf;

public:
    BTreeNode(int grado, bool esHoja);
    void insertNonFull(Cancion k);
    void splitChild(int i, BTreeNode *y);
    void search(const std::string &term);
    void collectSongs(std::vector<Cancion>& songs);
    friend class BTree;
  
};

class BTree {
    BTreeNode *root;
    int t;

public:
    BTree(int grado) : root(nullptr), t(grado) {}
    void insert(Cancion k);
    void search(const std::string &term);
    void shuffle();
    void sortSongs(std::string criterio, bool asc);
    BTreeNode* getRoot() { return root; }
};

#endif // PLAYLIST_H