#pragma once
#include <string>
#include "PlayListNode.h"
#include "MusicQueueNode.h" // For data from BSTs

class PlayList {
private:
	PlayListNode* head;
	PlayListNode* cursor;
	int count;
	int total_time_sec;
	
	// Private helper functions for internal logic
	void update_total_time();
	PlayListNode* findNode(const std::string& artist, const std::string& title);

public:
	// Constructors and Destructor
	PlayList();
	~PlayList();

	// Public interface functions
	void insert_node(std::string artist, std::string title, std::string runtime);
	bool delete_node(const std::string& artist, const std::string& title);
	bool empty() const;
	bool full() const;
	bool exist(const std::string& artist, const std::string& title);
	bool print() const;
	std::string getRuntimeString() const;
    
    // Functions for MAKEPL command
    bool makepl_artist(const std::string& artist);
    bool makepl_title(const std::string& title);
    bool makepl_song(const std::string& artist, const std::string& title);

    // Functions for DELETE command
    bool delete_node_artist(const std::string& artist);
    bool delete_node_title(const std::string& title);
    bool delete_node_list(const std::string& artist, const std::string& title);
    bool delete_node_song(const std::string& artist, const std::string& title);
};