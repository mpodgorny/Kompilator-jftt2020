%{
#include <iostream>
#include <string>
#include "logic.hpp"
#include "operations.hpp"

int yylex();
int yyparse();
void yyerror(char const *s);
extern FILE *yyin;
extern int yylineno;

const std::string error_alert = "\x1b[31merror\x1b[0m: ";


%}

%union {
    char* pid;
    char* num;
}


//Tokens
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

//Types
%type <pid> value
%type <pid> identifier
%type <pid> condition;

//Operators precedence
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


command:        identifier  ASSIGN expression';'                                        {std::cout<<"ASSIGN\n";  assign($1, yylineno); }

                | IF condition THEN commands                                            { }                   
                  ELSE commands ENDIF                                                   { }               

                | IF condition THEN commands ENDIF                                      { }             

                | WHILE condition DO commands ENDWHILE                                  { }    

                | DO commands WHILE condition ENDDO                                     { }
                | FOR pidentifier FROM value TO value DO commands ENDFOR                {std::cout<<"FOR\n"; }

                | FOR pidentifier FROM value DOWNTO value DO commands ENDFOR            { }

                | READ identifier';'                                                    { std::cout<<"read: "<<$2<<std::endl; read($2);    }
                | WRITE value';'                                                        { std::cout<<"write: "<<$2<<std::endl; write($2);   }
;

expression:     value                                                                   { }
                | value ADD value                                                       { add($1, $3, yylineno); }
                | value SUB value                                                       { sub($1, $3, yylineno); }
                | value MUL value                                                       { mul($1, $3, yylineno); }
                | value DIV value                                                       { div($1, $3, yylineno); }
                | value MOD value                                                       { mod($1, $3, yylineno); }
;

condition:      value EQ value                                                          { }
                | value NEQ value                                                       { }
                | value LE value                                                        { }
                | value GE value                                                        { }
                | value LEQ value                                                       { }
                | value GEQ value                                                       { }
;

value:          num                                                                     {std::cout<<"VAL\n";  value_num($1, yylineno); }
                | identifier                                                             
;

identifier:     pidentifier                                                             {identifier_pid($1, yylineno);}
                | pidentifier '(' pidentifier ')'                                       {identifier_pid_pid($1, $3, yylineno); }
                | pidentifier '(' num ')'                                               {identifier_pid_num($1, $3, yylineno); }
;


%%


int main(int argc, char* argv[]) {
        std::cout << "\tCompiler by me\n------------Compiling------------" << std::endl;
        if(argc != 3)
                std::cout<<"Usage: ./compiler <input_file> <output.file>\nAborting...";
        
        yyin = fopen(argv[1], "r");
        
        if (yyin == NULL)
                std::cout<<"Given input fie was not found.\nAborting...";
        
        yyparse();
        std::cout<<"------------Probably succes xd------------\n";
        save_to_file(argv[2]);
        return 0;

}

void yyerror(char const *s) {
        std::cerr << error_alert << s << " - unrecognized token (line " << yylineno << ")" << std::endl;
        std::cerr << "### \x1b[31mErrors occured\x1b[0m ###" << std::endl;
        exit(0);
}
