#include "loops.hpp"
#include "conditions.hpp"
#include<vector>
using namespace std;

stack<for_loop> for_loops;
stack<while_loop> while_loops;

void loop_for(char* it_name, char** iterator, char** to_value, bool downto, int line){

    for_loop new_loop;
    new_loop.name=it_name;
    var it;
    it.mem_addr= free_mem_idx++;
    
    load_single_value(iterator);
    add_code("STORE", it.mem_addr, "#FOR_BEGINING");

    var to_value_var;
    to_value_var.mem_addr=free_mem_idx++;
    
    load_single_value(to_value);
    add_code("STORE", to_value_var.mem_addr);

    if(downto){
        add_code("LOAD", it.mem_addr);
        add_code("SUB", to_value_var.mem_addr);
    }else{
        add_code("LOAD", to_value_var.mem_addr);
        add_code("SUB", it.mem_addr);
    }
    new_loop.loop_end = k;
    add_code("JNEG", k, " #SOMEHOW_END");

    variables.insert(make_pair(it_name, it));
    new_loop.iterator=it;
    new_loop.to_value=to_value_var;
    new_loop.j=k;
    new_loop.downto=downto;
    for_loops.push(new_loop);
}



void end_loop_for(int line){
    for_loop loop = for_loops.top();
    for_loops.pop();
    add_code("LOAD", loop.iterator.mem_addr, "# BEG_OF_END_FOR");

    if(loop.downto){
        add_code("DEC");
    }else{
        add_code("INC");

    }
    add_code("STORE", loop.iterator.mem_addr);
        //condtition check
    add_code("LOAD", loop.to_value.mem_addr);
    add_code("SUB", loop.iterator.mem_addr);

    if(loop.downto){
        add_code("JNEG", loop.j);
    }else{
        add_code("JPOS", loop.j);
    }
    add_code("JZERO", loop.j);
    code.at(loop.loop_end) = "JNEG " + to_string(k-1) ;
    variables.erase(loop.name);
}


//konwencja: mem_addr_3>0 - true | <=0 -false
void loop_while(int line){
    while_loop loop;
    loop.k_start=k;
    loop.k_end = k;
    add_code("LOAD", 3, " #WHILE_START");
    add_code("JNEG",loop.k_end); //this will be changed
    loop.jneg_addr=k-1;
    while_loops.push(loop);
}

void end_loop_while(int line){
    while_loop loop = while_loops.top();
    while_loops.pop();
    cond_flag flag = cond_flags.top();

    add_code("JUMP", flag.expr_start, " #WHILE_END");
    code.at(loop.jneg_addr)="JNEG " + to_string(k);
    cond_flags.pop();
}

void begin_do_while(int line){
   while_loop loop;
   loop.k_start=k; 
    while_loops.push(loop);
}

void end_do_while(int line){
    while_loop loop = while_loops.top();
    while_loops.pop();

    add_code("LOAD", 3);
    add_code("JPOS", loop.k_start, " #END DO_WHILE");
    cond_flags.pop();
}

void if_loop(int line){
    cond_flag flag = cond_flags.top();
    cond_flags.pop();

    string tp1 = "LOAD " + to_string(flag.boolean.mem_addr) + " #IF BEGINING";
    string tp2 = "JNEG " + to_string(k);
    code.at(flag.k_start-2)=tp1;
    code.at(flag.k_start-1)=tp2;
}

void if_else_loop(int line){
    cond_flag &flag = cond_flags.top();

    string tp1 = "LOAD " + to_string(flag.boolean.mem_addr) + " #IFELSEE BEGINING";
    string tp2 = "JNEG " + to_string(k);

    code.at(flag.k_start-2)=tp1;
    code.at(flag.k_start-1)=tp2;
    flag.k_end=k;
    add_code("INC #LOOP ACCESS <- SHOULD DISSAPEAR");
    add_code("INC #LOOP ACCESS <- SHOULD DISSAPEAR");
}

void add_else(int line){
    cond_flag flag = cond_flags.top();
    cond_flags.pop();
    string tp1="LOAD " + to_string(flag.boolean.mem_addr) + " #IF ELSE MIDDLE";
    string tp2="JPOS " + to_string(k);
    code.at(flag.k_end)=tp1;
    code.at(flag.k_end+1)=tp2;

}