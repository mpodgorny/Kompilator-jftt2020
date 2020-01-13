#include<iostream>
#include<stack>
#include "logic.hpp"
#include "conditions.hpp"

using namespace std;

stack<cond_flag> cond_flags;

void exp_eq(char* val1, char* val2, int line){
    var var1= variables.at(val1);
    var var2 = variables.at(val2);
    
    var boolean;
    boolean.mem_addr=free_mem_idx++;
    
    add_code("LOAD", var1.mem_addr, " #EQ_BEGINING");
    add_code("SUB", var2.mem_addr);
    add_code("JZERO", k+4);
    add_code("SUB", 0);
    add_code("DEC");
    add_code("JUMP", k+3);
    add_code("SUB", 0);
    add_code("INC");
    add_code("STORE", boolean.mem_addr, " #EQ_END");

    cond_flag flag;
    flag.k_start=k;


    flag.boolean=boolean;
    
    cond_flags.push(flag);
}

// val1 !=val2
void exp_neq(char* val1, char* val2, int line){
    var var1= variables.at(val1);
    var var2 = variables.at(val2);
    
    var boolean;
    boolean.mem_addr=free_mem_idx++;
    
    add_code("LOAD", var1.mem_addr, " #NEQ_BEGINING");
    add_code("SUB", var2.mem_addr);
    add_code("JZERO", k+4);
    add_code("SUB", 0);
    add_code("INC");
    add_code("JUMP", k+3);
    add_code("SUB", 0);
    add_code("DEC");
    add_code("STORE", boolean.mem_addr, " #NEQ_END");

    cond_flag flag;


    flag.boolean=boolean;
    
    flag.k_start=k;
    cond_flags.push(flag);
}

// val1 < val2
void exp_le(char* val1, char* val2, int line){
    var var1= variables.at(val1);
    var var2 = variables.at(val2);

    var boolean;
    boolean.mem_addr=free_mem_idx++;

    add_code("LOAD", var1.mem_addr, " #EQ_BEGINING");
    add_code("SUB", var2.mem_addr);
    add_code("JNEG", k+4);
    add_code("SUB", 0);
    add_code("DEC");
    add_code("JUMP", k+3);
    add_code("SUB", 0);
    add_code("INC");
    add_code("STORE", boolean.mem_addr, " #EQ_END");

    cond_flag flag;

    flag.boolean=boolean;
    
    flag.k_start=k;
    cond_flags.push(flag);
}

// val1 > val2
void exp_ge(char* val1, char* val2, int line){
    var var1= variables.at(val1);
    var var2 = variables.at(val2);
    var boolean;
    boolean.mem_addr=free_mem_idx++;
    add_code("LOAD", var1.mem_addr, " #EQ_BEGINING");
    add_code("SUB", var2.mem_addr);
    add_code("JPOS", k+4);
    add_code("SUB", 0);
    add_code("DEC");
    add_code("JUMP", k+3);
    add_code("SUB", 0);
    add_code("INC");
    add_code("STORE", boolean.mem_addr, " #EQ_END");

    cond_flag flag;


    flag.boolean=boolean;
    
    flag.k_start=k;
    cond_flags.push(flag);    
}

// val1 <= val2
void exp_leq(char* val1, char* val2, int line){
    var var1= variables.at(val1);
    var var2 = variables.at(val2);
    var boolean;
    boolean.mem_addr=free_mem_idx++;
    add_code("LOAD", var1.mem_addr, " #EQ_BEGINING");
    add_code("SUB", var2.mem_addr); //val1 - val2
    add_code("JNEG", k+5);
    add_code("JZERO", k+4);
    add_code("SUB", 0);
    add_code("DEC");
    add_code("JUMP", k+3);
    add_code("SUB", 0);
    add_code("INC");
    add_code("STORE", boolean.mem_addr, " #EQ_END");

    cond_flag flag;


    flag.boolean=boolean;
    
    flag.k_start=k;
    cond_flags.push(flag);
}

//val1 >= val2
void exp_geq(char* val1, char* val2, int line){
    var var1= variables.at(val1);
    var var2 = variables.at(val2);

    var boolean;
    boolean.mem_addr=free_mem_idx++;

    add_code("LOAD", var1.mem_addr, " #EQ_BEGINING");
    add_code("SUB", var2.mem_addr); //val1 - val2
    add_code("JPOS", k+5);
    add_code("JZERO", k+4);
    add_code("SUB", 0);
    add_code("DEC");
    add_code("JUMP", k+3);
    add_code("SUB", 0);
    add_code("INC");
    add_code("STORE", boolean.mem_addr, " #EQ_END");

    cond_flag flag;

    flag.boolean=boolean;
    
    flag.k_start=k;
    cond_flags.push(flag);
}