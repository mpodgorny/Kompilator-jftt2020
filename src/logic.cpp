#include "logic.hpp"
using namespace std;

vector<string> code;
map<string, var> variables;
map<string, var> arrays;
stack<index> indexes;

map<int, long long int> consts;

long long int k=0;

bool reg1_taken = false;

long long int free_mem_idx=15;

bool debug = true;

// TYPES: single, array, iterator

void declaration(char* identifier, int line){
    if (variables.find(identifier) != variables.end())
            error("variable already declared, bro", line);
    var temp;
    temp.type="single";
    temp.mem_addr=free_mem_idx++;
    variables.insert(make_pair(identifier, temp));
}

void declaration(char* identifier, char* begining, char* end, int line){
    if (variables.find(identifier) != variables.end())
            error("variable already declared, bro", line);
    if(stoll(begining)>stoll(end))
        error("array's end smaller than begining index", line);
    var temp;
    temp.type="array";
    temp.mem_addr=free_mem_idx++;
    temp.size= stoll(end) - stoll(begining)+1;
    free_mem_idx+=temp.size; //address reservation
    generate_number(temp.mem_addr-stoll(begining)+1); //saving value to extract values at idx's
    add_code("STORE", temp.mem_addr, " #ARR_BEGINING");
    variables.insert(make_pair(identifier, temp));
}

void assign(char* name[], int line){
    if (variables.find(string(name[0])) == variables.end())
        error("variable has not been declared", line);
    var &searched = variables.at(string(name[0]));
    if (searched.type == "iterator")
        error("no loop iterators modification allowed", line);
    searched.initialized=true;
    store_variable(name);
}

void store_variable(char* name[]){
    var variable = variables.at(name[0]);
    if (variable.type=="array"){
        add_code("STORE", 4, " # STORE_VAR_BEGINNING");   //store value to store :)
        if( (name[1] != nullptr) && (check_if_number(name[1])) ){ 
            generate_number(stoll(name[1])); // IF the index is number const - generate it
            add_code("STORE", 6); //save index in mem=6
        }else{                                                  //IF the index is variable
            var found_index = variables.at(string(name[1]));    
            add_code("LOAD", found_index.mem_addr);             //load index value
            add_code("STORE", 6);                   //store it mem=6
        }    
        //Now we have: 
        //value to store at 4, index of array at 6         
        add_code("LOAD", variable.mem_addr); //load relative index of array
        add_code("ADD", 6);   //add wanted index
        add_code("STORE", 5); // storing absolute index
        add_code("LOAD", 4);  // loading value to store, duh
        add_code("STOREI", 5, " #STORE_VAR_END"); // STOREI IT! :)
    
    }else{
        add_code("STORE", variable.mem_addr, " # re-assigning");
    }

}

bool check_if_number(const std::string& s)
{   
    if( !(s.at(0)=='-' || isdigit(s.at(0))) ){
        return false;
    }
    std::string::const_iterator it = s.begin();
    advance(it, 1);
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void read(char** name){
    var &variable = variables.at(name[0]);
    variable.initialized=true;
    add_code("GET");
    store_variable(name);
}

void write(char** name){
    load_single_value(name);
    add_code("PUT");
    cout<<" >>>>>>>"<<name[0];

}

void load_variable(char** name){
    var variable = variables.at(name[0]);
    if (variable.type=="array"){
        if( (name[1] != nullptr) && (check_if_number(name[1])) ){ 
            generate_number(stoll(name[1])); // IF the index is number const - generate it
            add_code("STORE", 6, " # LOAD_VAR_BEGINNING"); //save index in mem=6
        }else{                                                  //IF the index is variable
            var found_index = variables.at(name[1]);    
            add_code("LOAD", found_index.mem_addr);             //load index value
            add_code("STORE", 6);                   //store it mem=6
        }    
        //Now we have: 
        //value to store at 4, index of array at 6         
        add_code("LOAD", variable.mem_addr); //load relative index of array
        add_code("ADD", 6);   //add wanted index
        add_code("STORE", 5); // storing absolute index
        add_code("LOADI", 5, " #LOAD_VAR END"); // LOADI IT:)
    
    }else{
        add_code("LOAD", variable.mem_addr, " # load variable");
    }
}


void load_single_value(char** name){
    if (check_if_number(name[0])){
        generate_number(name[0]);
    }else{
        load_variable(name);
    }
}

void generate_number(char* val){
    generate_number(stoll(val));
}

void generate_number(long long int val){
    if(val>=0){
        add_code("SUB", 0);
        if (val < 10) {
        for (long long int i = 0; i < val; ++i) {
            add_code("INC");
        }
    } else {
        generate_number(val >> 1);
        add_code("ADD", 0);
        if (val % 2 == 1) {
            add_code("INC");
        }
    }
    } else {
        add_code("SUB", 0);
        if (val > -10) {
        for (long long int i = 0; i < abs(val); ++i) {
            add_code("DEC");
        }
    } else {
        generate_number(val >> 1);
        add_code("ADD", 0);
        if (abs(val) % 2 == 1) {
            add_code("INC");
        }
    }
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
    // index index;
    // index.arr_name=name;
    // index.name=idx;
    // indexes.push(index);
    // cout<<"idx_str_added:"<<idx<<endl;
}

void identifier_pid_num(char* name, char* idx, int line){
    if (variables.find(name) == variables.end())
        error("The variable has not been declared:", line);
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