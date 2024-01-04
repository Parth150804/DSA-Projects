/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

SymbolTable::SymbolTable() {
    size = 0;
    root = new SymNode();
}

int height(SymNode* root) {
    if (root == NULL) {
        return 0;
    }
    else {
        return root -> height;
    }
}

void Balancing(SymNode** root) {
    if (!(*root) or (!(*root) -> left and !(*root) -> right)) {
        return;
    }
    else {
        int balance_factor = height((*root) -> right) - height((*root) -> left);
        if (balance_factor == 2) {
            if (height((*root) -> right -> right) >= height((*root) -> right -> left)) {
                (*root) = (*root) -> LeftLeftRotation();
            }
            else {
                (*root) -> right = (*root) -> right -> RightRightRotation();
                (*root) -> right -> par = (*root);
                (*root) = (*root) -> LeftLeftRotation();
            }
        }
        else if (balance_factor == -2) {
            if (height((*root) -> left -> left) >= height((*root) -> left -> right)) {
                (*root) = (*root) -> RightRightRotation();
            }
            else {
                (*root) -> left = (*root) -> left -> LeftLeftRotation();
                (*root) -> left -> par = (*root);
                (*root) = (*root) -> RightRightRotation();
            }
        }
        return;
    }
}

void Update_Height(SymNode* root) {
    if (root == NULL) {
        return;
    }
    else if (!root -> left and !root -> right) {
        root -> height = 1;
        return;
    }
    else {
        Update_Height(root -> right);
        Update_Height(root -> left);
        root -> height = 1 + max(height(root -> right), height(root -> left));
        return;
    }
}

void SymbolTable::insert(string k) {
    if (size == 0) {
        root -> key = k;
        root -> height = 1;
        size++;
        return;
    }
    else {
        SymNode* temp = root;
        SymNode* node = NULL;
        while (temp -> left or temp -> right) {
            if (k > temp -> key) {
                if (temp -> right) {
                    temp -> height++;
                    temp = temp -> right;
                }
                else {
                    break;
                }
            }
            else {
                if (temp -> left) {
                    temp -> height++;
                    temp = temp -> left;
                }
                else {
                    break;         
                }
            }
        }
        if (temp -> key < k) {
            SymNode* newNode = new SymNode(k);
            newNode -> height = 1;
            newNode -> par = temp;
            temp -> height++;
            temp -> right = newNode;
        }
        else if (temp -> key > k) {
            SymNode* newNode = new SymNode(k);
            newNode -> height = 1;
            newNode -> par = temp;
            temp -> height++;
            temp -> left = newNode;
        }
        size++;
        while (temp) {
            if (abs(height(temp -> right) - height(temp -> left)) > 1) {
                node = temp;
                temp = temp -> par;
                break;
            }
            else {
                temp = temp -> par;
            }
        }
        string s = "\0";
        if (node) {
            if (temp and temp -> left == node) {
                s = "left";
            }
            else if (temp and temp -> right == node) {
                s = "right";
            }
            Balancing(&node);
            Update_Height(node);
            if (temp) {
                node -> par = temp;
                if (s == "right") {
                    temp -> right = node;
                }
                else {
                    temp -> left = node;
                }
            }
            else {
                root = node;
            }
        }
        return;
    }
}

SymNode* min(SymNode* root) {
    if (root == NULL) {
        return root;
    }
    else {
        SymNode* temp = root;
        while (temp -> left != NULL) {
            temp = temp -> left;
        }
        return temp;
    }
}

void deletion(SymNode** root, string k, int &size) {
    if ((*root) -> key == "\0") {
        return;
    }
    else if (size == 1 and ((*root) -> key == k)) {
        (*root) -> key = "\0";
        (*root) -> height = 0;
        (*root) -> address = -1;
        (*root) -> par = NULL;
        (*root) -> left = NULL;
        (*root) -> right = NULL;
        size--;
        return;
    }
    SymNode* temp = (*root);
    while (temp != NULL and temp -> key != k) {
        if (k > temp -> key) {
            temp = temp -> right;
        }
        else {
            temp = temp -> left;
        }
    }
    if (temp == NULL) {
        return;
    }
    else {
        if (!temp -> right and !temp -> left) {
            if (temp -> par) {
                if (temp -> par -> right == temp) {
                    temp -> par -> right = NULL;
                }
                else {
                    temp -> par -> left = NULL;
                }
            }
            delete temp;
            size--;
        }
        else if (!temp -> right and temp -> left) {
            if (temp -> par) {
                if (temp -> par -> right == temp) {
                    temp -> par -> right = temp -> left;
                }
                else {
                    temp -> par -> left = temp -> left;
                    temp -> left -> par = temp -> par;
                }
            }
            else {
                (*root) = temp -> left;
                (*root) -> par = NULL;
            }
            delete temp;    
            size--;
        }
        else if (temp -> right and !temp -> left) {
            if (temp -> par) {
                if (temp -> par -> left == temp) {
                    temp -> par -> left = temp -> right;
                }
                else {
                    temp -> par -> right = temp -> right;
                    temp -> right -> par = temp -> par;
                }
            }
            else {
                (*root) = temp -> right;
                (*root) -> par = NULL;
            }
            delete temp;
            size--;
        }
        else {
            SymNode* succ = min(temp -> right);
            swap(succ -> key, temp -> key);
            deletion(&(temp -> right), succ -> key, size);
        }
        Balancing(root);
        Update_Height(*root);
        return;
    }
}

void SymbolTable::remove(string k) {
    deletion(&root, k, size);
}

int SymbolTable::search(string k) {
    if (root -> key == "\0") {
        return -2;
    }
    else {
        SymNode* temp = root;
        while (temp) {
            if (k > temp -> key) {
                temp = temp -> right;
            }
            else if (k < temp -> key) {
                temp = temp -> left;
            }
            else {
                return temp -> address;
            }
        }
        return -2;
    }
}

void SymbolTable::assign_address(string k, int idx) {
    if (root -> key == "\0") {
        return;
    }
    else {
        SymNode* temp = root;
        while (temp) {
            if (k > temp -> key) {
                temp = temp -> right;
            }
            else if (k < temp -> key) {
                temp = temp -> left;
            }
            else {
                temp -> address = idx;
                return;
            }
        }
        return;       
    }
}

int SymbolTable::get_size() {
    return size;
}

SymNode* SymbolTable::get_root() {
    return root;
}

void delete_table(SymNode* root) {
    if (root == NULL) {
        return;
    }
    else if (root -> left == NULL and root -> right == NULL) {
        delete root;
    }
    else {
        delete_table(root -> right);
        delete_table(root -> left);
        delete root;
    }
}

SymbolTable::~SymbolTable(){
    delete_table(root);
}

