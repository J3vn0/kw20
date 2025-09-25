#pragma once
#include <string>
#include <vector>
#include "MusicQueueNode.h"

using namespace std;

class ArtistBSTNode {
private:
	string artist;
	vector<string> title;
	vector<string> run_time;
	int count;
	ArtistBSTNode* left;
	ArtistBSTNode* right;

public:
	// Constructors and Destructor
	ArtistBSTNode() : count(0), left(nullptr), right(nullptr) {}
	ArtistBSTNode(string artist, string title, string run_time) : count(1), left(nullptr), right(nullptr) {
		this->artist = artist;
		this->title.push_back(title);
		this->run_time.push_back(run_time);
	}
	~ArtistBSTNode() {}

	// Getter functions to access private members
	string getArtist() const { return artist; }
	const vector<string>& getTitles() const { return title; }
	const vector<string>& getRunTimes() const { return run_time; }
	int getCount() const { return count; }
	ArtistBSTNode* getLeft() const { return left; }
	ArtistBSTNode* getRight() const { return right; }

	// Setter functions to enable modification by ArtistBST
	void setArtist(const string& newArtist) { artist = newArtist; }
	void setTitles(const vector<string>& newTitles) { title = newTitles; }
	void setRunTimes(const vector<string>& newRunTimes) { run_time = newRunTimes; }
	void setCount(int newCount) { count = newCount; }
	void setLeft(ArtistBSTNode* node) { left = node; }
	void setRight(ArtistBSTNode* node) { right = node; }
    
    // Functions to modify song data
	void addSong(string newTitle, string newRunTime) {
		this->title.push_back(newTitle);
		this->run_time.push_back(newRunTime);
		this->count++;
	}
	bool removeSong(string songTitle) {
		for (size_t i = 0; i < title.size(); ++i) {
			if (title[i] == songTitle) {
				title.erase(title.begin() + i);
				run_time.erase(run_time.begin() + i);
				count--;
				return true;
			}
		}
		return false;
	}
};