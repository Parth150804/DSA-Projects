// Do NOT add any other includes
#include "search.h"
#define rep(i,a,b) for(size_t i = a; i<b; i++)
using namespace std;

const int J = 1e6 + 7;

SearchEngine::SearchEngine(){
}

SearchEngine::~SearchEngine(){
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){ 
    for(size_t i = 0; i<sentence.size(); i++){
        if(sentence[i]!=' '){
            sentence[i] = tolower(sentence[i]); 
        }       
    }
    
    if (book_code <= int(v.size())) {
        if (page < int(v[book_code - 1].size())) {
            if (paragraph < int(v[book_code - 1][page].size())) {
                if (sentence_no - 1 < int(v[book_code - 1][page][paragraph].size())) {
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

    for(size_t i=0; i<str1.size(); i++){
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
    return hash%J;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    for(size_t i=0; i<pattern.size(); i++){
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
                    for(size_t m = 0; m < str.size(); m++){
                        string test = str.substr(m,pattern.size());
                        if(hashfunc(test) == hash_pattern){
                            if(checkstring(pattern, test)){
                                if (m == 0) {
                                    if (str.size() == test.size() or str[test.size()] == ' ') {
                                        n_matches++;
                                        insertathead(head,i+1,j,k,v[i][j][k][l].second,m); 
                                    }                              
                                }
                                else if (m == str.size() - test.size()) {
                                    if (str[m - 1] == ' ') {
                                        n_matches++;
                                        insertathead(head,i+1,j,k,v[i][j][k][l].second,m);  
                                    }
                                }
                                else {
                                    if (str[m - 1] == ' ' and str[m + test.size()] == ' ') {
                                        n_matches++;
                                        insertathead(head,i+1,j,k,v[i][j][k][l].second,m);
                                    }
                                }
                            }
                        }    
                    }
                }
            }
        }
    }  
    return head;
}

// int main() {
//     SearchEngine* srch = new SearchEngine();

//     // New_Dict* srch = new New_Dict();
//     srch->insert_sentence(1, 0, 0, 1, "VOL.1: 1896 30 NOVEMBER, 1896 1");
//     srch->insert_sentence(1, 0, 1, 2, "1.896 A CONFESSION 1, 56, 1896");
//     srch->insert_sentence(1, 0, 2, 3, "[1896] I wrote it on a slip of paper and handed it to him myself.");
//     srch->insert_sentence(1, 0, 2, 4, "In this note not only did I confess my guilt, but I asked adequate punishment for it, and closed with a request to him not to punish himself for my offence.");
//     srch->insert_sentence(1, 0, 2, 5, "I also pledged myself never to steal in future.");
//     srch->insert_sentence(1, 0, 3, 6, "An Autobiography, Pt. I, Ch. VIII");
//     srch->insert_sentence(1, 0, 4, 7, "2. SPEECH AT ALFRED HIGH SCHOOL, RAJKOT 3");
//     srch->insert_sentence(1, 0, 5, 8, "July 4, 1888 I hope that some of you will follow in my footsteps, and after you return from England you will work wholeheartedly for big reforms in India.");
//     srch->insert_sentence(1, 0, 6, 9, "[From Gujarati] Kethiawar Times, 12 7 1888");
//     srch->insert_sentence(1, 0, 7, 10, "1 When Gandhiji was 15, he had removed a bit of the gold from his brothers armlet to clear his a small debt of the latter.");
//     srch->insert_sentence(1, 0, 7, 11, "He felt so mortified about his act that he decided to make a confession to his father.");
//     srch->insert_sentence(1, 0, 7, 12, "Parental forgiveness was granted to him in the form of silent tears.");
//     srch->insert_sentence(1, 0, 7, 13, "The incident left a lasting mark on his mind.");
//     srch->insert_sentence(1, 0, 7, 14, "In his own words, it was an object lesson to him in the power of ahimsa.");

//     int n = 0;
//     Node* node = srch -> search("the", n);
//     printlist(node);
//     delete srch;
// }