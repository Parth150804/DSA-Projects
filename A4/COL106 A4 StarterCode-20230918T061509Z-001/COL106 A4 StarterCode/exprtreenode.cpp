/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode() {
    type = "VAR";
    val = new UnlimitedRational();
    evaluated_value = new UnlimitedRational();
    id = "\0";
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v) {
    type = t;
    UnlimitedInt* den = new UnlimitedInt(1);
    val = new UnlimitedRational(v, den);
    evaluated_value = new UnlimitedRational();
    id = "\0";
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v) {
    type = t;
    val = v;
    evaluated_value = new UnlimitedRational();
    id = "x";
    left = nullptr;
    right = nullptr;
}

ExprTreeNode::~ExprTreeNode() {
    delete val;
    delete evaluated_value;
}

