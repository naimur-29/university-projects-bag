#include <iostream>

class Node {
public:
    int value;
    Node *next;

    Node() {
        this->next = NULL;
    }

    Node(int value) {
        this->value = value;
        this->next = NULL;
    }
};

class List {
public:
    Node* head;

    List() {
        this->head = NULL;
    }

    List(int val) {
        this->head = new Node(val);
    }

    void push_front(int val) {
        if (this->head == NULL) {
            this->head = new Node(val);
            return;
        }

        Node* temp = new Node(val);
        temp->next = head;
        this->head = temp;
    }

    void push_back(int val) {
        if (this->head == NULL) {
            this->head = new Node(val);
            return;
        }

        Node* temp = this->head;

        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new Node(val);
    }
};

int main() {
    List list;

    for (int i = 0; i < 10; i++) {
        list.push_front(110 - (i*10 + 10));
    }

    Node* current = list.head;
    while(current != NULL) {
        std::cout << current->value << std::endl;
        current = current->next;
    }

    return 0;
}