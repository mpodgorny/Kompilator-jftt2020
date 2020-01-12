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

    //TODO: SAME VARIABLES  HANDLING XDDDDDDDDD

    var temp1, temp2, temp3;
    
    temp1 = variables.at(val1);
    temp2 = variables.at(val2);
    temp3.mem_addr = free_mem_idx++;
    
    add_code("LOAD", temp1.mem_addr);
    add_code("STORE", temp3.mem_addr);
    long long int j = k;
    add_code("LOAD", temp2.mem_addr);
    add_code("DEC");
    add_code("STORE", temp2.mem_addr);
    
    add_code("JZERO", j+8);
    add_code("LOAD", temp1.mem_addr);
    add_code("ADD", temp3.mem_addr);
    add_code("STORE", temp1.mem_addr);

    add_code("JUMP", j);
    add_code("LOAD", temp1.mem_addr);
}

void div(char* val1, char* val2, int line){
    var temp1, temp2, temp3;
    
    temp1 = variables.at(val1);
    temp2 = variables.at(val2);
    temp3.mem_addr = free_mem_idx++;

    add_code("SUB", 0);
    add_code("STORE", temp3.mem_addr);
    long long int j = k;
    add_code("JUMP", j+3); 
    add_code("LOAD", temp3.mem_addr);
    add_code("INC");
    add_code("STORE", temp3.mem_addr);
    add_code("LOAD", temp1.mem_addr);
    add_code("SUB", temp2.mem_addr);
    add_code("JUMP", j+9);
    add_code("LOAD", temp3.mem_addr);
    add_code("INC");
    add_code("JZERO", j+7);
    add_code("STORE", temp1.mem_addr);
    add_code("JPOS", j+1);
    add_code("LOAD", temp3.mem_addr);
}

void mod(char* val1, char* val2, int line){
    var temp1, temp2;
    
    temp1 = variables.at(val1);
    temp2 = variables.at(val2);

    add_code("LOAD", temp1.mem_addr);
    long long int j = k;
    add_code("SUB", temp2.mem_addr);
    add_code("JPOS", j);
    add_code("JZERO", j + 4);
    add_code("ADD", temp2.mem_addr);
}