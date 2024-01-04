/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
#include <iostream>

Evaluator::Evaluator() {
    symtable = new SymbolTable();
}

Evaluator::~Evaluator() {
    for (int i = 0; i < expr_trees.size(); i++) {
        delete expr_trees[i];
    }
    delete symtable;
}

// ExprTreeNode* tree_maker(string a, string b, string c) {
//     string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//     ExprTreeNode* root = new ExprTreeNode();
//     if (b == "+") {
//         root -> type = "ADD";
//     }
//     else if (b == "-") {
//         root -> type = "SUB";
//     }
//     else if (b == "*") {
//         root -> type = "MUL";
//     }
//     else {
//         root -> type = "DIV";
//     }

//     if (s.find(a) != string::npos) {
//         ExprTreeNode* left = new ExprTreeNode();
//         left -> id = a;
//         left -> type = "VAR";
//         root -> left = left;
//     }
//     else {
//         UnlimitedRational* n1;
//         n1 = new UnlimitedRational(new UnlimitedInt(a), new UnlimitedInt("1"));
//         ExprTreeNode* left = new ExprTreeNode("VAL", n1);
//         root -> left = left;
//     }
//     if (s.find(c) != string::npos) {
//         ExprTreeNode* right = new ExprTreeNode();
//         right -> id = c;
//         right -> type = "VAR";
//         root -> right = right;
//     }
//     else {
//         UnlimitedRational* n2;
//         n2 = new UnlimitedRational(new UnlimitedInt(c), new UnlimitedInt("1"));
//         ExprTreeNode* right = new ExprTreeNode("VAL", n2);
//         root -> right = right;
//     }
//     return root;
// }

// ExprTreeNode* combiner(string a, string b, ExprTreeNode* node) {
//     string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//     ExprTreeNode* root = new ExprTreeNode();
//     if (b == "+") {
//         root -> type = "ADD";
//     }
//     else if (b == "-") {
//         root -> type = "SUB";
//     }
//     else if (b == "*") {
//         root -> type = "MUL";
//     }
//     else {
//         root -> type = "DIV";
//     }

//     if (s.find(a) != string::npos) {
//         ExprTreeNode* left = new ExprTreeNode();
//         left -> id = a;
//         left -> type = "VAR";
//         root -> left = left;
//     }
//     else {
//         UnlimitedRational* n1;
//         n1 = new UnlimitedRational(new UnlimitedInt(a), new UnlimitedInt("1"));
//         ExprTreeNode* left = new ExprTreeNode("VAL", n1);
//         root -> left = left;
//     }

//     root -> right = node;
//     return root;
// }

// void Evaluator::parse(vector<string> code) { 
//     ExprTreeNode* root = new ExprTreeNode();
//     root -> type = "VAR";
//     root -> val = nullptr;
//     root -> id = ":=";
//     ExprTreeNode* left = new ExprTreeNode();
//     left -> type = "VAR";
//     left -> val = nullptr;
//     left -> id = code[0];

//     root -> left = left;
//     vector<string> token;
//     for (int i = 2; i < code.size(); i++) {
//         if (code[i] != "(" and code[i] != ")") {
//             token.push_back(code[i]);
//         }
//         else {
//             continue;
//         }
//     }
//     int n = token.size();
//     if (n > 1) {
//         ExprTreeNode* t;
//         ExprTreeNode* b = tree_maker(token[n-3], token[n-2], token[n-1]);
//         token.pop_back();
//         token.pop_back();
//         token.pop_back();
//         n -= 3;
//         while (n > 0) {
//             t = combiner(token[n-2], token[n-1], b);
//             b = t;
//             token.pop_back();
//             token.pop_back();
//             n -= 2;
//         }
//         root -> right = b;
//         expr_trees.push_back(root);
//     }
//     else {
//         string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";       
//         if (s.find(token[0]) != string::npos) {
//             ExprTreeNode* right = new ExprTreeNode();
//             right -> id = token[0];
//             right -> type = "VAR";
//             root -> right = right;
//         }
//         else {
//             UnlimitedRational* n1;
//             n1 = new UnlimitedRational(new UnlimitedInt(token[0]), new UnlimitedInt("1"));
//             ExprTreeNode* right = new ExprTreeNode("VAL", n1);
//             root -> right = right;
//         }
//         expr_trees.push_back(root);
//     }
// }

ExprTreeNode* parent(ExprTreeNode* root, ExprTreeNode* ptr) {
    if (root == nullptr or root == ptr) {
        return nullptr;
    }
    
    if ((root->left == ptr) or (root->right == ptr)) {
        return root;
    }
    
    ExprTreeNode* left_parent = parent(root->left, ptr);
    if (left_parent != nullptr) {
        return left_parent;
    }
    
    return parent(root->right, ptr);
}

ExprTreeNode* express_to_tree(vector<string> code) {
    ExprTreeNode* root = new ExprTreeNode();
    ExprTreeNode* prev = nullptr;
    ExprTreeNode* curr = root;
    string s1 = "+-/*";
    string s2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
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
        else if (s2.find(code[i]) != string::npos) {
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
            string st = root -> type;
            UnlimitedRational* a;
            UnlimitedRational* b;
            if (root -> left -> type != "VAR") {
                a = root -> left -> val;
            }
            else {
                a = s -> search(root -> left -> id);
            }
            if (root -> right -> type != "VAR") {
                b = root -> right -> val;
            }
            else {
                b = s -> search(root -> right -> id);
            }

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

int main() {
    Evaluator* E = new Evaluator();
    vector<string> code = {"v", ":=", "(", "13", "+", "(", "2", "/", "51", ")", ")"};
    E -> parse(code);
    E -> eval();
    ExprTreeNode* tree = E -> expr_trees[0];
    std::cout << tree -> evaluated_value -> get_frac_str() << "\n";
    // vector<string> code2 = {"g", ":=", "(", "2", "*", "v", ")"};
    // E -> parse(code2);
    // // ExprTreeNode* tree2 = E -> expr_trees[1];
    // // std::cout << tree2 -> right -> left -> val -> get_frac_str();
    // E -> eval();
    // // ExprTreeNode* tree2 = E -> expr_trees[1];
    // // std::cout << tree2 -> evaluated_value -> get_frac_str();
    // vector<string> code3 = {"x", ":=", "(", "g", "+", "6", ")"};
    // E -> parse(code3);
    // // ExprTreeNode* tree3 = E -> expr_trees[2];
    // // std::cout << tree3 -> right -> right -> val -> get_frac_str();
    // vector<string> code4 = {"y", ":=", "x"};
    // E -> parse(code4);
    // ExprTreeNode* tree4 = E -> expr_trees[3];
    // std::cout << tree4 -> left -> id;  
}