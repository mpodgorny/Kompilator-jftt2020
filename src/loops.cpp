#include "loops.hpp"
#include "conditions.hpp"
#include<vector>
using namespace std;

stack<for_loop> for_loops;
stack<while_loop> while_loops;

void loop_for(char* it_name, char* iterator, char* to_value, bool downto, int line){

    for_loop new_loop;
    new_loop.name=it_name;

    
    var original_it = variables.at(iterator);
    var it;
    it.mem_addr= free_mem_idx++;
    
    add_code("LOAD", original_it.mem_addr);
    add_code("STORE", it.mem_addr);

    
    var original_to_value_var = variables.at(to_value);
    var to_value_var;
    to_value_var.mem_addr=free_mem_idx++;
    
    add_code("LOAD", original_to_value_var.mem_addr);
    add_code("STORE", to_value_var.mem_addr);

    if(downto){
        add_code("LOAD", it.mem_addr);
        add_code("SUB", to_value_var.mem_addr);
    }else{
        add_code("LOAD", to_value_var.mem_addr);
        add_code("SUB", it.mem_addr);
    }
    new_loop.loop_end = k;
    add_code("JNEG", k);

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
    add_code("LOAD", loop.iterator.mem_addr);

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
    code.at(loop.loop_end) = "JNEG " + to_string(k-1);
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
    add_code("JUMP", loop.k_start, " #WHILE_END");
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
    string temp = "LOAD "+ to_string(flag.boolean.mem_addr) +"\nJNEG " + to_string(k+2) + " #IF JUMP";
    auto it = code.insert(code.begin()+flag.k_start-2, temp); 
    k+=2;
}

void if_else_loop(int line){
    cond_flag &flag = cond_flags.top();

    string temp = "LOAD "+ to_string(flag.boolean.mem_addr) +" #IF\nJNEG " + to_string(k+2) + " #IF_ELSE FIRST JUMP";
    auto it = code.insert(code.begin()+flag.k_start, temp); 
    k+=2;
    flag.k_end=k;
}

void add_else(int line){
    cond_flag flag = cond_flags.top();
    cond_flags.pop();
    string temp="LOAD "+ to_string(flag.boolean.mem_addr) + " # ELSE\nJPOS " + to_string(k+2) + " #jump if condition was true";
    auto it = code.insert(code.begin()+flag.k_end-1, temp); 
    k+=2;
}

/*
void adjust_loops(int adj){
    while_loop while_arr[while_loops.size];
    for_loop for_arr[for_loops.size];
    int it = 0;

    while(!for_loops.empty){
        for_loop loop = for_loops.top();
        for_arr[it++];
        for_loops.pop();
    }
    while(!while_loops.empty){
        while_loop loop = while_loops.top();
        while_arr[it++];
        while_loops.pop();
    }

}
*/