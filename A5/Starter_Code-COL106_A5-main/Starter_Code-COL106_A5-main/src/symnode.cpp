/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode() {
    key = "\0";
    height = 0;
    address = -1;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode::SymNode(string k) {
    key = k;
    height = 0;
    address = -1;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode::~SymNode() {
    
}

SymNode* SymNode::LeftLeftRotation() {
    SymNode* self = right -> par;
    SymNode* newRoot = right;
    right -> par = NULL;
    right = NULL;
    if (newRoot -> left) {
        newRoot -> left -> par = self;
    }
    self -> right = newRoot -> left;
    newRoot -> left = self;
    self -> par = newRoot;
    return newRoot;
}

SymNode* SymNode::RightRightRotation() {
    SymNode* self = left -> par;
    SymNode* newRoot = left;
    left -> par = NULL;
    left = NULL;
    if (newRoot -> right) {
        newRoot -> right -> par = self;
    }
    self -> left = newRoot -> right;
    newRoot -> right = self;
    self -> par = newRoot;
    return newRoot;
}

SymNode* SymNode::LeftRightRotation() {
    return NULL;
}

SymNode* SymNode::RightLeftRotation() {
    return NULL;
}
