#include "ArtistBST.h"
#include <iostream>

using namespace std;

// ArtistBST constructor
ArtistBST::ArtistBST() : root(nullptr) {}

// ArtistBST destructor
ArtistBST::~ArtistBST() {
    destroyTree(root);
}

// Private helper function to recursively destroy the tree
void ArtistBST::destroyTree(ArtistBSTNode* node) {
    if (node) {
        destroyTree(node->getLeft());
        destroyTree(node->getRight());
        delete node;
    }
}

// Inserts a new song into the BST
void ArtistBST::insert(MusicQueueNode* data) {
    root = insertRecursive(root, data->getArtist(), data->getTitle(), data->getRunTime());
}

// Private recursive function for insertion
ArtistBSTNode* ArtistBST::insertRecursive(ArtistBSTNode* node, const string& artist, const string& title, const string& run_time) {
    if (node == nullptr) {
        return new ArtistBSTNode(artist, title, run_time);
    }
    
    if (artist < node->getArtist()) {
        node->setLeft(insertRecursive(node->getLeft(), artist, title, run_time));
    } else if (artist > node->getArtist()) {
        node->setRight(insertRecursive(node->getRight(), artist, title, run_time));
    } else {
        node->addSong(title, run_time);
    }
    return node;
}

// Searches for an artist and prints all their songs
bool ArtistBST::search(const string& artist) {
    ArtistBSTNode* current = root;
    while (current != nullptr) {
        if (current->getArtist() == artist) {
            cout << "========SEARCH========" << endl;
            const vector<string>& titles = current->getTitles();
            const vector<string>& runTimes = current->getRunTimes();
            for (size_t i = 0; i < titles.size(); ++i) {
                cout << current->getArtist() << "/" << titles[i] << "/" << runTimes[i] << endl;
            }
            cout << "====================" << endl;
            return true;
        } else if (artist < current->getArtist()) {
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

// Searches for a specific song by artist and title
bool ArtistBST::search_song(const string& artist, const string& title) {
    ArtistBSTNode* current = root;
    while (current != nullptr) {
        if (current->getArtist() == artist) {
            const vector<string>& titles = current->getTitles();
            const vector<string>& runTimes = current->getRunTimes();
            for (size_t i = 0; i < titles.size(); ++i) {
                if (titles[i] == title) {
                    cout << "========SEARCH========" << endl;
                    cout << current->getArtist() << "/" << titles[i] << "/" << runTimes[i] << endl;
                    cout << "====================" << endl;
                    return true;
                }
            }
            break;
        } else if (artist < current->getArtist()) {
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

// In-order traversal to print all songs in the BST
bool ArtistBST::print_inorder() {
    if (root == nullptr) {
        return false;
    }
    printInorderRecursive(root);
    return true;
}

void ArtistBST::printInorderRecursive(ArtistBSTNode* node) {
    if (node) {
        printInorderRecursive(node->getLeft());
        const vector<string>& titles = node->getTitles();
        const vector<string>& runTimes = node->getRunTimes();
        for (size_t i = 0; i < titles.size(); ++i) {
            cout << node->getArtist() << "/" << titles[i] << "/" << runTimes[i] << endl;
        }
        printInorderRecursive(node->getRight());
    }
}

// Deletes a node (artist) from the BST
bool ArtistBST::delete_node_artist(const string& artist) {
    ArtistBSTNode* oldRoot = root;
    root = deleteRecursive(root, artist);
    return oldRoot != root; // Check if the root has changed to determine if a deletion occurred
}

// Private recursive function for node deletion
ArtistBSTNode* ArtistBST::deleteRecursive(ArtistBSTNode* node, const string& artist) {
    if (node == nullptr) {
        return nullptr;
    }

    if (artist < node->getArtist()) {
        node->setLeft(deleteRecursive(node->getLeft(), artist));
    } else if (artist > node->getArtist()) {
        node->setRight(deleteRecursive(node->getRight(), artist));
    } else {
        // Node with only one child or no child
        if (node->getLeft() == nullptr) {
            ArtistBSTNode* temp = node->getRight();
            delete node;
            return temp;
        } else if (node->getRight() == nullptr) {
            ArtistBSTNode* temp = node->getLeft();
            delete node;
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        ArtistBSTNode* temp = findMin(node->getRight());

        node->setArtist(temp->getArtist());
        node->setTitles(temp->getTitles());
        node->setRunTimes(temp->getRunTimes());
        node->setCount(temp->getCount());

        node->setRight(deleteRecursive(node->getRight(), temp->getArtist()));
    }
    return node;
}

// Private helper function to find the minimum node in a BST subtree
ArtistBSTNode* ArtistBST::findMin(ArtistBSTNode* node) {
    ArtistBSTNode* current = node;
    while (current && current->getLeft() != nullptr) {
        current = current->getLeft();
    }
    return current;
}

// Deletes a song from the BST. If the artist has no more songs, the node is deleted.
bool ArtistBST::delete_node_song(const string& artist, const string& title) {
    ArtistBSTNode* current = root;
    while (current != nullptr) {
        if (current->getArtist() == artist) {
            if (current->removeSong(title)) {
                if (current->getCount() == 0) {
                    root = deleteRecursive(root, artist);
                }
                return true;
            }
            break;
        } else if (artist < current->getArtist()) {
            current = current->getLeft();
        } else {
            current = current->getRight();
        }
    }
    return false;
}

// New function to delete songs by title from ArtistBST
bool ArtistBST::delete_node_title(const string& title) {
    bool deleted = deleteNodeTitleRecursive(root, title);
    return deleted;
}

bool ArtistBST::deleteNodeTitleRecursive(ArtistBSTNode* node, const string& title) {
    if (node == nullptr) {
        return false;
    }

    bool left_deleted = deleteNodeTitleRecursive(node->getLeft(), title);
    bool right_deleted = deleteNodeTitleRecursive(node->getRight(), title);
    
    bool current_deleted = false;
    if (node->removeSong(title)) {
        current_deleted = true;
        if (node->getCount() == 0) {
            root = deleteRecursive(root, node->getArtist());
        }
    }
    return left_deleted || right_deleted || current_deleted;
}