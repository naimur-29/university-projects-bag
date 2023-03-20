#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node *next;

    Node() {
        this->next = NULL;
    }

    Node(int data) {
        this->data = data;
        this->next = NULL;
    }
};

class List {
public:
    Node* head;
    Node* tail;
    int length = 0;

    List() {
        this->head = NULL;
    }

    List(int val) {
        this->head = this->tail = new Node(val);
    }

    // Functions:
    int at(int index) {
        Node* temp = this->head;
        while(index--) {
            temp = temp->next;
        }

        return temp->data;
    }

    void push_front(int val) {        
        this->length++;
        if (this->head == NULL) {
            this->head = this->tail = new Node(val);
            return;
        }

        Node* temp = new Node(val);
        temp->next = this->head;
        this->head = temp;
    }

    void push_back(int val) {
        this->length++;
        if (this->head == NULL) {
            this->head = this->tail = new Node(val);
            return;
        }

        Node* temp = new Node(val);
        this->tail->next = temp;
        this->tail = temp;
    }

    void insert(int val, int pos) {
        if (pos == 0) {
            this->push_front(val);
        }
        else if (pos > -1 && pos < this->length) {
            Node* temp = this->head;
            pos--;
            while(pos--) {
                temp = temp->next;
            }

            Node* temp2 = new Node(val);
            temp2->next = temp->next;
            temp->next = temp2;
        }
    }
};

int main() {
    List list;

    for (int i = 0; i < 5; i++) {
        list.push_front(i+1);
    }

    for (int i = 0; i < 5; i++) {
        list.push_back(i+1);
    }

    list.insert(0, list.length/2);

    for (Node* i = list.head; i != NULL; i = i->next) {
        cout << i->data << " ";
    }

    return 0;
}