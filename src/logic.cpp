#include "logic.hpp"
using namespace std;

vector<string> code; 
map<string, var> variables;
map<int, long long int> consts;

long long int k=0;

var last_var;

bool reg1_taken = false;

long long int free_mem_idx=4;

// TYPES: single, array, iterator

void declaration(char* identifier, int line){
    if (variables.find(identifier) != variables.end())
            error("variable already declared, bro", line);
    var temp;
    temp.type="single";
    variables.insert(make_pair(identifier, temp));
}

void declaration(char* identifier, char* begining, char* end, int line){
    if (variables.find(identifier) != variables.end())
            error("variable already declared, bro", line);
    if(stoll(begining)>stoll(end))
        error("array's end smaller than begining index", line);
    
    var temp;
    temp.type="array";
    temp.size= stoll(end) - stoll(begining);
    variables.insert(make_pair(identifier, temp));
}

void assign(char* name, int line){
    if (variables.find(name) == variables.end())
        error("The variable has not been declared:", line);
    var &searched = variables.at(name);
    if (searched.type == "iterator")
        error("no loop iterators modification allowed", line);
    if (searched.initialized==true){
        add_code("STORE", searched.mem_addr, " #assigning");
    }else{
        searched.initialized = true;
        searched.mem_addr=free_mem_idx;
        add_code("STORE", searched.mem_addr, " #assigning");
        free_mem_idx++;
    }
}

void read(char* name){
    var &variable = variables.at(name);
    variable.mem_addr=free_mem_idx++;
    variable.initialized=true;
    add_code("GET");
    add_code("STORE", variable.mem_addr);
}

void write(char* name){
    var searched = variables.at(name);
    add_code("LOAD", searched.mem_addr, " #WRITE");
    add_code("PUT");
}

void value_num(char* val, int line){
    add_code("SUB", 0);
    if (stoll(val)>0){
        for(long long int it = 0; it!=stoll(val);it++){
            add_code("INC");

        }
    }else {
        for(long long int it = 0; it!=stoll(val);it--){
            add_code("DEC");     

        }
    }
    if (reg1_taken){
        add_code("STORE", 2);
        var temp;
        temp.mem_addr=2;
        variables.insert(make_pair(val, temp));
        reg1_taken=false;
    }else {
        add_code("STORE", 1);
        var temp;
        temp.mem_addr=1;
        variables.insert(make_pair(val, temp));
        reg1_taken=true;
    }
}

void identifier_pid(char* name, int line){
    if (variables.find(name) == variables.end())
        error("The variable has not been declared:", line);
}

void identifier_pid_pid(char* name, char* idx, int line){
    if (variables.find(name) == variables.end())
        error("The variable has not been declared:", line);
    if (variables.find(idx) == variables.end())
        error("The variable has not been declared:", line);
    //TODO: controling arrays
}

void identifier_pid_num(char* name, char* idx, int line){
    if (variables.find(name) == variables.end())
        error("The variable has not been declared:", line);
    //TODO: controling arrays
}

/*
 * "around" compiler functions
*/
void add_code(string snip){
    k++;
    code.push_back(snip);
}

void add_code(string snip, long long int val) {
    k++;
    string temp;
    temp = snip + " " + to_string(val);
    code.push_back(temp);
}

void add_code(string snip, long long int val, string comment) {
    k++;
    string temp;
    temp = snip + " " + to_string(val)+comment;
    code.push_back(temp);
}

void save_to_file(char* out) {
    ofstream file;
    file.open(out);
    for (int command = 0; command < code.size(); command++) {
        file << code.at(command) << endl;
    }
    file.close();
}

void error(string msg, int line){
    cout<<"Error in line: "<<line<<": "<<msg<<endl;
    exit(-1);
}

void end() {
    add_code("HALT");
}