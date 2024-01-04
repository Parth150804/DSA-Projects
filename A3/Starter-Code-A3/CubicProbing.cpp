#include "CubicProbing.h"

CubicProbing::CubicProbing() {
    bankStorage1d.resize(100003);
}

void CubicProbing::createAccount(std::string id, int count) {
    Account ac;
    ac.id = id;
    ac.balance = count;

    int probe = hash(id);

    std::vector<int>::iterator itr = std::lower_bound(balances.begin(), balances.end(), ac.balance);
    balances.insert(itr, ac.balance);
    
    if (bankStorage1d[probe].id == "\0" or bankStorage1d[probe].id == "DELETED") {
        bankStorage1d[probe] = ac;
    }
    else {
        int i = 1;
        while (bankStorage1d[(probe+i*i*i)%100003].id != "\0" and bankStorage1d[(probe+i*i*i)%100003].id != "DELETED") {
            i++;
        }
        bankStorage1d[(probe+i*i*i)%100003] = ac;
    }
}

std::vector<int> CubicProbing::getTopK(int k) {
    std::vector<int> ans;
    int i = balances.size()-1;
    while (k > 0 and i >= 0) {
        ans.push_back(balances[i]);
        k--;
        i--;
    }
    return ans;
}

int CubicProbing::getBalance(std::string id) {
    int hashvalue = hash(id);
    if (bankStorage1d[hashvalue].id == "\0") {
        return -1;
    }
    else {
        if (bankStorage1d[hashvalue].id == id) {
            return bankStorage1d[hashvalue].balance;
        }
        else {
            int probe = (hashvalue)%100003;
            int i = 0;

            while (bankStorage1d[(probe+i*i*i)%100003].id != "\0") {
                if (bankStorage1d[(probe+i*i*i)%100003].id == id) {
                    return bankStorage1d[(probe+i*i*i)%100003].balance;
                }
                else {
                    i++;
                }
            }

            return -1;
        }
    }
}

void CubicProbing::addTransaction(std::string id, int count) {
    int hashvalue = hash(id);

    if (bankStorage1d[hashvalue].id == id) {
        std::vector<int>::iterator itr1 = CubicProbing::find(balances, bankStorage1d[hashvalue].balance);
        balances.erase(itr1);

        bankStorage1d[hashvalue].balance += count;

        std::vector<int>::iterator itr2 = std::lower_bound(balances.begin(), balances.end(), bankStorage1d[hashvalue].balance);
        balances.insert(itr2, bankStorage1d[hashvalue].balance);
        return;
    }

    int probe = (hashvalue)%100003;
    int i = 0;
    while (bankStorage1d[(probe+i*i*i)%100003].id != "\0") {
        if (bankStorage1d[(probe+i*i*i)%100003].id == id) {
            std::vector<int>::iterator itr1 = CubicProbing::find(balances, bankStorage1d[(probe+i*i*i)%100003].balance);
            balances.erase(itr1);

            bankStorage1d[(probe+i*i*i)%100003].balance += count;

            std::vector<int>::iterator itr2 = std::lower_bound(balances.begin(), balances.end(), bankStorage1d[(probe+i*i*i)%100003].balance);
            balances.insert(itr2, bankStorage1d[(probe+i*i*i)%100003].balance);
            return;
        }
        else {
            i++;
        }
    }

    Account ac;
    ac.balance = count;
    ac.id = id;

    bankStorage1d[(probe+i*i*i)%100003] = ac;

    std::vector<int>::iterator itr = std::lower_bound(balances.begin(), balances.end(), ac.balance);
    balances.insert(itr, ac.balance);
    return;
}

bool CubicProbing::doesExist(std::string id) {
    int hashvalue = hash(id);
    if (bankStorage1d[hashvalue].id == "\0") {
        return false;
    }
    else {
        if (bankStorage1d[hashvalue].id == id) {
            return true;
        }
        else {
            int probe = (hashvalue)%100003;
            int i = 0;

            while (bankStorage1d[(probe+i*i*i)%100003].id != "\0") {
                if (bankStorage1d[(probe+i*i*i)%100003].id == id) {
                    return true;
                }
                else {
                    i++;
                }
            }
            return false;
        }
    }
}

bool CubicProbing::deleteAccount(std::string id) {
    int hashvalue = hash(id);

    if (bankStorage1d[hashvalue].id == "\0") {
        return false;
    }
    else {
        if (bankStorage1d[hashvalue].id == id) {

            std::vector<int>::iterator itr1 = CubicProbing::find(balances, bankStorage1d[hashvalue].balance);
            balances.erase(itr1);

            bankStorage1d[hashvalue].balance = 0;
            bankStorage1d[hashvalue].id = "DELETED";

            return true;
        }
        else {
            int probe = (hashvalue)%100003;
            int i = 0;
            while (bankStorage1d[(probe+i*i*i)%100003].id != "\0") {
                if (bankStorage1d[(probe+i*i*i)%100003].id == id) {
                    std::vector<int>::iterator itr1 = CubicProbing::find(balances, bankStorage1d[(probe+i*i*i)%100003].balance);
                    balances.erase(itr1);

                    bankStorage1d[(probe+i*i*i)%100003].balance = 0;
                    bankStorage1d[(probe+i*i*i)%100003].id = "DELETED";

                    return true;
                }
                else {
                    i++;
                }
            }
            return false;
        }
    }
}

int CubicProbing::databaseSize() {
    return balances.size();
}

int CubicProbing::hash(std::string id) {
    int hashvalue = 0;
    int i = 1;
    for (char c : id) {
        hashvalue += static_cast<int>(c*i*(i+3)*(i+7));
        i++;
    }
    return hashvalue%100003;
}