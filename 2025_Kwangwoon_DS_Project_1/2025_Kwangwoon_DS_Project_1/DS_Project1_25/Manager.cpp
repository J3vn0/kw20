#include "Manager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Manager::Manager() {
    flog.open("log.txt", ios::app);
    if (!flog.is_open()) {
        cerr << "Error: Unable to open log.txt" << endl;
    }
}

Manager::~Manager() {
    if (flog.is_open()) {
        flog.close();
    }
}

void Manager::run(const char* command) {
    fcmd.open(command);
    if (!fcmd.is_open()) {
        flog << "========ERROR========" << endl;
        flog << "1000" << endl;
        flog << "====================" << endl;
        return;
    }

    string cmdLine;
    while (getline(fcmd, cmdLine)) {
        stringstream ss(cmdLine);
        string cmd;
        ss >> cmd;

        if (cmd == "LOAD") {
            LOAD();
        } else if (cmd == "ADD") {
            string artist, title, runtime;
            getline(ss, artist, '|');
            getline(ss, title, '|');
            getline(ss, runtime);
            ADD(artist.substr(1), title.substr(1), runtime.substr(1));
        } else if (cmd == "QPOP") {
            QPOP();
        } else if (cmd == "SEARCH") {
            string option;
            ss >> option;
            if (option == "ARTIST") {
                string arg;
                getline(ss, arg);
                SEARCH_ARTIST(arg.substr(1));
            } else if (option == "TITLE") {
                string arg;
                getline(ss, arg);
                SEARCH_TITLE(arg.substr(1));
            } else if (option == "SONG") {
                string artist, title;
                getline(ss, artist, '|');
                getline(ss, title);
                SEARCH_SONG(artist.substr(1), title.substr(1));
            } else {
                flog << "========ERROR========" << endl;
                flog << "1000" << endl;
                flog << "====================" << endl;
            }
        } else if (cmd == "MAKEPL") {
            string option;
            ss >> option;
            if (option == "ARTIST") {
                string arg;
                getline(ss, arg);
                MAKEPL_ARTIST(arg.substr(1));
            } else if (option == "TITLE") {
                string arg;
                getline(ss, arg);
                MAKEPL_TITLE(arg.substr(1));
            } else if (option == "SONG") {
                string artist, title;
                getline(ss, artist, '|');
                getline(ss, title);
                MAKEPL_SONG(artist.substr(1), title.substr(1));
            } else {
                flog << "========ERROR========" << endl;
                flog << "1000" << endl;
                flog << "====================" << endl;
            }
        } else if (cmd == "PRINT") {
            string option;
            ss >> option;
            if (option == "ARTIST") {
                PRINT_ARTIST();
            } else if (option == "TITLE") {
                PRINT_TITLE();
            } else if (option == "LIST") {
                PRINT_LIST();
            } else {
                flog << "========ERROR========" << endl;
                flog << "1000" << endl;
                flog << "====================" << endl;
            }
        } else if (cmd == "DELETE") {
            string option;
            ss >> option;
            if (option == "ARTIST") {
                string arg;
                getline(ss, arg);
                DELETE_ARTIST(arg.substr(1));
            } else if (option == "TITLE") {
                string arg;
                getline(ss, arg);
                DELETE_TITLE(arg.substr(1));
            } else if (option == "LIST") {
                string artist, title;
                getline(ss, artist, '|');
                getline(ss, title);
                DELETE_LIST(artist.substr(1), title.substr(1));
            } else if (option == "SONG") {
                string artist, title;
                getline(ss, artist, '|');
                getline(ss, title);
                DELETE_SONG(artist.substr(1), title.substr(1));
            } else {
                flog << "========ERROR========" << endl;
                flog << "1000" << endl;
                flog << "====================" << endl;
            }
        } else if (cmd == "EXIT") {
            EXIT();
            break;
        } else {
            flog << "========ERROR========" << endl;
            flog << "1000" << endl;
            flog << "====================" << endl;
        }
    }
    fcmd.close();
}

void Manager::LOAD() {
    ifstream musicList("Music_List.txt");
    if (!musicList.is_open()) {
        flog << "========ERROR========" << endl;
        flog << "100" << endl;
        flog << "====================" << endl;
        return;
    }
    flog << "========LOAD========" << endl;
    string line;
    while (getline(musicList, line)) {
        stringstream ss(line);
        string artist, title, runtime;
        getline(ss, artist, '|');
        getline(ss, title, '|');
        getline(ss, runtime);
        q.push(artist, title, runtime);
        flog << artist << "/" << title << "/" << runtime << endl;
    }
    flog << "====================" << endl;
    flog << ": 데이터 로드를 성공함" << endl;
    musicList.close();
}

void Manager::ADD(string artist, string title, string runtime) {
    if (q.exist(artist, title)) {
        flog << "========ERROR========" << endl;
        flog << "200" << endl;
        flog << "====================" << endl;
        flog << ": 이미 Queue에 존재하는 곡을 추가한 상태" << endl;
    } else {
        q.push(artist, title, runtime);
        flog << "========ADD========" << endl;
        flog << artist << "/" << title << "/" << runtime << endl;
        flog << "====================" << endl;
        flog << ": 새로운 데이터를 추가한 상태" << endl;
    }
}

void Manager::QPOP() {
    if (q.empty()) {
        flog << "========ERROR========" << endl;
        flog << "300" << endl;
        flog << "====================" << endl;
        return;
    }
    flog << "========QPOP========" << endl;
    while (!q.empty()) {
        MusicQueueNode* node = q.pop();
        ab.insert(node);
        tb.insert(node);
        delete node;
    }
    flog << "Success" << endl;
    flog << "====================" << endl;
    flog << ": QPOP 명령어를 성공하여 BST 구조 형성 성공" << endl;
}

void Manager::SEARCH_ARTIST(string artist) {
    if (!ab.search(artist)) {
        flog << "========ERROR========" << endl;
        flog << "400" << endl;
        flog << "====================" << endl;
    }
    flog << ": 해당 Artist 명으로 노래 검색" << endl;
}

void Manager::SEARCH_TITLE(string title) {
    if (!tb.search(title)) {
        flog << "========ERROR========" << endl;
        flog << "400" << endl;
        flog << "====================" << endl;
    }
    flog << ": 노래 제목을 기준으로 검색" << endl;
}

void Manager::SEARCH_SONG(string artist, string title) {
    if (!ab.search_song(artist, title)) {
        flog << "========ERROR========" << endl;
        flog << "400" << endl;
        flog << "====================" << endl;
    }
    flog << ": 하나의 음원에 대한 검색" << endl;
}

void Manager::MAKEPL_ARTIST(string artist) {
    // 이 함수는 ArtistBST에서 데이터를 가져와야 합니다.
    // 플레이리스트에 곡을 추가하는 로직은 PlayList::makepl_artist() 함수에 구현되어 있습니다.
    ab.search_artist_and_add_to_playlist(artist, pl);
}

void Manager::MAKEPL_TITLE(string title) {
    // 이 함수는 TitleBST에서 데이터를 가져와야 합니다.
    tb.search_title_and_add_to_playlist(title, pl);
}

void Manager::MAKEPL_SONG(string artist, string title) {
    // 이 함수는 ArtistBST에서 데이터를 가져와야 합니다.
    ab.search_song_and_add_to_playlist(artist, title, pl);
}

void Manager::PRINT_ARTIST() {
    flog << "========PRINT========" << endl;
    flog << "ArtistBST" << endl;
    if (!ab.print_inorder()) {
        flog << "========ERROR========" << endl;
        flog << "600" << endl;
        flog << "====================" << endl;
    }
    flog << "====================" << endl;
    flog << ": ArtistBST 전체 출력" << endl;
}

void Manager::PRINT_TITLE() {
    flog << "========Print========" << endl;
    flog << "TitleBST" << endl;
    if (!tb.print_inorder()) {
        flog << "========ERROR========" << endl;
        flog << "600" << endl;
        flog << "====================" << endl;
    }
    flog << "====================" << endl;
    flog << ": TitleBST 전체 출력" << endl;
}

void Manager::PRINT_LIST() {
    flog << "========Print========" << endl;
    if (!pl.print()) {
        flog << "========ERROR========" << endl;
        flog << "600" << endl;
        flog << "====================" << endl;
    }
    flog << "====================" << endl;
    flog << ": playlist 전체 출력" << endl;
}

void Manager::DELETE_ARTIST(string artist) {
    bool deleted = ab.delete_node_artist(artist);
    if (!deleted) {
        flog << "========ERROR========" << endl;
        flog << "700" << endl;
        flog << "====================" << endl;
        flog << ": 존재 하지 않는 데이터에 대한 명령어" << endl;
        return;
    }
    tb.delete_node_artist(artist);
    pl.delete_node_artist(artist);
    flog << "========DELETE========" << endl;
    flog << "Success" << endl;
    flog << "====================" << endl;
    flog << ": 해당 가수 음원 전부 삭제(BST, List 전부)" << endl;
}

void Manager::DELETE_TITLE(string title) {
    bool deleted_from_title_bst = tb.delete_node_title(title);
    if (!deleted_from_title_bst) {
        flog << "========ERROR========" << endl;
        flog << "700" << endl;
        flog << "====================" << endl;
        flog << ": 존재 하지 않는 데이터에 대한 명령어" << endl;
        return;
    }
    ab.delete_node_title(title);
    pl.delete_node_title(title);
    flog << "========DELETE========" << endl;
    flog << "Success" << endl;
    flog << "====================" << endl;
    flog << ": 같은 노래 제목 전부 삭제(BST, List 전부)" << endl;
}

void Manager::DELETE_LIST(string artist, string title) {
    if (pl.delete_node_list(artist, title)) {
        flog << "========DELETE========" << endl;
        flog << "Success" << endl;
        flog << "====================" << endl;
        flog << ": playList에서만 해당 곡 삭제" << endl;
    } else {
        flog << "========ERROR========" << endl;
        flog << "700" << endl;
        flog << "====================" << endl;
        flog << ": 존재 하지 않는 데이터에 대한 명령어" << endl;
    }
}

void Manager::DELETE_SONG(string artist, string title) {
    bool deleted_from_artist_bst = ab.delete_node_song(artist, title);
    if (!deleted_from_artist_bst) {
        flog << "========ERROR========" << endl;
        flog << "700" << endl;
        flog << "====================" << endl;
        flog << ": 존재 하지 않는 데이터에 대한 명령어" << endl;
        return;
    }
    tb.delete_node_song(artist, title);
    pl.delete_node_song(artist, title);
    flog << "========DELETE========" << endl;
    flog << "Success" << endl;
    flog << "====================" << endl;
    flog << ": 해당 곡에 대한 데이터 전부 삭제" << endl;
}

void Manager::EXIT() {
    flog << "========EXIT========" << endl;
    flog << "Success" << endl;
    flog << "====================" << endl;
    flog << ": 모든 메모리 할당 해제 하며 프로그램 종료" << endl;
}