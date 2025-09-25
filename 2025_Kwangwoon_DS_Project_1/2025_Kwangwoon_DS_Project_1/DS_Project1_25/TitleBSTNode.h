#pragma once
#include <string>
#include <vector>
#include "MusicQueueNode.h"

using namespace std;

class TitleBSTNode {
private:
	string title;
	vector<string> artist;
	vector<string> run_time;
	int count;
	TitleBSTNode* left;
	TitleBSTNode* right;

public:
	TitleBSTNode() : count(0), left(nullptr), right(nullptr) {}
	TitleBSTNode(string title, string artist, string run_time) : count(1), left(nullptr), right(nullptr) {
		this->title = title;
		this->artist.push_back(artist);
		this->run_time.push_back(run_time);
	}
	~TitleBSTNode() {}

	// Getter functions to access private members
	string getTitle() const { return title; }
	const vector<string>& getArtists() const { return artist; }
	const vector<string>& getRunTimes() const { return run_time; }
	int getCount() const { return count; }
	TitleBSTNode* getLeft() const { return left; }
	TitleBSTNode* getRight() const { return right; }

	// Setter functions for BST structure and data manipulation
	void setTitle(const string& newTitle) { this->title = newTitle; }
	void setArtists(const vector<string>& newArtists) { this->artist = newArtists; }
	void setRunTimes(const vector<string>& newRunTimes) { this->run_time = newRunTimes; }
	void setCount(int newCount) { this->count = newCount; }
	void setLeft(TitleBSTNode* node) { left = node; }
	void setRight(TitleBSTNode* node) { right = node; }

	// Functions to modify data within the node
	void addArtist(string newArtist, string newRunTime) {
		this->artist.push_back(newArtist);
		this->run_time.push_back(newRunTime);
		this->count++;
	}
	bool removeArtist(string artistToRemove) {
		for (size_t i = 0; i < artist.size(); ++i) {
			if (artist[i] == artistToRemove) {
				artist.erase(artist.begin() + i);
				run_time.erase(run_time.begin() + i);
				count--;
				return true;
			}
		}
		return false;
	}
};