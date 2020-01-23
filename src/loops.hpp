
#include <stack>
#include <deque>
#include "logic.hpp"

struct for_loop{
    var iterator;
    var to_value;
    var boolean;
    char* name;
    int j;
    bool ignore=false;
    bool downto;
    int loop_end;
};

struct while_loop{
    int k_start;
    int k_end;
    int jneg_addr;
    int expr_start;

};

extern stack<for_loop> for_loops;
extern stack<while_loop> while_loops;



void loop_for(char* it_name, char** iterator, char** to_value, bool downto, int line);    

void end_loop_for(int line);

void loop_while(int line);

void end_loop_while(int line);

void begin_do_while(int line);

void end_do_while(int line);

void if_loop(int line);

void if_else_loop(int line);

void add_else(int line);