// Do NOT add any other includes
#include "search.h"
// #include "Node.cpp"
#define rep(i,a,b) for(int i=a; i<b; i++)
using namespace std;

const int N=1e8+7;

SearchEngine::SearchEngine(){
}

SearchEngine::~SearchEngine(){
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){ 
    for(int i=0; i<sentence.size(); i++){
        if(sentence[i]!=' '){
            sentence[i] = tolower(sentence[i]); 
        }       
    }
    
    if (book_code <= v.size()) {
        if (page < v[book_code - 1].size()) {
            if (paragraph < v[book_code - 1][page].size()) {
                if (sentence_no - 1 < v[book_code - 1][page][paragraph].size()) {
                    v[book_code - 1][page][paragraph][sentence_no - 1] = make_pair(sentence, sentence_no);
                } else {
                    v[book_code - 1][page][paragraph].push_back(make_pair(sentence, sentence_no));
                }
            } else {
                v[book_code - 1][page].push_back(vector<pair<string, int>>{make_pair(sentence, sentence_no)});
            }
        } else {
            v[book_code - 1].push_back(vector<vector<pair<string, int>>>{{make_pair(sentence, sentence_no)}});
        }
    } else {
        v.push_back(vector<vector<vector<pair<string, int>>>>());
        v[v.size() - 1].push_back(vector<vector<pair<string, int>>>());
        v[v.size() - 1][v[v.size() - 1].size() - 1].push_back(vector<pair<string, int>>({make_pair(sentence, sentence_no)}));
    }
}     

void insertathead(Node* &head, int book_cd, int page_no, int para, int sent_no, int offset){
    Node* newnode = new Node(book_cd,page_no,para,sent_no,offset);
    newnode -> right = head;

    if(head != NULL){
        head -> left = newnode;
    }
    head = newnode;
}

bool checkstring(const string &str1, const string &str2){
    if(str1.size()!=str2.size()){
        return false;
    }

    for(int i=0; i<str1.size(); i++){
        if(str1[i]!=str2[i]){
            return false;
        }
    }
    return true;
}

unsigned long hashfunc(const std::string& str) {
    unsigned long hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
    }
    return hash%N;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    for(int i=0; i<pattern.size(); i++){
        if(pattern[i]!=' '){
            pattern[i] = tolower(pattern[i]); 
        }       
    }   
    // Implement your function here  
    unsigned long hash_pattern = hashfunc(pattern);
    Node* head = NULL;

    rep(i,0,v.size()){
        rep(j,0,v[i].size()){
            rep(k,0,v[i][j].size()){
                rep(l,0,v[i][j][k].size()){
                    string str = v[i][j][k][l].first;
                    for(int m=0; m < str.size(); m++){
                        string test = str.substr(m,pattern.size());
                        if(hashfunc(test) == hash_pattern){
                            if(checkstring(pattern,test)){
                                n_matches++;
                                insertathead(head,i+1,j,k,v[i][j][k][l].second,m);    
                            }
                        }
                    }
                }
            }
        }
    }
    
    return head;
}