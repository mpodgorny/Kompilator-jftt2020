#include<iostream>
#include<stack>
#include "logic.hpp"
#include "conditions.hpp"

using namespace std;

stack<cond_flag> cond_flags;

void exp_eq(char** val1, char** val2, int line){
    var boolean;
    cond_flag flag;
    boolean.initialized=true;
    boolean.type="single";
    boolean.mem_addr=free_mem_idx++;
    flag.expr_start=k;
    load_single_value(val1);
    add_code("STORE", 10, " #EX_EQ_BEGIN");
    load_single_value(val2);
    add_code("SUB", 10);
    add_code("JZERO", k+4);
    add_code("SUB", 0);
    add_code("DEC");
    add_code("JUMP", k+3);
    add_code("SUB", 0);
    add_code("INC");
    add_code("STORE", boolean.mem_addr, " #EX_EQ_END");
    add_code("STORE", 3);

    add_code("INC #<SHOULD DISSAPEAR");
    add_code("INC #<SHOULD DISSAPEAR");

    flag.k_start=k;
    flag.boolean=boolean;
    
    cond_flags.push(flag);
}

// val1 !=val2
void exp_neq(char** val1, char** val2, int line){
    var boolean;
    boolean.mem_addr=free_mem_idx++;
    cond_flag flag;
    flag.expr_start=k;

    load_single_value(val2);
    add_code("STORE", 10, " #EX_NEQ_BEG");
    load_single_value(val1);
    add_code("SUB", 10);
    add_code("JZERO", k+4);
    add_code("SUB", 0);
    add_code("INC");
    add_code("JUMP", k+3);
    add_code("SUB", 0);
    add_code("DEC");
    add_code("STORE", boolean.mem_addr, " #EX_NEQ_END");
    add_code("STORE", 3);
    
    add_code("INC #<SHOULD DISSAPEAR");
    add_code("INC #<SHOULD DISSAPEAR");



    flag.boolean=boolean;
    
    flag.k_start=k;
    cond_flags.push(flag);
}

// val1 < val2
void exp_le(char** val1, char** val2, int line){
    var boolean;
    boolean.mem_addr=free_mem_idx++;
    cond_flag flag;
    flag.expr_start=k;

    load_single_value(val2);
    add_code("STORE", 10, " # EX_LE_BEGIN");
    load_single_value(val1);
    add_code("SUB", 10);
    add_code("JNEG", k+4);
    add_code("SUB", 0);
    add_code("DEC");
    add_code("JUMP", k+3);
    add_code("SUB", 0);
    add_code("INC");
    add_code("STORE", boolean.mem_addr, " # EX_LE_END");
    add_code("STORE", 3);

    add_code("INC #<SHOULD DISSAPEAR");
    add_code("INC #<SHOULD DISSAPEAR");

    flag.boolean=boolean;
    flag.k_start=k;
    cond_flags.push(flag);
}

// val1 > val2
void exp_ge(char** val1, char** val2, int line){
    var boolean;
    cond_flag flag;
    boolean.mem_addr=free_mem_idx++;
    flag.expr_start=k;
    flag.expr_start=k;

    load_single_value(val2);
    add_code("STORE", 10, " #EX_GE_BEGIN");
    load_single_value(val1);
    add_code("SUB", 10);
    add_code("JPOS", k+4);
    add_code("SUB", 0);
    add_code("DEC");
    add_code("JUMP", k+3);
    add_code("SUB", 0);
    add_code("INC");
    add_code("STORE", boolean.mem_addr, " #EQ_END");
    add_code("STORE", 3);

    add_code("INC #<SHOULD DISSAPEAR");
    add_code("INC #<SHOULD DISSAPEAR");

    flag.boolean=boolean;
    flag.k_start=k;
    cond_flags.push(flag);  
}

// val1 <= val2
void exp_leq(char** val1, char** val2, int line){
    var boolean;
    boolean.mem_addr=free_mem_idx++;
    cond_flag flag;
    flag.expr_start=k;

    load_single_value(val2);
    add_code("STORE", 10, " #EX_LEQ_BEGIN");
    load_single_value(val1);
    add_code("SUB", 10); //val1 - val2
    add_code("JNEG", k+5);
    add_code("JZERO", k+4);
    add_code("SUB", 0);
    add_code("DEC");
    add_code("JUMP", k+3);
    add_code("SUB", 0);
    add_code("INC");
    add_code("STORE", boolean.mem_addr, " #EX_LEQ_END");
    add_code("STORE", 3);

    add_code("INC #<SHOULD DISSAPEAR");
    add_code("INC #<SHOULD DISSAPEAR");

    flag.boolean=boolean;
    flag.k_start=k;
    cond_flags.push(flag);
}

//val1 >= val2
void exp_geq(char** val1, char** val2, int line){
    var boolean;
    boolean.mem_addr=free_mem_idx++;
    cond_flag flag;
    flag.expr_start=k;
    
    load_single_value(val2 );
    add_code("STORE", 10, " # EX_GEQ_BEGIN");
    load_single_value(val1);
    add_code("SUB", 10); //val1 - val2
    add_code("JPOS", k+5);
    add_code("JZERO", k+4);
    add_code("SUB", 0);
    add_code("DEC");
    add_code("JUMP", k+3);
    add_code("SUB", 0);
    add_code("INC");
    add_code("STORE", boolean.mem_addr, " # EQ_GEQ_END");
    add_code("STORE", 3);

    add_code("INC #<SHOULD DISSAPEAR");
    add_code("INC #<SHOULD DISSAPEAR");

    flag.boolean=boolean;
    flag.k_start=k;
    cond_flags.push(flag);
}