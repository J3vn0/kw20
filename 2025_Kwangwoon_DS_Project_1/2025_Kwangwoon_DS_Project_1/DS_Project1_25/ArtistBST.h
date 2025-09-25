#pragma once
#include "ArtistBSTNode.h"
#include "MusicQueueNode.h"
#include <iostream>

class ArtistBST {
private:
    ArtistBSTNode* root;

    void destroyTree(ArtistBSTNode* node);
    ArtistBSTNode* insertRecursive(ArtistBSTNode* node, const std::string& artist, const std::string& title, const std::string& run_time);
    void printInorderRecursive(ArtistBSTNode* node);
    ArtistBSTNode* deleteRecursive(ArtistBSTNode* node, const std::string& artist);
    ArtistBSTNode* findMin(ArtistBSTNode* node);
    bool deleteNodeTitleRecursive(ArtistBSTNode* node, const std::string& title);

public:
    ArtistBST();
    ~ArtistBST();

    void insert(MusicQueueNode* data);
    bool search(const std::string& artist);
    bool search_song(const std::string& artist, const std::string& title);
    bool print_inorder();
    bool delete_node_artist(const std::string& artist);
    bool delete_node_song(const std::string& artist, const std::string& title);
    bool delete_node_title(const std::string& title); // Added this function
};