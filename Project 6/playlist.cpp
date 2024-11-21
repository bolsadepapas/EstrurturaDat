#include "playlist.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

BTreeNode::BTreeNode(int grado, bool esHoja) {
    t = grado;
    leaf = esHoja;
    keys = new Cancion[2 * t - 1];
    children = new BTreeNode *[2 * t];
    n = 0;
}

void BTreeNode::insertNonFull(Cancion k) {
    int i = n - 1;
    if (leaf) {
        while (i >= 0 && k.track_name < keys[i].track_name) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n++;
    } else {
        while (i >= 0 && k.track_name < keys[i].track_name)
            i--;
        if (children[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (k.track_name > keys[i + 1].track_name)
                i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];
    }

    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = z;
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    n++;
}

void BTree::insert(Cancion k) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->children[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0].track_name < k.track_name)
                i++;
            s->children[i]->insertNonFull(k);
            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

void BTreeNode::search(const std::string &term) {
    for (int i = 0; i < n; i++) {
        if (keys[i].track_name.find(term) != std::string::npos ||
            keys[i].artist_name.find(term) != std::string::npos) {
            std::cout << "Artista: " << keys[i].artist_name 
                      << " - Canción: " << keys[i].track_name << std::endl;
        }
    }
    if (!leaf) {
        for (int i = 0; i <= n; i++) {
            children[i]->search(term);
        }
    }
}

void BTree::search(const std::string &term) {
    if (root)
        root->search(term);
    else
        std::cout << "No se encontraron coincidencias para: " << term << std::endl;
}

void BTreeNode::collectSongs(std::vector<Cancion>& songs) {
 
    for (int i = 0; i < n; i++) {
        songs.push_back(keys[i]);
    }

    if (!leaf) {
        for (int i = 0; i <= n; i++) {
            children[i]->collectSongs(songs);  
        }
    }
}

void BTree::shuffle() {
    if (!root) {
        std::cout << "No hay canciones en la lista de reproducción." << std::endl;
        return;
    }

    std::vector<Cancion> songs;
    root->collectSongs(songs); 

  
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(songs.begin(), songs.end(), g);

   
    std::cout << "Reproducción aleatoria:" << std::endl;
    for (const auto &song : songs) {
        std::cout << song.track_name << " - " << song.artist_name << std::endl;
    }
}


void BTree::sortSongs(std::string criterio, bool asc) {
    if (!root) {
        std::cout << "No hay canciones en la lista de reproducción." << std::endl;
        return;
    }

    std::vector<Cancion> songs;
    root->collectSongs(songs); 

   
    std::sort(songs.begin(), songs.end(), [&](const Cancion &a, const Cancion &b) {
        if (criterio == "popularidad") {
            return asc ? a.popularity < b.popularity : a.popularity > b.popularity;
        } else if (criterio == "año") {
            return asc ? a.year < b.year : a.year > b.year;
        } else if (criterio == "nombre") {
            return asc ? a.track_name < b.track_name : a.track_name > b.track_name;
        }
        return false; 
    });

    
    std::cout << "Canciones ordenadas por " << criterio << ":" << std::endl;
    for (const auto &song : songs) {
        std::cout << song.track_name << " - " << song.artist_name << std::endl;
    }
}

