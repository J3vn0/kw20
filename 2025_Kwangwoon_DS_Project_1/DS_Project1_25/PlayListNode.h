#pragma once
#include <string>
#include <stdexcept>

class PlayListNode {
private:
	std::string artist;
	std::string title;
	int runtime_sec;

	PlayListNode* prev;
	PlayListNode* next;

public:
	// Constructors and Destructor
	PlayListNode() : runtime_sec(0), prev(nullptr), next(nullptr) {}
	PlayListNode(std::string artist, std::string title, int runtime_sec)
		: artist(artist), title(title), runtime_sec(runtime_sec), prev(nullptr), next(nullptr) {}
	~PlayListNode() {}
	
	// Getter functions for private members
	std::string getArtist() const { return artist; }
	std::string getTitle() const { return title; }
	int getRuntimeSec() const { return runtime_sec; }
	PlayListNode* getPrev() const { return prev; }
	PlayListNode* getNext() const { return next; }

	// Setter functions for private members
	void setArtist(const std::string& newArtist) { artist = newArtist; }
	void setTitle(const std::string& newTitle) { title = newTitle; }
	void setRuntimeSec(int newRuntimeSec) { runtime_sec = newRuntimeSec; }
	void setPrev(PlayListNode* newPrev) { prev = newPrev; }
	void setNext(PlayListNode* newNext) { next = newNext; }
};