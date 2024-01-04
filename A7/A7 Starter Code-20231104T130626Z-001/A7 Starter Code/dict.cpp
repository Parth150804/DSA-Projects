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
    for (size_t i = 0; i < sentence.size(); i++) {
        if (sentence[i] != ' ') {
            if (separators.find(sentence[i]) == string::npos) {     
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
    return;
}

New_Dict::New_Dict(){  
    New_Dictionary = new Modified_HashTable(); 
}

New_Dict::~New_Dict(){ 
    delete New_Dictionary; 
}

void New_Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    string s = "\0";
    string separators = ".,-:!\"\'()?—[]“”‘’˙;@";
    for (size_t i = 0; i < sentence.size(); i++) {
        if (sentence[i] != ' ') {
            if (separators.find(sentence[i]) == string::npos) {     
                s += sentence[i];
            }
            else {
                New_Dictionary -> insertWord(s, book_code, page, paragraph, sentence_no);
                s = "\0";      
            }
        }
        else {
            New_Dictionary -> insertWord(s, book_code, page, paragraph, sentence_no);
            s = "\0";
        }
        if (i == sentence.size() - 1) {
            New_Dictionary -> insertWord(s, book_code, page, paragraph, sentence_no);          
        }
    }
    return;
}

int New_Dict::get_para_word_count(string word, int book_code, int pg, int para){
    return New_Dictionary -> freq_in_a_para(word, book_code, pg, para);
}

void New_Dict::dump_dictionary(string filename){    
    return;
}


// int main() {
//     New_Dict* srch = new New_Dict();
//     srch->insert_sentence(1, 0, 0, 1, "VOL.1: 1896 30 NOVEMBER, 1896 1");
//     srch->insert_sentence(1, 0, 1, 2, "1.896 A CONFESSION 1, 56, 1896");
//     srch->insert_sentence(1, 0, 2, 3, "[1896] I wrote it on a slip of paper and handed it to him myself.");
//     srch->insert_sentence(1, 0, 2, 4, "In this note not only did I confess my guilt, but I asked adequate punishment for it, and closed with a request to him not to punish himself for my offence.");
//     srch->insert_sentence(1, 0, 2, 5, "I also pledged myself never to steal in future.");
//     srch->insert_sentence(1, 0, 3, 6, "An Autobiography, Pt. I, Ch. VIII");
//     srch->insert_sentence(1, 0, 4, 7, "2. SPEECH AT ALFRED HIGH SCHOOL, RAJKOT 3");
//     srch->insert_sentence(1, 0, 5, 8, "July 4, 1888 I hope that some of you will follow in my footsteps, and after you return from England you will work wholeheartedly for big reforms in India.");
//     srch->insert_sentence(1, 0, 6, 9, "[From Gujarati] Kethiawar Times, 12 7 1888");
//     srch->insert_sentence(1, 0, 7, 10, "1 When Gandhiji was 15, he had removed a bit of gold from his brothers armlet to clear his a small debt of the latter.");
//     srch->insert_sentence(1, 0, 7, 11, "He felt so mortified about his act that he decided to make a confession to his father.");
//     srch->insert_sentence(1, 0, 7, 12, "Parental forgiveness was granted to him in the form of silent tears.");
//     srch->insert_sentence(1, 0, 7, 13, "The incident left a lasting mark on his mind.");
//     srch->insert_sentence(1, 0, 7, 14, "In his own words, it was an object lesson to him in the power of ahimsa.");

//     std::cout << srch -> get_para_word_count("the", 1, 0, 7);
// }
