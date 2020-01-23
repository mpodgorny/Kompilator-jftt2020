#include <iostream>
#include <string>

using namespace std;


void add(char** val1, char** val2, int line);

void sub(char** val1, char** val2, int line);

void mul(char** val1, char** val2, int line);

void div(char** val1, char** val2, int line);

void mod(char** val1, char** val2, int line);

bool is_number(const string& s);

void evaluate_sign_and_abs(int adrr);

void check_sign_flag_and_reverse_result(int addr);

void div_low(char** val1, char** val2, int line);