#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }

    void traverse() {
        if (this->left != NULL) {
            this->left->traverse();
        }
        
        cout << this->data << endl;

        if (this->right != NULL){
            this->right->traverse();
        }
    }

    void insert(int data) {
        if (data < this->data) {
            if (this->left == NULL) {
                this->left = new Node(data);
            } else {
                this->left->insert(data);
            }
        } else {
            if (this->right == NULL) {
                this->right =new Node(data);
            } else {
                this->right->insert(data);
            }
        }
    }
};

class Tree {
public:
    Node* root;

    Tree() {
        this->root = NULL;
    }

    void traverse() {
        this->root->traverse();
    }

    void insert(int data) {
        if (this->root == NULL) {
            this->root = new Node(data);
            return;
        }

        this->root->insert(data);
    }
};

int main() {
    Tree* tree = new Tree();
    int arr[6] = {10, 23, 15, 5, 6, 12};

    for (int i = 0; i < 6; i++) {
        tree->insert(arr[i]);
    }

    tree->traverse();

    return 0;    
}