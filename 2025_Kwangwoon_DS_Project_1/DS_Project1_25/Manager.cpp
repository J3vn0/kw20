#include "Manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

Manager::Manager() {
    // Constructor initializes all data structures
    // The objects are declared as member variables in Manager.h, so they are
    // automatically created when a Manager object is instantiated.
}

Manager::~Manager() {
    // Destructor
    // The member variables (que, artist_bst, title_bst, playlist)
    // will be automatically destructed, so no manual deletion is needed here.
}

// Main function to run the program by processing commands from a file
void Manager::Run(string command_file) {
    ifstream file(command_file);
    if (!file.is_open()) {
        cout << "Error opening command file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        cout << "======== " << line << " ========" << endl;

        vector<string> tokens;
        stringstream ss(line);
        string token;
        while (getline(ss, token, ' ')) {
            tokens.push_back(token);
        }

        string command = tokens[0];

        if (command == "LOAD") {
            Load();
        } else if (command == "ADD") {
            if (tokens.size() > 1) {
                Add(tokens[1]);
            }
        } else if (command == "QPOP") {
            Qpop();
        } else if (command == "SEARCH") {
            if (tokens.size() > 2) {
                if (tokens[1] == "ARTIST") {
                    SearchArtist(tokens[2]);
                } else if (tokens[1] == "TITLE") {
                    SearchTitle(tokens[2]);
                } else if (tokens[1] == "SONG") {
                    SearchSong(tokens[2]);
                }
            }
        } else if (command == "MAKEPL") {
            if (tokens.size() > 2) {
                if (tokens[1] == "ARTIST") {
                    MakeplArtist(tokens[2]);
                } else if (tokens[1] == "TITLE") {
                    MakeplTitle(tokens[2]);
                } else if (tokens[1] == "SONG") {
                    MakeplSong(tokens[2]);
                }
            }
        } else if (command == "PRINT") {
            if (tokens.size() > 1) {
                if (tokens[1] == "ARTIST") {
                    PrintArtist();
                } else if (tokens[1] == "TITLE") {
                    PrintTitle();
                } else if (tokens[1] == "LIST") {
                    PrintList();
                }
            }
        } else if (command == "DELETE") {
            if (tokens.size() > 2) {
                if (tokens[1] == "ARTIST") {
                    DeleteArtist(tokens[2]);
                } else if (tokens[1] == "TITLE") {
                    DeleteTitle(tokens[2]);
                } else if (tokens[1] == "LIST") {
                    DeleteList(tokens[2]);
                } else if (tokens[1] == "SONG") {
                    DeleteSong(tokens[2]);
                }
            }
        } else if (command == "EXIT") {
            break;
        }

        cout << "====================" << endl << endl;
    }
}

// LOAD command implementation
void Manager::Load() {
    ifstream music_file("Music_List.txt");
    if (!music_file.is_open()) {
        cout << "Error opening Music_List.txt" << endl;
        return;
    }

    string line;
    while (getline(music_file, line)) {
        que.push(line);
        cout << line << endl;
    }
}

// ADD command implementation
void Manager::Add(const string& data) {
    MusicQueueNode* newNode = new MusicQueueNode(data);
    if (que.exist(newNode)) {
        cout << "========ERROR========" << endl;
        cout << "200" << endl;
    } else {
        que.push(data);
        cout << data << endl;
    }
    delete newNode; // Clean up temp node
}

// QPOP command implementation
void Manager::Qpop() {
    if (que.empty()) {
        cout << "========ERROR========" << endl;
        cout << "100" << endl;
        return;
    }
    while (!que.empty()) {
        MusicQueueNode* data = que.pop();
        artist_bst.insert(data);
        title_bst.insert(data);
        delete data; // Free the node after use
    }
    cout << "Success" << endl;
}

// SEARCH command implementations
void Manager::SearchArtist(const string& artist) {
    artist_bst.search(artist);
}

void Manager::SearchTitle(const string& title) {
    title_bst.search(title);
}

void Manager::SearchSong(const string& data) {
    stringstream ss(data);
    string artist, title;
    getline(ss, artist, '|');
    getline(ss, title, '|');
    artist_bst.search_song(artist, title);
    title_bst.search_song(artist, title);
}

// MAKEPL command implementations
void Manager::MakeplArtist(const string& artist) {
    // This is a placeholder, as MAKEPL logic needs to be added here.
    // The logic would involve traversing the ArtistBST and adding to the PlayList.
}

void Manager::MakeplTitle(const string& title) {
    // This is a placeholder, similar to MakeplArtist
}

void Manager::MakeplSong(const string& data) {
    // This is a placeholder, similar to other MAKEPL functions
}

// PRINT command implementations
void Manager::PrintArtist() {
    cout << "ArtistBST" << endl;
    artist_bst.print_inorder();
}

void Manager::PrintTitle() {
    cout << "TitleBST" << endl;
    title_bst.print_inorder();
}

void Manager::PrintList() {
    cout << "PlayList" << endl;
    playlist.print();
}

// DELETE command implementations
void Manager::DeleteArtist(const string& artist) {
    bool deleted_from_artist_bst = artist_bst.delete_node_artist(artist);
    bool deleted_from_title_bst = title_bst.delete_node_artist(artist);
    bool deleted_from_playlist = playlist.delete_node_artist(artist);

    if (deleted_from_artist_bst || deleted_from_title_bst || deleted_from_playlist) {
        cout << "Success" << endl;
    } else {
        cout << "========ERROR========" << endl;
        cout << "700" << endl;
    }
}

void Manager::DeleteTitle(const string& title) {
    bool deleted_from_title_bst = title_bst.delete_node_title(title);
    bool deleted_from_artist_bst = artist_bst.delete_node_title(title); // Assuming this function exists in ArtistBST
    bool deleted_from_playlist = playlist.delete_node_title(title);

    if (deleted_from_title_bst || deleted_from_artist_bst || deleted_from_playlist) {
        cout << "Success" << endl;
    } else {
        cout << "========ERROR========" << endl;
        cout << "700" << endl;
    }
}

void Manager::DeleteList(const string& data) {
    stringstream ss(data);
    string artist, title;
    getline(ss, artist, '|');
    getline(ss, title, '|');

    bool deleted = playlist.delete_node(artist, title);
    if (deleted) {
        cout << "Success" << endl;
    } else {
        cout << "========ERROR========" << endl;
        cout << "700" << endl;
    }
}

void Manager::DeleteSong(const string& data) {
    stringstream ss(data);
    string artist, title;
    getline(ss, artist, '|');
    getline(ss, title, '|');

    bool deleted_from_artist_bst = artist_bst.delete_node_song(artist, title);
    bool deleted_from_title_bst = title_bst.delete_node_song(artist, title);
    bool deleted_from_playlist = playlist.delete_node_song(artist, title);

    if (deleted_from_artist_bst || deleted_from_title_bst || deleted_from_playlist) {
        cout << "Success" << endl;
    } else {
        cout << "========ERROR========" << endl;
        cout << "700" << endl;
    }
}