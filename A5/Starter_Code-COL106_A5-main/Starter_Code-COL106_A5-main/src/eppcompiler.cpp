/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler() {
    memory_size = 0;
    output_file = "\0";
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit) {
    memory_size = mem_limit;
    for (int i = 0; i < memory_size; i++) {
        mem_loc.push_back(i);
    }
    output_file = out_file;
}

void EPPCompiler::compile(vector<vector<string>> code) {
    for (int i = 0; i < code.size(); i++) {
        targ.parse(code[i]);
        if (code[i][0] == "del") {
            int avail_address = targ.last_deleted;
            mem_loc.push_back(avail_address);
            generate_targ_commands();
        }
        else if (code[i][0] == "ret") {
            generate_targ_commands();
        }
        else {
            if (targ.symtable -> search(code[i][0]) == -1) {
                targ.symtable -> assign_address(code[i][0], mem_loc.back());
                mem_loc.pop_back();
            }
            generate_targ_commands();
        }
    }
}

void command_gene(vector<string> &v, ExprTreeNode* Tree, SymbolTable* sym, int last_deleted) {
    if (Tree == NULL) {
        return;
    }
    else if (!Tree -> right and !Tree -> left) {
        if (Tree -> type == "VAR") {
            int address = sym -> search(Tree -> id);
            if (address == -2) {
                v.push_back("PUSH mem[" + to_string(last_deleted) + "]");
            }
            else {
                v.push_back("PUSH mem[" + to_string(address) + "]");
            }
        }
        else {
            v.push_back("PUSH " + to_string(Tree -> num));
        }
    }
    else {
        command_gene(v, Tree -> right, sym, last_deleted);
        command_gene(v, Tree -> left, sym, last_deleted);
        v.push_back(Tree -> type);
    }
}

vector<string> EPPCompiler::generate_targ_commands() {
    ExprTreeNode* Tree = targ.expr_trees.back();
    vector<string> v;
    command_gene(v, Tree -> right, targ.symtable, targ.last_deleted);
    if (Tree -> left -> type == "VAR") {
        v.push_back("mem[" + to_string(targ.symtable -> search(Tree -> left -> id)) + "] = POP");
    }
    else if (Tree -> left -> type == "DEL") {
        v.push_back("DEL = mem[" + to_string(targ.last_deleted) + "]");
    }
    else {
        v.push_back("RET = POP");
    }
    write_to_file(v);
    return v;
}

void EPPCompiler::write_to_file(vector<string> commands) {
    ofstream outputFilestream(output_file, ios::app);

    for (string command : commands) {
        outputFilestream << command << "\n";
    }

    outputFilestream.close();
}

EPPCompiler::~EPPCompiler() {
  
}


