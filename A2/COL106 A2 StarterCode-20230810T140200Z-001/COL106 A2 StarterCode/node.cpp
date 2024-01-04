#include <iostream>
#include <stdexcept>
#include "node.h"

using namespace std;

    Node :: Node(bool sentinel) {
        is_sentinel = sentinel;
        next = nullptr;
        prev = nullptr;
    }

    Node :: Node(int v, Node* nxt, Node* prv) {
        value = v;
        is_sentinel = false;
        next = nxt;
        prev = prv;
    }

    bool Node :: is_sentinel_node() {
        if (is_sentinel == true) {
            return true;
        }
        else {
            return false;
        }
    }

    int Node :: get_value() {
        if (is_sentinel == false) {
            return value;
        }
        else {
            return -1;
        }
    }
