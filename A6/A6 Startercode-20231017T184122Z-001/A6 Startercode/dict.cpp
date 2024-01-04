// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    Dictionary = new HashTable();    
}

Dict::~Dict(){
    delete Dictionary;  
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    string s = "\0";
    string separators = ".,-:!\"\'()?—[]“”‘’˙;@";
    for (int i = 0; i < sentence.size(); i++) {
        if (sentence[i] != ' ') {
            if (separators.find(sentence[i]) == string::npos) {     // npos -> no position
                s += sentence[i];
            }
            else {
                Dictionary -> insertWord(s);
                s = "\0";      
            }
        }
        else {
            Dictionary -> insertWord(s);
            s = "\0";
        }
        if (i == sentence.size() - 1) {
            Dictionary -> insertWord(s);          
        }
    }
    return;
}

int Dict::get_word_count(string word){
    return Dictionary -> freq(word);
}

void Dict::dump_dictionary(string filename){
    Dictionary -> write_to_file(filename);     
    return;
}

