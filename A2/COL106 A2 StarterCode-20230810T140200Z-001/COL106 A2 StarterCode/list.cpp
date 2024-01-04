#include <iostream> 
#include "list.h"
#include "node.h"

using namespace std;
 
    List :: List() {
        size = 0;
        sentinel_head = new Node(true);
        sentinel_tail = new Node(true);
        sentinel_head -> next = sentinel_tail;
        sentinel_head -> prev = nullptr;
        sentinel_tail -> prev = sentinel_head;
        sentinel_tail -> next = nullptr;
    }

    List :: ~List() {
        Node* temp = sentinel_head -> next;
        Node* ptr = temp -> next;
        while(temp != sentinel_tail or ptr != nullptr) {
            sentinel_head -> next = ptr;
            ptr -> prev = sentinel_head;
            delete temp;
            temp = ptr;
            ptr = ptr -> next;

        }
        delete sentinel_head;
        delete sentinel_tail;
    }

    void List :: insert(int v) {
        Node* newNode = new Node(v, nullptr, nullptr);
        
        newNode -> next = sentinel_tail;
        newNode -> prev = sentinel_tail -> prev;
        sentinel_tail -> prev = newNode;
        newNode -> prev -> next = newNode;

        size += 1;
    }

    int List :: delete_tail() {
        if (sentinel_tail -> prev == sentinel_head) {
            throw std::runtime_error("Empty Stack");
        }
        else {
            Node* temp = sentinel_tail -> prev;
            temp -> prev -> next = sentinel_tail;
            sentinel_tail -> prev = temp -> prev;
            int val = temp -> get_value();
            delete temp; 
            size -= 1;
            return val;
        }
    }

    int List :: get_size() {
        return size;
    }
 
    Node* List :: get_head() {
        return sentinel_head;
    }
