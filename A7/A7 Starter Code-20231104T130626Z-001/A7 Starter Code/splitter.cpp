#include <bits/stdc++.h>
#include <chrono>
#include "search.cpp"
#include "Node.cpp"
using namespace std;

#define FILENAME "text_combined.txt"
// #define FILENAME "text_combined.txt"

int main() 
{
    int countin = 0;
    std::ifstream inputFile(FILENAME);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file." << std::endl;
        return 1;
    }
    std::ofstream outfile("split.txt" , fstream::app);

    auto start = chrono::high_resolution_clock::now();
    std::string tuple;
    std::string sentence;

    SearchEngine d;

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        std::vector<int> metadata;    
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
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
                metadata.push_back(num);
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata.push_back(num);
            }
        }

        // Now we have the string in sentence
        // And the other info in metadata
        // Add to the dictionary

        // Insert in the dictionary
        d.insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
        countin++;
    }

    inputFile.close();
    int count = 0;



    Node* a = d.search("the",count);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop-start);


    Node* traversal = a;

    // while (traversal != nullptr)
    // {
    //     outfile << "in book "<<traversal->book_code << " in page " << traversal->page << " in para "<< traversal->paragraph << " in sentence " << traversal->sentence_no << " at " << traversal->offset << endl;
    //     traversal = traversal->right;
    // }

    cout << "time " << duration.count()/1000.00000 << " seconds" << endl;
    cout << "ocuurences " << count;


}