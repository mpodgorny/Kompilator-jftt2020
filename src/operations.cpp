#include "operations.hpp"
#include "logic.hpp"

using namespace std;


void add(char* val1, char* val2, int line){
    var temp1, temp2;
    temp1 = variables.at(val1);
    temp2 = variables.at(val2);

    add_code("LOAD", temp1.mem_addr);
    add_code("ADD", temp2.mem_addr);
}

void sub(char* val1, char* val2, int line){
    var temp1, temp2;
    temp1 = variables.at(val1);
    temp2 = variables.at(val2);

    add_code("LOAD", temp1.mem_addr);
    add_code("SUB", temp2.mem_addr);
}

void mul(char* val1, char* val2, int line){
    var temp1, temp2, temp3, temp4;

    if(is_number(val1)){
        temp1.mem_addr=free_mem_idx++;
        generate_number(val1);
        add_code("STORE", temp1.mem_addr);
    } else{
        temp1.mem_addr = free_mem_idx++;
        add_code("LOAD", variables.at(val1).mem_addr);
        add_code("STORE", temp1.mem_addr);
    }

    if(is_number(val2)){
        temp2.mem_addr=free_mem_idx++;
        generate_number(val2);
        add_code("STORE", temp2.mem_addr);
    } else {
        temp2.mem_addr = free_mem_idx++;
        add_code("LOAD", variables.at(val2).mem_addr);
        add_code("STORE", temp2.mem_addr);    
        }
    //temp1 = variables.at(val1);
    //temp2 = variables.at(val2);
    temp3.mem_addr = free_mem_idx++;
    temp4.mem_addr = free_mem_idx++;

    add_code("LOAD", temp1.mem_addr, " # MUL_START");
    add_code("STORE", temp3.mem_addr);
    add_code("LOAD", temp2.mem_addr);
    add_code("STORE", temp4.mem_addr);
    long long int j = k;
    add_code("LOAD", temp4.mem_addr);
    add_code("DEC");
    add_code("STORE", temp4.mem_addr);
    
    add_code("JZERO", j+8);
    add_code("LOAD", temp1.mem_addr);
    add_code("ADD", temp3.mem_addr);
    add_code("STORE", temp1.mem_addr);

    add_code("JUMP", j);
    add_code("LOAD", temp1.mem_addr, " #MUL_END");
}

void div(char* val1, char* val2, int line){
    var temp1, temp2;
    int counter = free_mem_idx++;
    if(is_number(val1)){
        temp1.mem_addr=free_mem_idx++;
        generate_number(val1);
        add_code("STORE", temp1.mem_addr, " #DIV_ALLOCATING_MEM");
    } else{
        temp1.mem_addr = free_mem_idx++;
        add_code("LOAD", variables.at(val1).mem_addr);
        add_code("STORE", temp1.mem_addr);
    }
    if(is_number(val2)){
        temp2.mem_addr=free_mem_idx++;
        generate_number(val2);
        add_code("STORE", temp2.mem_addr);
    } else {
        temp2.mem_addr = free_mem_idx++;
        add_code("LOAD", variables.at(val2).mem_addr);
        add_code("STORE", temp2.mem_addr);    
        }

    add_code("SUB", 0, " #DIV_START");
    add_code("STORE", counter, " #COUNTER");
    int j=k;
    add_code("LOAD", temp2.mem_addr, " #test na dzielnik 0");
    add_code("JZERO", j+11); //na koniec bo dzielenie przez zero
    
    add_code("LOAD", temp1.mem_addr, " #WLASCIWY ALGO");
    add_code("JZERO", j+11); 
    add_code("SUB", temp2.mem_addr);
    add_code("JNEG", j+11); //na koniec, zwracamy zero

    add_code("STORE", temp1.mem_addr);
    add_code("LOAD", counter);
    add_code("INC");
    add_code("STORE", counter);
    add_code("JUMP", j+2); //skacz do zaladowania temp1
    add_code("LOAD", counter, " #DIV_END");
}

//TODO: NEGATIVE NUMBERS
void mod(char* val1, char* val2, int line){
    var temp1, temp2;
    if(is_number(val1)){
        temp1.mem_addr=free_mem_idx++;
        generate_number(val1);
        add_code("STORE", temp1.mem_addr, " #MOD_ALLOCATING_MEM");
    } else{
        temp1.mem_addr = free_mem_idx++;
        add_code("LOAD", variables.at(val1).mem_addr);
        add_code("STORE", temp1.mem_addr);
    }
    if(is_number(val2)){
        temp2.mem_addr=free_mem_idx++;
        generate_number(val2);
        add_code("STORE", temp2.mem_addr);
    } else {
        temp2.mem_addr = free_mem_idx++;
        add_code("LOAD", variables.at(val2).mem_addr);
        add_code("STORE", temp2.mem_addr);    
        }
    
    add_code("LOAD", temp2.mem_addr, " #MOD_START");
    long long int j = k;
    add_code("JZERO", j+6);
    add_code("LOAD", temp1.mem_addr);
    j = k;
    add_code("SUB", temp2.mem_addr);
    add_code("JPOS", j);
    add_code("JZERO", j + 4);
    add_code("ADD", temp2.mem_addr, " #MOD_END");
}

bool is_number(const std::string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}