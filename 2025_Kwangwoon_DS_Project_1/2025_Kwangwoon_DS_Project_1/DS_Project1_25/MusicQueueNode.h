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
	// Constructors and Destructor
	MusicQueueNode() : next(nullptr), prev(nullptr) {}
	MusicQueueNode(string artist, string title, string run_time) : next(nullptr), prev(nullptr) {
		this->artist = artist;
		this->title = title;
		this->run_time = run_time;
	}
	~MusicQueueNode() {}

	// Getter functions to access private members
    string getArtist() const { return artist; }
    string getTitle() const { return title; }
    string getRunTime() const { return run_time; }
    MusicQueueNode* getNext() const { return next; }
    MusicQueueNode* getPrev() const { return prev; }

    // Setter functions to modify private members
    void setArtist(const string& newArtist) { artist = newArtist; }
    void setTitle(const string& newTitle) { title = newTitle; }
    void setRunTime(const string& newRunTime) { run_time = newRunTime; }
    void setNext(MusicQueueNode* newNext) { next = newNext; }
    void setPrev(MusicQueueNode* newPrev) { prev = newPrev; }
};