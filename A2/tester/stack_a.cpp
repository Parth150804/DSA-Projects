#include <iostream>
#include <stdexcept>
#include "stack_a.h"

using namespace std;
 
    Stack_A :: Stack_A() { 
        size = 0; 
    }

    void Stack_A :: push(int data) {
        if (size == 1024) {
            throw std::runtime_error("Stack Full");
        }
        else {
            stk[size++] = data;
        }
    }

    int Stack_A :: pop() {
        if (size == 0) {
            throw std::runtime_error("Empty Stack");
        }
        else {
            return stk[--size];
        }
    }

    int Stack_A :: get_element_from_top(int idx) {
        if (idx >= size or idx < 0) {
            throw std::runtime_error("Index out of range");
        }
        else {
            return stk[size - idx - 1];
        }
    }

    int Stack_A :: get_element_from_bottom(int idx) {
        if (idx >= size or idx < 0) {
            throw std::runtime_error("Index out of range");
        }
        else {
            return stk[idx];
        }
    }

    void Stack_A :: print_stack(bool top_or_bottom) {
        if (size == 0) {
            return;
        }
        else {
            if (top_or_bottom == 0) {
                for (int i = 0; i < size; i++) {
                    std::cout << stk[i] << "\n";
                }
        }
            else {
                for (int i = 0; i < size; i++) {
                    std::cout << stk[size - i - 1] << "\n";
                }
            }
        }    
    }

    int Stack_A :: add() {
        if (size == 0 or size == 1) {
            throw std::runtime_error("Not Enough Arguments");
        }
        else {
            int n1 = stk[--size];
            int n2 = stk[--size];
            stk[size++] = n1 + n2;
            return stk[size-1];
        }
    }

    int Stack_A :: subtract() {
        if (size == 0 or size == 1) {
            throw std::runtime_error("Not Enough Arguments");
        }
        else {
            int n1 = stk[--size];
            int n2 = stk[--size];
            stk[size++] = n2 - n1;
            return stk[size-1];
        }
    }

    int Stack_A :: multiply() {
        if (size == 0 or size == 1) {
            throw std::runtime_error("Not Enough Arguments");
        }
        else {
            int n1 = stk[--size];
            int n2 = stk[--size];
            stk[size++] = n1 * n2;
            return stk[size-1];
        }
    }

    int Stack_A :: divide() {
        if (size == 0 or size == 1) {
            throw std::runtime_error("Not Enough Arguments");
        }
        else {
            int n1 = stk[--size];
            int n2 = stk[--size];

            if (n1 == 0) {
                throw std::runtime_error("Division by zero Error");
            }
            else if ((n2%n1 == 0) or (n1 > 0 and n2 > 0) or (n2 < 0 and n1 < 0)) {
                stk[size++] = n2/n1;
                return stk[size-1];
            }
            else {
                stk[size++] = n2/n1 - 1;
                return stk[size-1];
            }  
        }
    }

    int* Stack_A :: get_stack() {
        return stk;
    }

    int Stack_A :: get_size() {
        return size;
    }
