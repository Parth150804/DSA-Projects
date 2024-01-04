#include <assert.h>
#include <sstream>
#include "qna_tool.h"

using namespace std;

#define FILENAME "mahatma-gandhi-collected-works-volume-1.txt"

long double score_word(string word, Dict* general_counter, csv_counter* cc) {
    long double num = general_counter -> get_word_count(word);
    long double den = cc -> get_count(word);
    return (num + 1)/(den + 1);
}

void Insertathead(Node* &head, int book_cd, int page_no, int para, int sent_no, int offset){
    Node* newnode = new Node(book_cd,page_no,para,sent_no,offset);
    newnode -> right = head;

    if(head != NULL){
        head -> left = newnode;
    }
    head = newnode;
}

void merge(std::vector<std::pair<long double, Node>>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    std::vector<std::pair<long double, Node>> leftArr(n1);
    std::vector<std::pair<long double, Node>> rightArr(n2);

    // Copy data to temporary arrays leftArr[] and rightArr[]
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].first <= rightArr[j].first) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArr[], if there are any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArr[], if there are any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<std::pair<long double, Node>>& arr, int left, int right) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

void modify_score(vector<pair<long double, Node>> &v, long double sum, int book, int pg, int para) {
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i].second.book_code == book) {
            if (v[i].second.page == pg) {
                if (v[i].second.paragraph == para) {
                    v[i].first += sum;
                    return;
                }
            }
        }
    }
    Node node(book, pg, para, -1, -1);
    v.push_back(make_pair(sum, node));
}

QNA_tool::QNA_tool(){
    general_counter = new Dict();       
    cc = new csv_counter();
    srch = new SearchEngine();

    std::ifstream file("unigram_freq.csv");

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    std::string line;
    // Skip the first line with headers
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string word;
        long long count;

        if (std::getline(lineStream, word, ',') &&
            std::getline(lineStream, line, ',')) {
            count = std::stoll(line);
            cc -> insert(word, count);
        }
    }
}

QNA_tool::~QNA_tool(){
    delete general_counter;
    delete cc;
    delete srch;
}

void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    general_counter -> insert_sentence(book_code, page, paragraph, sentence_no, sentence);
    srch -> insert_sentence(book_code, page, paragraph, sentence_no, sentence);
    return;
}

Node* QNA_tool::get_top_k_para(string question, int k) {
    long double score;
    vector<pair<string, long double>> v;

    string s = "\0";
    string separators = ".,-:!\"\'()?—[]“”‘’˙;@";
    for (size_t i = 0; i < question.size(); i++) {
        if (question[i] != ' ') {
            if (separators.find(question[i]) == string::npos) {     
                s += question[i];
            }
            else {
                score = score_word(s, general_counter, cc);
                v.push_back(make_pair(s, score));
                s = "\0";      
            }
        }
        else {
            score = score_word(s, general_counter, cc);
            v.push_back(make_pair(s, score));
            s = "\0";
        }
        if (i == question.size() - 1) {
            score = score_word(s, general_counter, cc);
            v.push_back(make_pair(s, score));          
        }
    }

    Node* nd; 
    Node* temp;
    vector<pair<long double, Node>> score_p;
    int n = 0;

    for(size_t i = 0; i < v.size(); i++) {
        nd = srch -> search(v[i].first, n);
        long double sum;

        temp = nd;
        while (temp) {
            sum = v[i].second;
            modify_score(score_p, sum, temp -> book_code, temp -> page, temp -> paragraph); 
            temp = temp -> right;
        }
        n = 0;
    }
    mergeSort(score_p, 0, score_p.size()-1);
    Node* head = NULL;
    if (k > int(score_p.size())) {
        for (size_t i = 0; i < score_p.size(); i++) {
            Insertathead(head, score_p[i].second.book_code, score_p[i].second.page, score_p[i].second.paragraph, -1, -1);
        } 
        return head;
    }

    for (size_t i = score_p.size() - k; i < score_p.size(); i++) {
        Insertathead(head, score_p[i].second.book_code, score_p[i].second.page, score_p[i].second.paragraph, -1, -1);
    }
    return head;
}

void QNA_tool::query(string question, string filename){
    Node* head = get_top_k_para(question, 3);
    query_llm(filename, head, 3, "sesyweiufgwogyuQGIWIEU", question);
    // Implement your function here  
    std::cout << "Q: " << question << std::endl;
    std::cout << "A: Studying COL106 :)" << std::endl;
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){

    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;
    
    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY, string question){

    // first write the k paragraphs into different files

    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph = get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();
 
    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}

void printlist(Node* head){
    Node* temp = head;
    while(temp != NULL){
        cout << temp->book_code << " "<<temp->page<<" "<<temp->paragraph<<" "<<temp->sentence_no<<" "<<"\n";
        temp = temp -> right;
    }
}

// int main() {
//     QNA_tool* srch = new QNA_tool();

//     srch->insert_sentence(1, 0, 0, 1, "VOL.1: 1896 30 NOVEMBER, 1896 1");
//     srch->insert_sentence(1, 0, 1, 2, "1896 A CONFESSION 1, 56, 1896");
//     srch->insert_sentence(1, 0, 2, 3, "[1896] I wrote it on a slip of paper and handed it to him myself.");
//     srch->insert_sentence(1, 0, 2, 4, "In this note not only did I confess my guilt, but I asked adequate punishment for it, and closed with a request to him not to punish himself for my offence.");
//     srch->insert_sentence(1, 0, 2, 5, "I also pledged myself never to steal in future.");
//     srch->insert_sentence(1, 0, 3, 6, "An Autobiography, Pt. I, Ch. VIII");
//     srch->insert_sentence(1, 0, 4, 7, "2. SPEECH AT ALFRED HIGH SCHOOL, RAJKOT 3");
//     srch->insert_sentence(1, 0, 5, 8, "July 4, 1888 I hope that some of you will follow in my footsteps, and after you return from England you will work wholeheartedly for big reforms in India.");
//     srch->insert_sentence(1, 0, 6, 9, "[From Gujarati] Kethiawar Times, 12 7 1888");
//     srch->insert_sentence(1, 0, 7, 10, "1 When Gandhiji was 15, he had removed a bit of gold from his brothers armlet to clear his a small debt of the latter.");
//     srch->insert_sentence(1, 0, 7, 11, "He felt so mortified about his act that he decided to make a confession to his father.");
//     srch->insert_sentence(1, 0, 7, 12, "Parental forgiveness the was granted to him in the form of silent tears.");
//     srch->insert_sentence(1, 0, 7, 13, "The incident left a lasting mark on his mind.");
//     srch->insert_sentence(1, 0, 7, 14, "In his own words, it was an object lesson to him in the power of ahimsa.");

//     // Node* node = srch -> get_top_k_para("the", 3);
//     // printlist(node);
//     srch -> query("a slip of paper?", "output.txt");
// }