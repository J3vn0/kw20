#include "MusicQueue.h"
#include <iostream>
#include <string>
#include <fstream>

MusicQueue::MusicQueue() {
	head = nullptr;
	rear = nullptr;
}

MusicQueue::~MusicQueue() {
    while (head != nullptr) {
        MusicQueueNode* temp = head;
        head = head->getNext();
        delete temp;
    }
}

bool MusicQueue::empty() {
	return head == nullptr;
}

// 주어진 음악 데이터가 Queue에 이미 존재하는지 확인
bool MusicQueue::exist(string artist, string title) {
    MusicQueueNode* current = head;
    while (current != nullptr) {
        if (current->getArtist() == artist && current->getTitle() == title) {
            return true;
        }
        current = current->getNext();
    }
    return false;
}

// Queue에 새로운 음악 데이터를 추가
void MusicQueue::push(string artist, string title, string run_time) {
    if (size >= 100) {
        cout << "========ERROR========" << endl;
        cout << "200" << endl;
        cout << "====================" << endl;
        exit(1);
    }
    MusicQueueNode* newNode = new MusicQueueNode();
    newNode->setArtist(artist);
    newNode->setTitle(title);
    newNode->setRunTime(run_time);
    newNode->setNext(nullptr);
    newNode->setPrev(nullptr);

    if (empty()) {
        head = newNode;
        rear = newNode;
    } else {
        rear->setNext(newNode);
        newNode->setPrev(rear);
        rear = newNode;
    }
    size++;
}

// Queue의 맨 앞 데이터를 제거하고 반환
MusicQueueNode* MusicQueue::pop() {
    if (empty()) {
        cout << "========ERROR========" << endl;
        cout << "300" << endl;
        cout << "====================" << endl;
        exit(1);
    }
    MusicQueueNode* temp = head;
    head = head->getNext();
    if (head != nullptr) {
        head->setPrev(nullptr);
    } else {
        rear = nullptr;
    }
    size--;
    return temp;
}

// Queue의 맨 앞 데이터를 제거하지 않고 반환
MusicQueueNode* MusicQueue::front() {
    if (empty()) {
        return nullptr;
    }
    return head;
}