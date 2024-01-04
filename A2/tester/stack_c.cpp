#include <iostream>
#include <stdexcept>
#include "stack_c.h"

using namespace std;

    Stack_C :: Stack_C() {
        stk = new List();
    }

    Stack_C :: ~Stack_C() {
        delete stk;
    }

    void Stack_C :: push(int data) {
        stk -> insert(data);
    }

    int Stack_C :: pop() {
        return stk -> delete_tail();
    }

    int Stack_C :: get_element_from_top(int idx) {
        if (idx >= stk -> get_size() or idx < 0) {
            throw std::runtime_error("Index out of range"); 
        }
        else {
            Node* temp = stk -> get_head() -> next;
            int size = stk -> get_size();
            int count = 0;
            while (count < size-1-idx) {
                temp = temp -> next;
                count++;
            }

            return temp -> get_value();
        }
    }

    int Stack_C :: get_element_from_bottom(int idx) {
        if (idx >= stk -> get_size() or idx < 0) {
            throw std::runtime_error("Index out of range"); 
        }
        else {
            Node* temp = stk -> get_head() -> next;
            int size = stk -> get_size();
            int count = 0;
            while (count < idx) {
                temp = temp -> next;
                count++;
            }

            return temp -> get_value();
        }
    }

    void Stack_C :: print_stack(bool top_or_bottom) {
        int n = stk -> get_size();
        if (n == 0) {
            return;
        }
        else {
            if (top_or_bottom == 0) {
                Node* temp = stk -> get_head();
                while (temp -> next != nullptr) {
                    std::cout << temp -> get_value() << "\n";
                    temp = temp -> next;
                }
            }
            else {
                Node* temp = stk -> get_head() -> next;
                int count = 0;
                while(count < n - 1) {
                    temp = temp -> next;
                    count++;
                }

                while(temp -> prev != stk -> get_head()) {
                    std::cout << temp -> get_value() << "\n";
                    temp = temp -> prev;
                }
            }
        }
    }

    int Stack_C :: add() {
        int n = stk -> get_size();
        if (n == 0 or n == 1) {
            throw std::runtime_error("Not Enough Arguments");
        }
        else {
            int n1 = stk -> delete_tail();
            int n2 = stk -> delete_tail();
            stk -> insert(n1+n2);
            return n1+n2;
        }
    }

    int Stack_C :: subtract() {
        int n = stk -> get_size();
        if (n == 0 or n == 1) {
            throw std::runtime_error("Not Enough Arguments");
        }
        else {
            int n1 = stk -> delete_tail();
            int n2 = stk -> delete_tail();
            stk -> insert(n2-n1);
            return n2-n1;
        }
    }

    int Stack_C :: multiply() {
        int n = stk -> get_size();
        if (n == 0 or n == 1) {
            throw std::runtime_error("Not Enough Arguments");
        }
        else {
            int n1 = stk -> delete_tail();
            int n2 = stk -> delete_tail();
            stk -> insert(n1*n2);
            return n2*n1;
        }
    }

    int Stack_C :: divide() {
        int n = stk -> get_size();
        if (n == 0 or n == 1) {
            throw std::runtime_error("Not Enough Arguments");
        }
        else {
            int n1 = stk -> delete_tail();
            int n2 = stk -> delete_tail();

            if (n1 == 0) {
                throw std::runtime_error("Division by zero Error");
            }
            else if ((n2%n1 == 0) or (n1 > 0 and n2 > 0) or (n2 < 0 and n1 < 0)) {
                stk -> insert(n2/n1);
                return n2/n1;
            }
            else {
                stk -> insert(n2/n1 - 1);
                return n2/n1 - 1;
            }
        }
    } 

    List* Stack_C :: get_stack() {
        return stk;
    }

    int Stack_C :: get_size() {
        return stk -> get_size();
    }

