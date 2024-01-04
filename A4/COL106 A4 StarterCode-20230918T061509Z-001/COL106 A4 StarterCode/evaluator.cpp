/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
// #include <iostream>

Evaluator::Evaluator() {
    symtable = new SymbolTable();
}

Evaluator::~Evaluator() {
    for (int i = 0; i < expr_trees.size(); i++) {
        delete expr_trees[i];
    }
    delete symtable;
}

ExprTreeNode* parent(ExprTreeNode* root, ExprTreeNode* ptr) {
    if (root == nullptr or root == ptr) {
        return root;
    }
    
    if ((root -> left == ptr) or (root -> right == ptr)) {
        return root;
    }
    
    ExprTreeNode* left_parent = parent(root->left, ptr);
    if (left_parent != nullptr) {
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

ExprTreeNode* express_to_tree(vector<string> code) {
    ExprTreeNode* root = new ExprTreeNode();
    ExprTreeNode* prev = root;
    ExprTreeNode* curr = root;
    string s1 = "+-/*";
    for (int i = 0; i < code.size(); i++) {
        if (code[i] == "(") {
            ExprTreeNode* child = new ExprTreeNode();
            curr -> left = child;
            prev = curr;
            curr = curr -> left;
        }
        else if (s1.find(code[i]) != string::npos) {
            if (code[i] == "+") {
                curr -> type = "ADD";
            }
            else if (code[i] == "-") {
                curr -> type = "SUB";
            }
            else if (code[i] == "*") {
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
        else if (code[i] == ")") {
            ExprTreeNode* par = parent(root, curr);
            if (par != nullptr) {
                swap(par, curr);
            }
        }
        else if (isVar(code[i])) {
            curr -> type = "VAR";
            curr -> id = code[i];
            swap(prev, curr);
        }
        else {
            curr -> type = "VAL";
            curr -> val = new UnlimitedRational(new UnlimitedInt(code[i]), new UnlimitedInt("1"));
            swap(prev, curr);
        }
    }
    return curr;
}

void Evaluator::parse(vector<string> code) { 
    ExprTreeNode* root = new ExprTreeNode();
    root -> id = code[1];
    root -> type = "VAR";

    ExprTreeNode* left = new ExprTreeNode();
    left -> id = code[0];
    left -> type = "VAR";

    root -> left = left;
    vector<string> v;
    for (int i = 2; i < code.size(); i++) {
        v.push_back(code[i]);
    }
    root -> right = express_to_tree(v);
    expr_trees.push_back(root);
}

void calculator(ExprTreeNode* root, SymbolTable* s) {
    if (root == nullptr) {
        return;
    }
    else {
        if (root -> left == nullptr and root -> right == nullptr) {
            if (root -> type != "VAR") {
                root -> evaluated_value = root -> val;
                return;
            }
            else {
                root -> evaluated_value = s -> search(root -> id);
                return;
            }
        }
        else {
            calculator(root -> right, s);
            calculator(root -> left, s);
            string st = root -> type;
            UnlimitedRational* a = root -> left -> evaluated_value;
            UnlimitedRational* b = root -> right -> evaluated_value;

            if (st == "ADD") {
                root -> evaluated_value = UnlimitedRational::add(a, b);
            }
            else if (st == "SUB") {
                root -> evaluated_value = UnlimitedRational::sub(a, b);
            }
            else if (st == "MUL") {
                root -> evaluated_value = UnlimitedRational::mul(a, b);
            }
            else {
                root -> evaluated_value = UnlimitedRational::div(a, b);
            }
            root -> type = "VAL";
            root -> val = root -> evaluated_value;
            return;
        }
    }
}

void Evaluator::eval() {
    ExprTreeNode* Tree = expr_trees[expr_trees.size() - 1];
    calculator(Tree -> right, symtable);
    Tree -> evaluated_value = Tree -> right -> evaluated_value;
    symtable -> insert(Tree -> left -> id, Tree -> right -> evaluated_value);
}

// int main() {
//     Evaluator* E = new Evaluator();
//     vector<string> code = {"pow1", ":=", "13"};
//     E -> parse(code);
//     E -> eval();
//     // ExprTreeNode* tree = E -> expr_trees[0];
//     // std::cout << tree -> evaluated_value -> get_frac_str() << "\n";
//     vector<string> code2 = {"pow2", ":=", "(", "(", "2", "*", "42", ")", "/", "(", "pow1", "*", "pow1", ")", ")"};
//     E -> parse(code2);
//     // ExprTreeNode* tree2 = E -> expr_trees[1];
//     // std::cout << tree2 -> right -> left -> left -> val -> get_frac_str();
//     E -> eval();
//     vector<string> code2 = {"pow2", ":=", "(", "(", "2", "*", "42", ")", "/", "(", "pow1", "*", "pow1", ")", ")"};
//     E -> parse(code2);
//     vector<string> code2 = {"pow2", ":=", "(", "(", "2", "*", "42", ")", "/", "(", "pow1", "*", "pow1", ")", ")"};
//     E -> parse(code2);
// }