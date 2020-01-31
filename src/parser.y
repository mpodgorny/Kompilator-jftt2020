%{
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include "logic.hpp"
#include "operations.hpp"
#include "loops.hpp"
#include "conditions.hpp"

int yylex();
int yyparse();
void yyerror(char const *s);
extern FILE *yyin;
extern int yylineno;


%}

%union {
    char* pid;
    char* num;
    char* temp[2];
}


%start program
%token DECLARE T_BEGIN END
%token <pid> IF WHILE DO
%token <pid> FOR 
%token THEN ELSE ENDIF FROM TO DOWNTO ENDFOR ENDWHILE ENDDO
%token READ WRITE       
%token LE GE LEQ GEQ EQ NEQ
%token ASSIGN
%token ERROR
%token <pid> pidentifier
%token <pid> num
%token ADD

%type <temp> value
%type <temp> identifier
%type <pid> condition
%type <pid> expression
%left SUB
%left MUL DIV MOD
%%      

program:        
        DECLARE declarations T_BEGIN commands END                               { end();}
        | T_BEGIN commands END                                                  { end();}
;

declarations:   
        declarations ',' pidentifier                                            { declaration($3, yylineno);           }
        | declarations ',' pidentifier '(' num ':' num ')'                      { declaration($3, $5, $7, yylineno);   }
        | pidentifier                                                           { declaration($1, yylineno);           }
        | pidentifier '(' num ':' num ')'                                       { declaration($1, $3, $5, yylineno);   }                                                     
;

commands:       commands command
                | command       
;


command:        identifier  ASSIGN expression';'                                  { assign($1, yylineno);                }

                | IF condition THEN commands                                      { if_else_loop(yylineno);               }                  
                        ELSE commands ENDIF                                       { add_else(yylineno);                   }               

                | IF condition THEN                                                     
                        commands ENDIF                                            { if_loop(yylineno);}             

                | WHILE  condition                                                { loop_while(yylineno);                 }
                        DO commands ENDWHILE                                     { end_loop_while(yylineno);             }           

                | DO                                                             { begin_do_while(yylineno);             }
                    commands WHILE condition ENDDO                               { end_do_while(yylineno);               }

                | FOR pidentifier FROM value TO value                            { loop_for($2, $4, $6, false, yylineno);}
                        DO commands ENDFOR                                       { end_loop_for(yylineno);               }

                | FOR pidentifier FROM value DOWNTO value                        { loop_for($2, $4, $6, true, yylineno); }
                        DO commands ENDFOR                                       { end_loop_for(yylineno);               }

                | READ identifier';'                                             { read($2);   }
                | WRITE value';'                                                 { write($2);  }
;

expression:     value                                                            { load_single_value($1); }
                | value ADD value                                                { add($1, $3, yylineno); }
                | value SUB value                                                { sub($1, $3, yylineno); }
                | value MUL value                                                { mul($1, $3, yylineno); }
                | value DIV value                                                { div($1, $3, yylineno); }
                | value MOD value                                                { mod($1, $3, yylineno); }
;

condition:      value EQ value                                                   { exp_eq($1, $3, yylineno);     }
                | value NEQ value                                                { exp_neq($1, $3, yylineno);    }
                | value LE value                                                 { exp_le($1, $3, yylineno);     }
                | value GE value                                                 { exp_ge($1, $3, yylineno);     }
                | value LEQ value                                                { exp_leq($1, $3, yylineno);    }
                | value GEQ value                                                { exp_geq($1, $3, yylineno);    }
;

value:          num                                                              { $$[0]=$1;$$[1]=NULL;         }
                | identifier                                                     { }
;

identifier:     pidentifier                                                      {$$[0]=$1; $$[1]=NULL; identifier_pid($1, yylineno);         }
                | pidentifier '(' pidentifier ')'                                {$$[0]=$1; $$[1]=$3; identifier_pid_pid($1, $3, yylineno);}
                | pidentifier '(' num ')'                                        {$$[0]=$1; $$[1]=$3; identifier_pid_num($1, $3, yylineno);}
;


%%


int main(int argc, char* argv[]) {
        
        
                std::cout<<"\n\n\t|/  _  ._ _  ._  o |  _. _|_  _  ._ "<<std::endl;
                std::cout<<"\t|\\ (_) | | | |_) | | (_|  |_ (_) |  "<<std::endl;
                std::cout<<"\t             |                       "<<std::endl;


        std::cout << "\t\t\033[;36m By Michał Podgórny\n" << std::endl;
        if(argc != 3){
                std::cout<<"\x1b[31mUsage: ./compiler <input_file> <output.file>\nAborting...\n";
        
        } else{
                yyin = fopen(argv[1], "r");
                if (yyin == NULL){
                        std::cout<<"\x1b[31mGiven input fie was not found.\nAborting...\n";
                        std::exit(1);
                        
                } else{
                std::cout<< "\t\033[;32m------------Compiling------------" << std::endl;
                generate_shifters();
                yyparse();
                std::cout<<"\t \033[;32m------------SUCCES------------\n\033[;0m";
                save_to_file(argv[2]);
                return 0;
                }
        }
}

void yyerror(char const *s) {
        std::cerr <<"\x1b[31munrecognized token line " << yylineno << "\nAborting...\n"<< std::endl;
        exit(0);
}
