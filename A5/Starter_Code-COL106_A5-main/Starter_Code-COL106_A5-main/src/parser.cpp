/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    symtable = new SymbolTable();
}

ExprTreeNode* parent(ExprTreeNode* root, ExprTreeNode* ptr) {
    if (root == NULL or root == ptr) {
        return root;
    }
    
    if ((root -> left == ptr) or (root -> right == ptr)) {
        return root;
    }
    
    ExprTreeNode* left_parent = parent(root->left, ptr);
    if (left_parent != NULL) {
        return left_parent;
    }
    
    return parent(root->right, ptr);
}

bool isVar(string s) {
    for (char c : s) {
        if (std::isdigit(c)) {
            continue;
        }
        else {
            return true;
        }
    }
    return false;
}

ExprTreeNode* express_to_tree(vector<string> expression) {
    ExprTreeNode* root = new ExprTreeNode();
    ExprTreeNode* prev = root;
    ExprTreeNode* curr = root;
    string s1 = "+-/*";
    for (int i = 0; i < expression.size(); i++) {
        if (expression[i] == "(") {
            ExprTreeNode* child = new ExprTreeNode();
            curr -> left = child;
            prev = curr;
            curr = curr -> left;
        }
        else if (s1.find(expression[i]) != string::npos) {
            if (expression[i] == "+") {
                curr -> type = "ADD";
            }
            else if (expression[i] == "-") {
                curr -> type = "SUB";
            }
            else if (expression[i] == "*") {
                curr -> type = "MUL";
            }
            else {
                curr -> type = "DIV";
            }
            ExprTreeNode* child = new ExprTreeNode();
            curr -> right = child;
            prev = curr;
            curr = curr -> right;
        }
        else if (expression[i] == ")") {
            ExprTreeNode* par = parent(root, curr);
            if (par != NULL) {
                swap(par, curr);
            }
        }
        else if (isVar(expression[i])) {
            curr -> type = "VAR";
            curr -> id = expression[i];
            swap(prev, curr);
        }
        else {
            curr -> type = "VAL";
            curr -> num = stoi(expression[i]);
            swap(prev, curr);
        }
    }
    return curr;
}

void Parser::parse(vector<string> expression){
    ExprTreeNode* root = new ExprTreeNode();
    root -> id = expression[1];
    root -> type = "VAR";

    ExprTreeNode* left = new ExprTreeNode();
    left -> id = expression[0];
    if (expression[0] == "del") {
        left -> type = "DEL";
    }
    else if (expression[0] == "ret") {
        left -> type = "RET";
    }
    else {
        left -> type = "VAR";
    }

    root -> left = left;
    vector<string> v;
    for (int i = 2; i < expression.size(); i++) {
        v.push_back(expression[i]);
    }
    root -> right = express_to_tree(v);
    expr_trees.push_back(root);  
    ExprTreeNode* node = root -> left;
    if (node -> type == "DEL") {
        last_deleted = symtable -> search(expression[2]);
        symtable -> remove(expression[2]);
    }
    else if (node -> type == "RET") {
        return;
    }
    else {
        symtable -> insert(expression[0]);
    }
}

Parser::~Parser(){
    delete symtable;
}