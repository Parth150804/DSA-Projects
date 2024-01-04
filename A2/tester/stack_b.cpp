#include <iostream>
#include <stdexcept>
#include "stack_b.h"

using namespace std;

    Stack_B :: Stack_B() {
        size = 0;
        stk = new int[1024];
        capacity = 1024;
    }

    Stack_B :: ~Stack_B() {
        delete[] stk;
    }

    void Stack_B :: push(int data) {
        if (size == capacity/2) {

            try {
                int* temp = new int[capacity*2];
                delete[] temp;
            }
            catch (const std::bad_alloc&) {
                throw std::runtime_error("Out of Memory");
            }

            int* temp = new int[capacity*2];

            for (int i = 0; i < size; i++) {
                    temp[i] = stk[i];
                }

                delete[] stk;
                stk = temp;
                capacity *= 2;
        }

        stk[size++] = data;
    }

    int Stack_B :: pop() {
        if (size == 0) {
            throw std::runtime_error("Empty Stack");
        }

        else if (size < capacity/4 and capacity/4 >= 1024) {
            int* temp = new int[capacity/2];
            for (int i = 0; i < size; i++) {
                temp[i] = stk[i];
            }
            delete[] stk;
            stk = temp;
            capacity /= 2;
        }

        int result = stk[size-1];
        size--;
        return result;
    }

    int Stack_B :: get_element_from_top(int idx) {
        if (idx >= size or idx < 0) {
            throw std::runtime_error("Index out of range");
        }
        else {
            return stk[size - idx - 1];
        }
    }

    int Stack_B :: get_element_from_bottom(int idx) {
        if (idx >= size or idx < 0) {
            throw std::runtime_error("Index out of range");
        }
        else {
            return stk[idx];
        }
    }

    void Stack_B :: print_stack(bool top_or_bottom) {
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

    int Stack_B :: add() {
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
    int Stack_B :: subtract() {
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

    int Stack_B :: multiply() {
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
    int Stack_B :: divide() {
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

    int* Stack_B :: get_stack() {
        return stk;
    }

    int Stack_B :: get_size() {
        return size;
    }
