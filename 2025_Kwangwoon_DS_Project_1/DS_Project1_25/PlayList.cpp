#include "PlayList.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

PlayList::PlayList() : head(nullptr), cursor(nullptr), count(0), total_time_sec(0) {}

PlayList::~PlayList() {
    if (head == nullptr) {
        return;
    }
    PlayListNode* current = head->getNext();
    while (current != head) {
        PlayListNode* temp = current;
        current = current->getNext();
        delete temp;
    }
    delete head;
}

// 재생 시간을 "분:초" 형식으로 변환하여 반환
string PlayList::getRuntimeString() const {
    int minutes = total_time_sec / 60;
    int seconds = total_time_sec % 60;
    stringstream ss;
    ss << minutes << "min " << seconds << "sec";
    return ss.str();
}

// PlayList가 비어있는지 확인
bool PlayList::empty() const {
    return count == 0;
}

// PlayList가 가득 찼는지 확인
bool PlayList::full() const {
    return count >= 10;
}

// PlayList에 특정 곡이 존재하는지 확인
bool PlayList::exist(const string& artist, const string& title) {
    if (head == nullptr) {
        return false;
    }
    PlayListNode* current = head;
    do {
        if (current->getArtist() == artist && current->getTitle() == title) {
            return true;
        }
        current = current->getNext();
    } while (current != head);
    return false;
}

// 총 재생 시간을 업데이트
void PlayList::update_total_time() {
    total_time_sec = 0;
    if (head == nullptr) {
        return;
    }
    PlayListNode* current = head;
    do {
        total_time_sec += current->getRuntimeSec();
        current = current->getNext();
    } while (current != head);
}

// 노드를 삽입하고 총 시간을 업데이트합니다.
void PlayList::insert_node(string artist, string title, string runtime) {
    if (full()) {
        return;
    }

    // "분:초"를 초 단위로 변환
    size_t colon_pos = runtime.find(':');
    int minutes = stoi(runtime.substr(0, colon_pos));
    int seconds = stoi(runtime.substr(colon_pos + 1));
    int runtime_sec = minutes * 60 + seconds;

    PlayListNode* newNode = new PlayListNode(artist, title, runtime_sec);

    if (empty()) {
        head = newNode;
        head->setNext(head);
        head->setPrev(head);
        cursor = head;
    } else {
        PlayListNode* tail = head->getPrev();
        tail->setNext(newNode);
        newNode->setPrev(tail);
        newNode->setNext(head);
        head->setPrev(newNode);
    }
    count++;
    update_total_time();
}

// PlayList의 모든 노드를 출력합니다.
bool PlayList::print() const {
    if (empty()) {
        cout << "========ERROR========" << endl;
        cout << "600" << endl;
        cout << "====================" << endl;
        return false;
    }
    PlayListNode* current = head;
    do {
        cout << current->getArtist() << "/" << current->getTitle() << "/" << current->getRuntimeSec() / 60 << ":" << setw(2) << setfill('0') << current->getRuntimeSec() % 60 << endl;
        current = current->getNext();
    } while (current != head);

    cout << "Count: " << count << " / 10" << endl;
    cout << "Time: " << getRuntimeString() << endl;
    return true;
}

// PlayList에서 특정 곡을 삭제합니다.
bool PlayList::delete_node(const string& artist, const string& title) {
    if (empty()) {
        return false;
    }

    PlayListNode* nodeToDelete = nullptr;
    PlayListNode* current = head;
    do {
        if (current->getArtist() == artist && current->getTitle() == title) {
            nodeToDelete = current;
            break;
        }
        current = current->getNext();
    } while (current != head);

    if (nodeToDelete == nullptr) {
        return false;
    }

    // 노드 삭제
    if (count == 1) {
        head = nullptr;
    } else {
        nodeToDelete->getPrev()->setNext(nodeToDelete->getNext());
        nodeToDelete->getNext()->setPrev(nodeToDelete->getPrev());
        if (nodeToDelete == head) {
            head = nodeToDelete->getNext();
        }
    }
    delete nodeToDelete;
    count--;
    update_total_time();
    return true;
}

// MAKEPL_ARTIST 명령어
bool PlayList::makepl_artist(const string& artist) {
    // 이 함수는 ArtistBST에서 데이터를 가져와야 함.
    // ArtistBST와 TitleBST에 대한 접근이 필요합니다.
    return false;
}

// MAKEPL_TITLE 명령어
bool PlayList::makepl_title(const string& title) {
    // 이 함수는 TitleBST에서 데이터를 가져와야 함.
    return false;
}

// MAKEPL_SONG 명령어
bool PlayList::makepl_song(const string& artist, const string& title) {
    // 이 함수는 BST에서 데이터를 가져와야 함.
    return false;
}

// DELETE_ARTIST 명령어 (PlayList에서만)
bool PlayList::delete_node_artist(const string& artist) {
    bool deleted = false;
    if (empty()) {
        return false;
    }
    PlayListNode* current = head;
    PlayListNode* nextNode;
    do {
        nextNode = current->getNext();
        if (current->getArtist() == artist) {
            if (delete_node(current->getArtist(), current->getTitle())) {
                deleted = true;
            }
        }
        current = nextNode;
    } while (current != head && !empty());
    return deleted;
}

// DELETE_TITLE 명령어 (PlayList에서만)
bool PlayList::delete_node_title(const string& title) {
    bool deleted = false;
    if (empty()) {
        return false;
    }
    PlayListNode* current = head;
    PlayListNode* nextNode;
    do {
        nextNode = current->getNext();
        if (current->getTitle() == title) {
            if (delete_node(current->getArtist(), current->getTitle())) {
                deleted = true;
            }
        }
        current = nextNode;
    } while (current != head && !empty());
    return deleted;
}

// DELETE_LIST 명령어 (PlayList에서만)
bool PlayList::delete_node_list(const string& artist, const string& title) {
    return delete_node(artist, title);
}

// DELETE_SONG 명령어 (PlayList에서만)
bool PlayList::delete_node_song(const string& artist, const string& title) {
    return delete_node(artist, title);
}