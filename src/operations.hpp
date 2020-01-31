#include <iostream>
#include <string>

using namespace std;


void add(char** val1, char** val2, int line);

void sub(char** val1, char** val2, int line);

void mul(char** val1, char** val2, int line);

void div(char** val1, char** val2, int line);

void mod(char** val1, char** val2, int line);

bool is_number(const string& s);

//if negative negates sign flag(mem[13]) and makes value absoulute
void evaluate_sign_and_abs(int adrr);

//if negative flag set to 1 reverses result
void check_sign_flag_and_reverse_result(int addr);
