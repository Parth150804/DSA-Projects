// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
const int N = 1e8 + 7;

class HashTable {
private:
    vector<vector<pair<string, int>>> table;

    unsigned long hashfunc(const std::string& str) {
        unsigned long hash = 5381;
        for (char c : str) {
            hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
        }
        return hash%N;
    }

public:
    HashTable() {
        table.resize(100000009);
    }

    bool isEqual(string s, string w) {
        if (s.length() != w.length()) {
            return false;
        }
        else {
            for (int i = 0; i < s.length(); i++) {
                if (s[i] != w[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    int searchWord(string w, const vector<pair<string, int>> &v) {
        for (int i = 0; i < v.size(); i++) {
            if (isEqual(w, v[i].first)) {
                return i;
            }
        }
        return -1;
    }

    void insertWord(string key) {
        if (key == "\0") {
            return;
        }
        for (int i = 0; i < key.length(); i++) {
            key[i] = tolower(key[i]);
        }
        unsigned long hashValue = hashfunc(key);
        int idx = searchWord(key, table[hashValue]);
        if (idx != -1) {
            table[hashValue][idx].second++;
        }
        else {
            table[hashValue].push_back(make_pair(key, 1));
        }
    }

    int freq(string w) {
        for (int i = 0; i < w.length(); i++) {
            w[i] = tolower(w[i]);
        }
        unsigned long hashValue = hashfunc(w);
        int idx = searchWord(w, table[hashValue]);
        if (idx == -1) {
            return 0;
        }
        else {
            return table[hashValue][idx].second;
        }
    }

    void write_to_file(string name) {      
        ofstream outputFilestream(name, ios::app);

        for (int i = 0; i < table.size(); i++) {
            for (int j = 0; j < table[i].size(); j++) {
                outputFilestream << table[i][j].first << ", " << table[i][j].second << "\n";
            }
        }

        outputFilestream.close();

    }
};

class Dict {
private:
    HashTable* Dictionary;
    // You can add attributes/helper functions here

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};