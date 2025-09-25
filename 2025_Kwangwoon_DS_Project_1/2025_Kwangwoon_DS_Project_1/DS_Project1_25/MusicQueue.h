#pragma once
#include "MusicQueueNode.h"

class MusicQueue {
private:
	MusicQueueNode* head;
	MusicQueueNode* rear;
	int size = 0;
public:
	MusicQueue();
	~MusicQueue();

	bool empty() const;
	bool exist(const string& artist, const string& title) const;
	void push(const string& artist, const string& title, const string& run_time);
	MusicQueueNode* pop();
	MusicQueueNode* front() const;
    int getSize() const;
};