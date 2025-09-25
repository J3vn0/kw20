#pragma once
#include "TitleBSTNode.h"
#include "MusicQueueNode.h"

class TitleBST {
private:
	TitleBSTNode* root;

	void destroyTree(TitleBSTNode* node);
	TitleBSTNode* insertRecursive(TitleBSTNode* node, string title, string artist, string run_time);
	void printInorderRecursive(TitleBSTNode* node);
	TitleBSTNode* findMin(TitleBSTNode* node);
	TitleBSTNode* deleteRecursive(TitleBSTNode* node, string title);

public:
	TitleBST();
	~TitleBST();

	void insert(MusicQueueNode* data);
	bool search(string title);
	bool search_song(string artist, string title);
	bool print_inorder();
	bool delete_node_title(string title);
	bool delete_node_song(string artist, string title);
	bool delete_node_artist(string artist);
};