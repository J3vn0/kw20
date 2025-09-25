#pragma once
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

class MusicQueueNode {
private:
	string artist;
	string title;
	string run_time;

	MusicQueueNode* next;
	MusicQueueNode* prev;

public:
	MusicQueueNode() {}
	~MusicQueueNode() {}

	// Getter and Setter functions to access private members
    string getArtist() { return artist; }
    string getTitle() { return title; }
    string getRunTime() { return run_time; }
    MusicQueueNode* getNext() { return next; }
    MusicQueueNode* getPrev() { return prev; }

    void setArtist(string newArtist) { artist = newArtist; }
    void setTitle(string newTitle) { title = newTitle; }
    void setRunTime(string newRunTime) { run_time = newRunTime; }
    void setNext(MusicQueueNode* newNext) { next = newNext; }
    void setPrev(MusicQueueNode* newPrev) { prev = newPrev; }

	void insert() {

	}

	bool exist() {
		return false;
	}
};