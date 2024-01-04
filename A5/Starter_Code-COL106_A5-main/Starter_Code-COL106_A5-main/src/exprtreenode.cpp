/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode() {
    type = "\0";
    id = "\0";
    num = -1;
    left = NULL;
    right = NULL;
}

ExprTreeNode::ExprTreeNode(string t, int v) {
    type = t;
    id = "\0";
    num = v;
    left = NULL;
    right = NULL;    
}

ExprTreeNode::~ExprTreeNode(){

}

