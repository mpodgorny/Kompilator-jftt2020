%option noyywrap
%option yylineno
    
%{
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstring>
#include "parser.tab.h"


%}

%x COMMENT

IDENTIFIER              [_a-z]
NUMBER                   -?[0-9]
MISC                   [\(\)\:\;\,]


%%
"DECLARE"               { return DECLARE; }
"BEGIN"                 { return T_BEGIN; }
"END"                   { return END; }

"ASSIGN"                { return ASSIGN; }
"READ"                  { return READ; }
"WRITE"                 { return WRITE; }

"IF"                    { return IF; }
"THEN"                  { return THEN; }
"ELSE"                  { return ELSE; }
"ENDIF"                 { return ENDIF; }

"WHILE"                 { return WHILE; }
"DO"                    { return DO; }
"ENDWHILE"              { return ENDWHILE; }
"ENDDO"                 { return ENDDO; }

"FOR"                   { return FOR; }
"FROM"                  { return FROM; }
"TO"                    { return TO; }
"DOWNTO"                { return DOWNTO; }
"ENDFOR"                { return ENDFOR; }

"EQ"                     { return EQ; }
"NEQ"                    { return NEQ; }
"LE"                     { return LE; }
"GE"                     { return GE; }
"LEQ"                    { return LEQ; }
"GEQ"                    { return GEQ; }

"PLUS"                    { return ADD; }
"MINUS"                   { return SUB; }
"DIV"                     { return DIV; }
"MOD"                     { return MOD; }
"TIMES"                   { return MUL; }

{IDENTIFIER}+           { yylval.pid =(char *)strdup(yytext); return pidentifier; }
{NUMBER}+               { yylval.num =(char *)strdup(yytext); return num; }
{MISC}                  { return yytext[0]; }

"["                     { BEGIN(COMMENT); }

<COMMENT>{
    "["                 { return ERROR; } 
    "]"                 {BEGIN(INITIAL);}
    .                   ;
}
[ \t\r\n]+                { }
.                       { return ERROR; }
%%
