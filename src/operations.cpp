#include "operations.hpp"
#include "logic.hpp"

using namespace std;
// m[1] <- 1 ; m[2] <- -1 
//3 <- loop bool 4-10 <-arr operations ; 10-20 <- arithemtic operations
void add(char** val1, char** val2, int line){
    load_single_value(val1);
    add_code("STORE", 10, " #ADD");
    load_single_value(val2);
    add_code("ADD ", 10);
}

void sub(char** val1, char** val2, int line){
    load_single_value(val2);
    add_code("STORE", 10);
    load_single_value(val1);
    add_code("SUB", 10);
}

void mul(char** val1, char** val2, int line){
    add_code("SUB", 0, " # MUL_BEGIN");     //sign flag
    add_code("STORE", 13);
    add_code("SUB", 0);
    add_code("STORE", 12); 
    load_single_value(val1);
    add_code("STORE", 10);
    load_single_value(val2);
    add_code("STORE", 11);
    // 10 <-a ; 11 <- b ; 12 <- result ; 13 <- sign flag
    
    evaluate_sign_and_abs(10);
    evaluate_sign_and_abs(11);
    
    //while(a!=0)
    int begining = k;
    add_code("LOAD", 10);
    add_code("JZERO", k+16); //////
    // a & 1
    add_code("LOAD", 10);
    add_code("SHIFT", 2);
    add_code("SHIFT", 1);
    add_code("SUB", 10);
    //if(a & 1)
    add_code("JZERO", k+4); 
    add_code("LOAD", 12);
    add_code("ADD", 11);
    add_code("STORE", 12);
    // a = a >> 1
    add_code("LOAD", 10);
    add_code("SHIFT", 2);
    add_code("STORE", 10);
    //b = b + 1
    add_code("LOAD", 11);
    add_code("ADD", 11);
    add_code("STORE", 11);
    add_code("JUMP", begining);
    check_sign_flag_and_reverse_result(12);
    add_code("LOAD", 12);
}

void evaluate_sign_and_abs(int adrr){
    add_code("LOAD", adrr);
    add_code("JPOS", k+10);
    add_code("LOAD", 13);
    add_code("JZERO", k+3);
    add_code("DEC");
    add_code("JUMP", k+2);
    add_code("INC");
    add_code("STORE", 13);
    add_code("SUB", 0);
    add_code("SUB", adrr);
    add_code("STORE", adrr);
}

void check_sign_flag_and_reverse_result(int addr){
    add_code("LOAD", 13);
    add_code("JZERO", k+4);
    add_code("SUB", 0);
    add_code("SUB", addr);
    add_code("STORE", addr);
}


void div_low(char** val1, char** val2, int line){
    // 10 <-a ; 11 <- b ; 12 <- result ; 13 <- sign flag ; 14 <- multipler
    add_code("SUB", 0, " #DIV_OR_MOD_BEGIN");     //sign flag
    add_code("STORE", 13);
    add_code("SUB", 0);
    add_code("STORE", 12); 
    load_single_value(val1);
    add_code("STORE", 10);
    load_single_value(val2);
    add_code("STORE", 11);
    add_code("SUB", 0); //multiplier 
    add_code("INC");
    add_code("STORE", 14);
    //checking if val2 == ZERO
    add_code("LOAD", 11);
    add_code("JZERO", k+2);
    add_code("JUMP", k+6);
    add_code("SUB", 0); 
    add_code("STORE", 10);
    add_code("STORE", 11);
    add_code("STORE", 14);
    add_code("STORE", 12);

    //evaluate_sign_and_abs(10); cuz result should have same sign as DZIELNIK
    evaluate_sign_and_abs(11);

    // a = REMAIN (10) ; b = SCALED_DIVISOR (11)
    int beginning = k;
    //	while(divisor < dividend)
    add_code("LOAD", 11);
    add_code("SUB", 10);
    add_code("JPOS", k+9);
    add_code("JZERO", k+8); 
     // Multiply "b" by two.
    add_code("LOAD", 11);
    add_code("ADD", 11);
    add_code("STORE", 11);
    // multiplier multiply by two.
    add_code("LOAD", 14);
    add_code("ADD", 14);
    add_code("STORE", 14);
    add_code("JUMP", beginning);
    //do
    int do_beginning = k;
    //IF (remain >= scaled_divisor)
    add_code("LOAD", 10);
    add_code("SUB", 11);
    add_code("JNEG", k+7);
    // remain = remain - scaled_divisor;
    add_code("LOAD", 10);
    add_code("SUB", 11);
    add_code("STORE", 10);
    // result = result + multiple;
    add_code("LOAD", 12);
    add_code("ADD", 14);
    add_code("STORE", 12);
    //END_IF
    //DIVIDING BY TWO: b and multiply
    add_code("LOAD", 11);
    add_code("SHIFT", 2);
    add_code("STORE", 11);
    add_code("LOAD", 14);
    add_code("SHIFT", 2);
    add_code("STORE", 14);
    
    //WHILE  multiply !=0
    add_code("LOAD", 14);
    add_code("JNEG", do_beginning);
    add_code("JPOS", do_beginning);
}

// void div(char** val1, char** val2, int line){
    
//     div_low(val1, val2, line);
//     check_sign_flag_and_reverse_result(12);
//     add_code("LOAD", 12, " # DIV END<");
// }
// //TODO: NEGATIVE NUMBERS
// void mod(char** val1, char** val2, int line){
//     // 10 <-a ; 11 <- b ; 12 <- result ; 13 <- sign flag
//     div_low(val1, val2, line);
//     check_sign_flag_and_reverse_result(10);
//     add_code("LOAD", 10, " # MOD END");

// }


void div(char** val1, char** val2, int line){



    // 10 <-a ; 11 <- b ; 12 <- result ; 13 <- sign flag ; 14 <- multipler
    add_code("SUB", 0, " #DIV_OR_MOD_BEGIN");     //sign flag
    add_code("STORE", 13);
    add_code("SUB", 0);
    add_code("STORE", 12); 
    load_single_value(val1);
    add_code("STORE", 10);
    load_single_value(val2);
    add_code("STORE", 11);
    add_code("SUB", 0); //multiplier 
    add_code("INC");
    add_code("STORE", 14);
    //checking if val2 == ZERO
    add_code("LOAD", 11);
    add_code("JZERO", k+2);
    add_code("JUMP", k+6);
    add_code("SUB", 0); 
    add_code("STORE", 10);
    add_code("STORE", 11);
    add_code("STORE", 14);
    add_code("STORE", 12);

    evaluate_sign_and_abs(10);
    evaluate_sign_and_abs(11);

    // a = REMAIN (10) ; b = SCALED_DIVISOR (11)
    int beginning = k;
    //	while(divisor < dividend)
    add_code("LOAD", 11);
    add_code("SUB", 10);
    add_code("JPOS", k+9);
    add_code("JZERO", k+8); 
     // Multiply "b" by two.
    add_code("LOAD", 11);
    add_code("ADD", 11);
    add_code("STORE", 11);
    // multiplier multiply by two.
    add_code("LOAD", 14);
    add_code("ADD", 14);
    add_code("STORE", 14);
    add_code("JUMP", beginning);
    //do
    int do_beginning = k;
    //IF (remain >= scaled_divisor)
    add_code("LOAD", 10);
    add_code("SUB", 11);
    add_code("JNEG", k+7);
    // remain = remain - scaled_divisor;
    add_code("LOAD", 10);
    add_code("SUB", 11);
    add_code("STORE", 10);
    // result = result + multiple;
    add_code("LOAD", 12);
    add_code("ADD", 14);
    add_code("STORE", 12);
    //END_IF
    //DIVIDING BY TWO: b and multiply
    add_code("LOAD", 11);
    add_code("SHIFT", 2);
    add_code("STORE", 11);
    add_code("LOAD", 14);
    add_code("SHIFT", 2);
    add_code("STORE", 14);
    
    //WHILE  multiply !=0
    add_code("LOAD", 14);
    add_code("JNEG", do_beginning);
    add_code("JPOS", do_beginning);

    add_code("LOAD", 13);
    add_code("JZERO", k+5);
    add_code("SUB", 0);
    add_code("SUB", 12);
    add_code("DEC");
    add_code("STORE", 12);

    add_code("LOAD", 12, " # DIV END<");
}
//TODO: NEGATIVE NUMBERS
void mod(char** val1, char** val2, int line){
    // 10 <-a ; 11 <- b ; 12 <- result ; 13 <- sign flag ; 14 <- multipler
    add_code("SUB", 0, " #DIV_OR_MOD_BEGIN");     //sign flag
    add_code("STORE", 13);
    add_code("SUB", 0);
    add_code("STORE", 12); 
    load_single_value(val1);
    add_code("STORE", 10);
    load_single_value(val2);
    add_code("STORE", 16);
    add_code("STORE", 11);
    add_code("SUB", 0); //multiplier 
    add_code("INC");
    add_code("STORE", 14);
    //checking if val2 == ZERO
    add_code("LOAD", 11);
    add_code("JZERO", k+2);
    add_code("JUMP", k+6);
    add_code("SUB", 0); 
    add_code("STORE", 10);
    add_code("STORE", 11);
    add_code("STORE", 14);
    add_code("STORE", 12);

    //evaluate_sign_and_abs(10); cuz result should have same sign as DZIELNIK
    //evaluate_sign_and_abs(11);
    //evaluate_sign_and_abs(10);

    add_code("LOAD", 11);
    add_code("JPOS", k+7);
    add_code("LOAD", 13);
    add_code("INC");
    add_code("STORE", 13);
    add_code("SUB", 0);
    add_code("SUB", 11);
    add_code("STORE", 11);

    add_code("SUB", 0);
    add_code("STORE", 17);

    add_code("LOAD", 10);
    add_code("JPOS", k+7);
    add_code("SUB", 0);
    add_code("INC");
    add_code("STORE", 17);
    add_code("SUB", 0);
    add_code("SUB", 10);
    add_code("STORE", 10);



    // a = REMAIN (10) ; b = SCALED_DIVISOR (11)
    int beginning = k;
    //	while(divisor < dividend)
    add_code("LOAD", 11);
    add_code("SUB", 10);
    add_code("JPOS", k+9);
    add_code("JZERO", k+8); 
     // Multiply "b" by two.
    add_code("LOAD", 11);
    add_code("ADD", 11);
    add_code("STORE", 11);
    // multiplier multiply by two.
    add_code("LOAD", 14);
    add_code("ADD", 14);
    add_code("STORE", 14);
    add_code("JUMP", beginning);
    //do
    int do_beginning = k;
    //IF (remain >= scaled_divisor)
    add_code("LOAD", 10);
    add_code("SUB", 11);
    add_code("JNEG", k+7);
    // remain = remain - scaled_divisor;
    add_code("LOAD", 10);
    add_code("SUB", 11);
    add_code("STORE", 10);
    // result = result + multiple;
    add_code("LOAD", 12);
    add_code("ADD", 14);
    add_code("STORE", 12);
    //END_IF
    //DIVIDING BY TWO: b and multiply
    add_code("LOAD", 11);
    add_code("SHIFT", 2);
    add_code("STORE", 11);
    add_code("LOAD", 14);
    add_code("SHIFT", 2);
    add_code("STORE", 14);
    
    //WHILE  multiply !=0
    add_code("LOAD", 14);
    add_code("JNEG", do_beginning);
    add_code("JPOS", do_beginning);

    //a w 17, b w 13

    //case when BOTH where negative
    add_code("LOAD", 17);
    add_code("ADD", 13);
    add_code("DEC");
    add_code("DEC");
    add_code("JZERO", k+2);
    add_code("JUMP", k+5);
    add_code("SUB", 0);
    add_code("SUB", 10);
    add_code("STORE", 10);
    add_code("JUMP", k+14); //jump all the way down

    //case when B is negative
    add_code("LOAD", 13);  // SHOULD be the case when a -b
    add_code("JZERO", k+4);
    add_code("LOAD", 10);
    add_code("ADD", 16);
    add_code("STORE", 10);  

    //case when A is negative
    add_code("LOAD", 17);
    add_code("JZERO", k+7);
    add_code("LOAD", 10);
    add_code("SUB", 16);
    add_code("STORE", 10);
    add_code("SUB", 0);
    add_code("SUB", 10);
    add_code("STORE", 10);  
    
    add_code("LOAD", 10, " # MOD END");

}



bool is_number(const std::string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}