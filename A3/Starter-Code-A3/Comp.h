#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Comp : public BaseClass {
public:
    Comp();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    std::vector<int> balances;
    std::vector<int>::iterator find(std::vector<int>& v, int val) {
        std::vector<int>::iterator itr = v.begin();

        while (itr != v.end()) {
            if (*itr == val) {
                return itr;
            }
            else {
                itr++;
            }
        }
        return itr;
    }
    int pow(int x, int i) {
        if (i == 0) {
            return 1;
        }
        else {
            if (i%2 == 0) {
                return pow(x, i/2)*pow(x, i/2);
            }
            else {
                return x*pow(x, i/2)*pow(x, i/2);
            }
        }
    }
    // Other data members and functions specific to Your implementation
};

#endif // COMP_H
