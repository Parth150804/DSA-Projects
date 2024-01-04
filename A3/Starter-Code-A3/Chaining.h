#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
public:
    Chaining();
    std::vector<int> balances;
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
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
    // Other data members and functions specific to Chaining
};

#endif // CHAINING_H
