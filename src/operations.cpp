#include "operations.hpp"
#include "logic.hpp"

using namespace std;
// 1 <- 0 ; 2 <- 1  4 <--1
//3 <- loop bool 4-10 <-arr operations ; 10-20 <- arithemtic operations
void add(char** val1, char** val2, int line){
    load_single_value(val1);
    add_code("STORE", 10);
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
    // 	uint_type a      = original_1;
	// uint_type b      = original_2;
	// uint_type result = 0;
	// while(a != 0)
	// {
	//     if(a & 1) // If the lowest order bit is set in A?
	//     {
	//         result = result + b;
	//     }
	//     a = a >> 1; // Note: This must set highest order bit ZERO. It must not copy the sign bit.
	//     b = b + b;  // Alternatively, left-shift by 1 bit
	// }


    // add_code("SUB", 0);
    // add_code("STORE", 10); // <--- Result at 11
    // load_single_value(val1);
    // add_code("STORE", 11);
    // load_single_value(val2);
    // add_code("STORE", 12);
    
    // long long int before_k=k;
    // add_code("LOAD", 11); // WHILE: 3 lines
    // add_code("JZERO", k+2);
    // add_code("JUMP", k+10); // <===uzupelnic po skonczeniu

    // add_code("")

}

void div(char** val1, char** val2, int line){
    // var temp1, temp2;
    // int counter = free_mem_idx++;
    // if(is_number(val1)){
    //     temp1.mem_addr=free_mem_idx++;
    //     generate_number(val1);
    //     add_code("STORE", temp1.mem_addr, " #DIV_ALLOCATING_MEM");
    // } else{
    //     temp1.mem_addr = free_mem_idx++;
    //     add_code("LOAD", variables.at(val1).mem_addr);
    //     add_code("STORE", temp1.mem_addr);
    // }
    // if(is_number(val2)){
    //     temp2.mem_addr=free_mem_idx++;
    //     generate_number(val2);
    //     add_code("STORE", temp2.mem_addr);
    // } else {
    //     temp2.mem_addr = free_mem_idx++;
    //     add_code("LOAD", variables.at(val2).mem_addr);
    //     add_code("STORE", temp2.mem_addr);    
    //     }

    // add_code("SUB", 0, " #DIV_START");
    // add_code("STORE", counter, " #COUNTER");
    // int j=k;
    // add_code("LOAD", temp2.mem_addr, " #test na dzielnik 0");
    // add_code("JZERO", j+11); //na koniec bo dzielenie przez zero
    
    // add_code("LOAD", temp1.mem_addr, " #WLASCIWY ALGO");
    // add_code("JZERO", j+11); 
    // add_code("SUB", temp2.mem_addr);
    // add_code("JNEG", j+11); //na koniec, zwracamy zero

    // add_code("STORE", temp1.mem_addr);
    // add_code("LOAD", counter);
    // add_code("INC");
    // add_code("STORE", counter);
    // add_code("JUMP", j+2); //skacz do zaladowania temp1
    // add_code("LOAD", counter, " #DIV_END");
}

//TODO: NEGATIVE NUMBERS
void mod(char** val1, char** val2, int line){
    // var temp1, temp2;
    // if(is_number(val1)){
    //     temp1.mem_addr=free_mem_idx++;
    //     generate_number(val1);
    //     add_code("STORE", temp1.mem_addr, " #MOD_ALLOCATING_MEM");
    // } else{
    //     temp1.mem_addr = free_mem_idx++;
    //     add_code("LOAD", variables.at(val1).mem_addr);
    //     add_code("STORE", temp1.mem_addr);
    // }
    // if(is_number(val2)){
    //     temp2.mem_addr=free_mem_idx++;
    //     generate_number(val2);
    //     add_code("STORE", temp2.mem_addr);
    // } else {
    //     temp2.mem_addr = free_mem_idx++;
    //     add_code("LOAD", variables.at(val2).mem_addr);
    //     add_code("STORE", temp2.mem_addr);    
    //     }
    
    // add_code("LOAD", temp2.mem_addr, " #MOD_START");
    // long long int j = k;
    // add_code("JZERO", j+6);
    // add_code("LOAD", temp1.mem_addr);
    // j = k;
    // add_code("SUB", temp2.mem_addr);
    // add_code("JPOS", j);
    // add_code("JZERO", j + 4);
    // add_code("ADD", temp2.mem_addr, " #MOD_END");
}

bool is_number(const std::string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}