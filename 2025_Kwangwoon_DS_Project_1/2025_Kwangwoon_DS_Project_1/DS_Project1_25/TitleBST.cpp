#include "TitleBST.h"
#include <iostream>

using namespace std;

// TitleBST 클래스 생성자
TitleBST::TitleBST() : root(nullptr) {}

// TitleBST 클래스 소멸자
TitleBST::~TitleBST() {
    destroyTree(root);
}

// 트리를 재귀적으로 파괴하는 비공개(private) 헬퍼 함수
void TitleBST::destroyTree(TitleBSTNode* node) {
    if (node) {
        destroyTree(node->getLeft());
        destroyTree(node->getRight());
        delete node;
    }
}

// 새로운 음악 데이터를 BST에 삽입하는 공개 함수
void TitleBST::insert(MusicQueueNode* data) {
    root = insertRecursive(root, data->getTitle(), data->getArtist(), data->getRunTime());
}

// 삽입을 위한 재귀적 헬퍼 함수
TitleBSTNode* TitleBST::insertRecursive(TitleBSTNode* node, string title, string artist, string run_time) {
    if (node == nullptr) {
        return new TitleBSTNode(title, artist, run_time);
    }
    
    if (title < node->getTitle()) {
        node->setLeft(insertRecursive(node->getLeft(), title, artist, run_time));
    } else if (title > node->getTitle()) {
        node->setRight(insertRecursive(node->getRight(), title, artist, run_time));
    } else {
        node->addArtist(artist, run_time);
    }
    return node;
}

// 노래 제목을 기준으로 노드를 검색하고 해당 정보를 출력하는 함수
bool TitleBST::search(string title) {
    TitleBSTNode* current = root;
    bool found = false;
    while (current != nullptr) {
        if (current->getTitle() == title) {
            found = true;
            cout << "========SEARCH========" << endl;
            const vector<string>& artists = current->getArtists();
            const vector<string>& runTimes = current->getRunTimes();
            for (size_t i = 0; i < artists.size(); ++i) {
                cout << artists[i] << "/" << current->getTitle() << "/" << runTimes[i] << endl;
            }
            cout << "====================" << endl;
            break;
        } else if (title < current->getTitle()) {
            current = current->getLeft();
        } else {
            current = current->getRight();
        }
    }
    if (!found) {
        cout << "========ERROR========" << endl;
        cout << "400" << endl;
        cout << "====================" << endl;
    }
    return found;
}

// 특정 가수와 제목을 가진 곡을 검색하는 함수
bool TitleBST::search_song(string artist, string title) {
    TitleBSTNode* current = root;
    while (current != nullptr) {
        if (current->getTitle() == title) {
            const vector<string>& artists = current->getArtists();
            const vector<string>& runTimes = current->getRunTimes();
            for (size_t i = 0; i < artists.size(); ++i) {
                if (artists[i] == artist) {
                    cout << "========SEARCH========" << endl;
                    cout << artists[i] << "/" << current->getTitle() << "/" << runTimes[i] << endl;
                    cout << "====================" << endl;
                    return true;
                }
            }
            break;
        } else if (title < current->getTitle()) {
            current = current->getLeft();
        } else {
            current = current->getRight();
        }
    }
    cout << "========ERROR========" << endl;
    cout << "400" << endl;
    cout << "====================" << endl;
    return false;
}

// 중위 순회(in-order traversal)로 모든 노드를 출력하는 함수
bool TitleBST::print_inorder() {
    if (root == nullptr) {
        return false;
    }
    printInorderRecursive(root);
    return true;
}

// 중위 순회를 위한 재귀적 헬퍼 함수
void TitleBST::printInorderRecursive(TitleBSTNode* node) {
    if (node) {
        printInorderRecursive(node->getLeft());
        const vector<string>& artists = node->getArtists();
        const vector<string>& runTimes = node->getRunTimes();
        for (size_t i = 0; i < artists.size(); ++i) {
            cout << artists[i] << "/" << node->getTitle() << "/" << runTimes[i] << endl;
        }
        printInorderRecursive(node->getRight());
    }
}

// 노래 제목을 기준으로 노드를 삭제하는 함수
bool TitleBST::delete_node_title(string title) {
    TitleBSTNode* oldRoot = root;
    root = deleteRecursive(root, title);
    return oldRoot != root;
}

// 노드 삭제를 위한 재귀적 헬퍼 함수
TitleBSTNode* TitleBST::deleteRecursive(TitleBSTNode* node, string title) {
    if (node == nullptr) {
        return nullptr;
    }

    if (title < node->getTitle()) {
        node->setLeft(deleteRecursive(node->getLeft(), title));
    } else if (title > node->getTitle()) {
        node->setRight(deleteRecursive(node->getRight(), title));
    } else {
        // 자식이 하나만 있거나 없는 경우
        if (node->getLeft() == nullptr) {
            TitleBSTNode* temp = node->getRight();
            delete node;
            return temp;
        } else if (node->getRight() == nullptr) {
            TitleBSTNode* temp = node->getLeft();
            delete node;
            return temp;
        }

        // 자식이 둘 다 있을 경우: 오른쪽 서브트리에서 가장 작은 노드를 찾음
        TitleBSTNode* temp = findMin(node->getRight());

        // 후속 노드의 데이터로 현재 노드의 데이터를 대체
        node->setTitle(temp->getTitle());
        node->setArtists(temp->getArtists());
        node->setRunTimes(temp->getRunTimes());
        node->setCount(temp->getCount());

        // 후속 노드 삭제
        node->setRight(deleteRecursive(node->getRight(), temp->getTitle()));
    }
    return node;
}

// BST 서브트리에서 가장 작은 값을 가진 노드를 찾는 헬퍼 함수
TitleBSTNode* TitleBST::findMin(TitleBSTNode* node) {
    TitleBSTNode* current = node;
    while (current && current->getLeft() != nullptr) {
        current = current->getLeft();
    }
    return current;
}

// 특정 곡(아티스트와 제목)을 삭제하는 함수
bool TitleBST::delete_node_song(string artist, string title) {
    TitleBSTNode* current = root;
    bool deleted = false;
    while (current != nullptr) {
        if (current->getTitle() == title) {
            if (current->removeArtist(artist)) {
                deleted = true;
                if (current->getCount() == 0) {
                    delete_node_title(title);
                }
            }
            break;
        } else if (title < current->getTitle()) {
            current = current->getLeft();
        } else {
            current = current->getRight();
        }
    }
    return deleted;
}

// 특정 가수의 모든 곡을 삭제하는 함수
bool TitleBST::delete_node_artist(string artist) {
    bool deleted = deleteArtistRecursive(root, artist);
    return deleted;
}