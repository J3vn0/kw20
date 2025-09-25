#pragma once
#include "MusicQueue.h"
#include "TitleBST.h"
#include "ArtistBST.h"
#include "PlayList.h"
#include <fstream>
#include <string>

using namespace std;

class Manager {
private:
	MusicQueue q;
	ArtistBST ab;
	TitleBST tb;
	PlayList pl;
	ifstream fcmd;
	ofstream flog;

public:
	// Constructors and Destructor
	Manager();
	~Manager();

	// Main function to run the program
	void run(const char* command);

	// Command implementations
	void LOAD();
	void ADD(string artist, string title, string runtime);
	void QPOP();
	void SEARCH_ARTIST(string artist);
	void SEARCH_TITLE(string title);
	void SEARCH_SONG(string artist, string title);
	void MAKEPL_ARTIST(string artist);
	void MAKEPL_TITLE(string title);
	void MAKEPL_SONG(string artist, string title);
	void PRINT_ARTIST();
	void PRINT_TITLE();
	void PRINT_LIST();
	void DELETE_ARTIST(string artist);
	void DELETE_TITLE(string title);
	void DELETE_LIST(string artist, string title);
	void DELETE_SONG(string artist, string title);
	void EXIT();
};