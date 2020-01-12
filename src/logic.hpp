#ifndef _LOGICHPP_
#define _LOGICHPP_

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>

using namespace std;

struct var {
    string name;
    string type;
    long long int value;
    long long int mem_addr;
	bool initialized;
	long long int begin;
	long long int size;
};

extern map<string, var> variables;
extern long long int free_mem_idx;
extern long long int k;
extern vector<string> code;

void declaration(char* identifier, int line);

void declaration(char* identifier, char* begining, char* end, int line);


void assign(char* name, int line);

void read(char* name);

void write(char* name);

void value_num(char* val, int line);

void identifier_pid(char* name, int line);

void identifier_pid_pid(char* name, char* idx, int line);

void identifier_pid_num(char* name, char* idx, int line);

void add_code(string snip);

void add_code(string snip, long long int val);

void add_code(string snip, long long int val, string comment);

void save_to_file(char* out);

void error(string msg, int line);

void end();

#endif