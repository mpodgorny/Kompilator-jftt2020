#include<stack>
#include "logic.hpp"

using namespace std;

struct cond_flag{
    int k_start;
    int k_end;
    var boolean;
};

extern stack<cond_flag> cond_flags;


void exp_eq(char** val1, char** val2, int line);

void exp_neq(char** val1, char** val2, int line);

void exp_le(char** val1, char** val2, int line);

void exp_ge(char** val1, char** val2, int line);

void exp_leq(char** val1, char** val2, int line);

void exp_geq(char** val1, char** val2, int line);