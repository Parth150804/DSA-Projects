// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
const int N = 1e7 + 7;
const int M = 1e6 + 7;

class HashTable {
private:
    vector<vector<pair<string, long long>>> table;

    unsigned long hashfunc(const std::string& str) {
        unsigned long hash = 5381;
        for (char c : str) {
            hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
        }
        return hash%N;
    }

public:
    HashTable() {
        table.resize(10000009);
    }

    bool isEqual(string s, string w) {
        if (s.length() != w.length()) {
            return false;
        }
        else {
            for (size_t i = 0; i < s.length(); i++) {
                if (s[i] != w[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    int searchWord(string w, const vector<pair<string, long long>> &v) {
        for (size_t i = 0; i < v.size(); i++) {
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
        for (size_t i = 0; i < key.length(); i++) {
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
        for (size_t i = 0; i < w.length(); i++) {
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
};

class csv_counter{
private:
    vector<vector<pair<string, long long>>> htable;

    unsigned long hashfunc(const std::string& str) {
        unsigned long hash = 5381;
        for (char c : str) {
            hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
        }
        return hash%M;
    }

public: 
    csv_counter(){
        htable.resize(1e6+9);
    }
    
    bool isEqual(string s, string w) {
        if (s.length() != w.length()) {
            return false;
        }
        else {
            for (size_t i = 0; i < s.length(); i++) {
                if (s[i] != w[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    void insert(string word, long long count){
        int hash_id = hashfunc(word);
        htable[hash_id].push_back(make_pair(word, count));
    }

    int searchWord(string w, const vector<pair<string, long long>> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (isEqual(w, v[i].first)) {
                return i;
            }
        }
        return -1;
    }

    long long get_count(string word) {
        for (size_t i = 0; i < word.length(); i++) {
            word[i] = tolower(word[i]);
        }
        unsigned long hashValue = hashfunc(word);
        int idx = searchWord(word, htable[hashValue]);
        if (idx == -1) {
            return 0;
        }
        else {
            return htable[hashValue][idx].second;
        }
    }
};

class node {
public:
    int book_code;
    int page;
    int paragraph;
    int para_count;
    string word;

    node(int bcd, int pg, int para, int p_c, string w) {
        book_code = bcd;
        page = pg;
        word = w;
        paragraph = para;
        para_count = p_c;
    }
};

class Modified_HashTable {
private:
    vector<vector<node>> mtable;

    unsigned long hashfunc(const std::string& str) {
        unsigned long hash = 5381;
        for (char c : str) {
            hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
        }
        return hash%N;
    }

public:
    Modified_HashTable() {
        mtable.resize(100000009);
    }

    bool isEqual(string s, string w) {
        if (s.length() != w.length()) {
            return false;
        }
        else {
            for (size_t i = 0; i < s.length(); i++) {
                if (s[i] != w[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    int searchWord(string w, const vector<node> &v, int book_code, int page, int paragraph) {
        for (size_t i = 0; i < v.size(); i++) {
            if (isEqual(w, v[i].word)) {
                if (v[i].book_code == book_code) {
                    if (v[i].page == page) {
                        if (v[i].paragraph == paragraph) {
                            return i;
                        }
                    }
                }
            }
        }
        return -1;
    }

    void insertWord(string key, int book_code, int page, int paragraph, int sentence_no) {
        if (key == "\0") {
            return;
        }
        for (size_t i = 0; i < key.length(); i++) {
            key[i] = tolower(key[i]);
        }
        unsigned long hashValue = hashfunc(key);
        int idx = searchWord(key, mtable[hashValue], book_code, page, paragraph);
        if (idx != -1) {
            mtable[hashValue][idx].para_count++;
        }
        else {
            mtable[hashValue].push_back(node(book_code, page, paragraph, 1, key));
        }
    }

    int freq_in_a_para(string w, int book_code, int page, int paragraph) {
        for (size_t i = 0; i < w.length(); i++) {
            w[i] = tolower(w[i]);
        }
        unsigned long hashValue = hashfunc(w);
        int idx = searchWord(w, mtable[hashValue], book_code, page, paragraph);
        if (idx == -1) {
            return 0;
        }
        else {
            return mtable[hashValue][idx].para_count;
        }
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

class New_Dict {
private: 
    Modified_HashTable* New_Dictionary;
    // You can add attributes/helper functions here

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    New_Dict();

    ~New_Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_para_word_count(string word, int book_code, int pg, int para);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};