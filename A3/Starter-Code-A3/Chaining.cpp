#include "Chaining.h"

Chaining::Chaining() {
    bankStorage2d.resize(100003);
}

void Chaining::createAccount(std::string id, int count) {
    Account ac;
    ac.id = id;
    ac.balance = count;

    int hashvalue = hash(id);
    
    bankStorage2d[hashvalue].push_back(ac);

    std::vector<int>::iterator itr = std::lower_bound(balances.begin(), balances.end(), ac.balance);
    balances.insert(itr, ac.balance);
}

std::vector<int> Chaining::getTopK(int k) {
    std::vector<int> ans;
    int i = balances.size()-1;
    while (k > 0 and i >= 0) {
        ans.push_back(balances[i]);
        k--;
        i--;
    }
    return ans;
}

int Chaining::getBalance(std::string id) {
    int hashvalue = hash(id);

    int i = 0;
    while (i < bankStorage2d[hashvalue].size()) {
        if (bankStorage2d[hashvalue][i].id == id) {
            return bankStorage2d[hashvalue][i].balance;
        }
        else {
            i++;
        }
    }

    return -1;
}

void Chaining::addTransaction(std::string id, int count) {
    int hashvalue = hash(id);

    int i = 0;

    while (i < bankStorage2d[hashvalue].size()) {
        if (bankStorage2d[hashvalue][i].id == id) {
            std::vector<int>::iterator itr1 = Chaining::find(balances, bankStorage2d[hashvalue][i].balance);
            balances.erase(itr1);

            bankStorage2d[hashvalue][i].balance += count;

            std::vector<int>::iterator itr2 = std::lower_bound(balances.begin(), balances.end(), bankStorage2d[hashvalue][i].balance);
            balances.insert(itr2, bankStorage2d[hashvalue][i].balance);
            return;
        }
        else {
            i++;
        }
    }

    Account ac;
    ac.balance = count;
    ac.id = id;

    bankStorage2d[hashvalue].push_back(ac);

    std::vector<int>::iterator itr = std::lower_bound(balances.begin(), balances.end(), ac.balance);
    balances.insert(itr, ac.balance);
    return;
}

bool Chaining::doesExist(std::string id) {
    int hashvalue = hash(id);

    int i = 0;
    while (i < bankStorage2d[hashvalue].size()) {
        if (bankStorage2d[hashvalue][i].id == id) {
            return true;
        }
        else {
            i++;
        }
    }

    return false;
}

bool Chaining::deleteAccount(std::string id) {
    int hashvalue = hash(id);

    int i = 0;
    while (i < bankStorage2d[hashvalue].size()) {
        if (bankStorage2d[hashvalue][i].id == id) {
            std::vector<int>::iterator itr1 = Chaining::find(balances, bankStorage2d[hashvalue][i].balance);
            balances.erase(itr1);

            bankStorage2d[hashvalue].erase(bankStorage2d[hashvalue].begin() + i);
            return true;
        }
        else {
            i++;
        }
    }

    return false;
}

int Chaining::databaseSize() {
    return balances.size();
}

int Chaining::hash(std::string id) {
    int hashvalue = 0;
    int i = 1;
    for (char c : id) {
        hashvalue += static_cast<int>(c*i*(i+3)*(i+7));
        i++;
    }
    return hashvalue%100003;
}

