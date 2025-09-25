#pragma once
#include "ArtistBSTNode.h"

class ArtistBST {
private:
	ArtistBSTNode* root;

	void destroyTree(ArtistBSTNode* node);
	ArtistBSTNode* insertRecursive(ArtistBSTNode* node, string artist, string title, string run_time); // Changed return type
	void printInorderRecursive(ArtistBSTNode* node);
	ArtistBSTNode* deleteRecursive(ArtistBSTNode* node, string artist);
	ArtistBSTNode* findMin(ArtistBSTNode* node);

public:
	ArtistBST();
	~ArtistBST();

	void insert(MusicQueueNode* data);
	bool search(string artist);
	bool search_song(string artist, string title);
	bool print_inorder();
	bool delete_node_artist(string artist);
	bool delete_node_song(string artist, string title);
};