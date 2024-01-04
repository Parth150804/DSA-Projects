/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
// #include <iostream>

SymbolTable::SymbolTable() {
    size = 0;
    root = nullptr;
}

void deletion(SymEntry* root) {
    if (root == nullptr) {
        return;
    }
    else {
        deletion(root -> right);
        deletion(root -> left);
        delete root;
    }
}
SymbolTable::~SymbolTable() {
    deletion(root);
}

void SymbolTable::insert(string k, UnlimitedRational* v) {
    if (root == nullptr) {
        root = new SymEntry(k, v);
        size++;
        return;
    }
    else {
        SymEntry* temp = root;
        while (temp -> left or temp -> right) {
            if (k > temp -> key) {
                if (temp -> right) {
                    temp = temp -> right;
                }
                else {
                    SymEntry* newNode = new SymEntry(k, v);
                    temp -> right = newNode;
                    size++;
                    return;
                }
            }
            else {
                if (temp -> left) {
                    temp = temp -> left;
                }
                else {
                    SymEntry* newNode = new SymEntry(k, v);
                    temp -> left = newNode;
                    size++;
                    return;            
                }
            }
        }
        if (temp -> key < k) {
            SymEntry* newNode = new SymEntry(k, v);
            temp -> right = newNode;
        }
        else {
            SymEntry* newNode = new SymEntry(k, v);
            temp -> left = newNode;
        }
        size++;
        return;
    }
}

UnlimitedRational* SymbolTable::search(string k) {
    if (root == nullptr) {
        return nullptr;
    }
    else {
        SymEntry* temp = root;
        while (temp != nullptr) {
            if (temp -> key > k) {
                temp = temp -> left;
            }
            else if (temp -> key < k) {
                temp = temp -> right;
            }
            else {
                return temp -> val;
            }
        }
        return nullptr;
    }
}


SymEntry* max(SymEntry* root) {
    if (root == nullptr) {
        return root;
    }
    else {
        SymEntry* temp = root;
        while (temp -> right != nullptr) {
            temp = temp -> right;
        }
        return temp;
    }
}

void SymbolTable::remove(string k) {
    SymEntry* temp = root;
    SymEntry* parent = root;
    while (temp != nullptr and temp -> key != k) {
        if (k > temp -> key) {
            parent = temp;
            temp = temp -> right;
        }
        else {
            parent = temp;
            temp = temp -> left;
        }
    }
    if (temp and temp -> key == k) {
        if (!temp -> right and !temp -> left) {
            if (parent -> left == temp) {
                parent -> left = nullptr;
                delete temp;
            }
            else {
                parent -> right = nullptr;
                delete temp;
            }
            size--;
            return;
        }
        else if (temp -> right == nullptr and temp -> left != nullptr) {
            if (parent -> left == temp) {
                parent -> left = temp -> left;
                delete temp;
            }
            else {
                parent -> right = temp -> left;
                delete temp;
            }
            size--;
            return;   
        }
        else if (temp -> left == nullptr and temp -> right != nullptr) {
            if (parent -> left == temp) {
                parent -> left = temp -> right;
                delete temp;
            }
            else if (parent -> right == temp) {
                parent -> right = temp -> right;
                delete temp;
            }
            else {
                if (temp -> left) {
                    SymEntry* pred = max(temp -> left);
                    swap(pred -> key, temp -> key);
                    remove(pred -> key);
                    return;  
                }
                else {
                    temp = temp -> right;
                    root = temp;
                    delete parent;
                }
            }
            size--;
            return;
        }
        else {
            SymEntry* pred = max(temp -> left);
            swap(pred -> key, temp -> key);
            remove(pred -> key);
        }
    }
    else {
        if (root != nullptr and root -> key == k) {
            root = nullptr;
            delete temp;
        }
        else {
            return;
        }
    }
}

int SymbolTable::get_size() {
    return size;
}

SymEntry* SymbolTable::get_root() {
    return root;
}

// int main() {
//     SymbolTable* Sym = new SymbolTable();
//     UnlimitedRational* i1 = new UnlimitedRational(new UnlimitedInt(4), new UnlimitedInt(1));
//     Sym -> insert("a", i1);
//     UnlimitedRational* i2 = new UnlimitedRational(new UnlimitedInt(81), new UnlimitedInt(9));
//     Sym -> insert("b", i2);
//     std::cout << Sym -> get_size() << "\n";
//     SymEntry* root = Sym -> get_root();
//     std::cout << root -> val -> get_frac_str() << "\n";
//     std::cout << root -> right -> val -> get_frac_str() << "\n";
//     std::cout << Sym -> search("a") -> get_frac_str() << "\n";
//     Sym -> remove("a");
//     std::cout << Sym -> get_size() << "\n";
// }