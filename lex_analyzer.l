%{
    #include <stdio.h>
	  #include <string.h>
    #include <stdlib.h>
    #include "parser.h"

    int numToken = 1;
    int nesting = 0;
    int starts_at = 0;
    int ends_at = 0;
%}

%option outfile = "lex_analyzer.c"
%option noyywrap
%option yylineno

IF          "if"
ELSE        "else"
WHILE       "while"
FOR         "for"
FUNCTION    "function"
RETURN      "return"
BREAK       "break"
CONTINUE    "continue"
AND         "and"
OR          "or"
NOT         "not"
LOCAL_TOKEN "local"
TRUE        "true"
FALSE       "false"
NIL         "nil"

OPERATOR_ASSIGN          "="
OPERATOR_PLUS            "+"
OPERATOR_MINUS           "-"
OPERATOR_MUL             "*"
OPERATOR_DIV             "/"
OPERATOR_MOD             "%"
OPERATOR_EQUALS          "=="
OPERATOR_NOT_EQUALS      "!="
OPERATOR_INCREMENT       "++"
OPERATOR_DECREMENT       "--"
OPERATOR_GREATER         ">"
OPERATOR_GREATER_EVEN    ">="
OPERATOR_LESS            "<"
OPERATOR_LESS_EVEN       "<="

COMMENT_LINE_COMMENT     "//".*
BLOAT                    [ \t\n\r]*

CONST_INT                [1-9][0-9]*
REAL_NUMBER              [0-9]+\.[0-9]*
ID                       [a-zA-Z][a-zA-Z_0-9]*
COLON                    ":"
SEMICOLON                ";"
COMMA                    ","
BRACKET_OPEN             "["
BRACKET_CLOSE            "]"
CURLY_BRACKET_OPEN       "{"
CURLY_BRACKET_CLOSE       "}"
OPENING_PARENTHESIS      "("
CLOSING_PARENTHESIS      ")"
SCOPE                    "::"
RANGE                    ".."
DOT                      "."

%x STRING MULTI_COMMENT
%%

  char string_buffer[10000];
  char *string_buffer_ptr;

{IF}          {return IF;}
{ELSE}        {return ELSE;}
{WHILE}       {return WHILE;}
{FOR}         {return FOR;}
{FUNCTION}    {return FUNCTION;}
{RETURN}      {return RETURN;}
{BREAK}       {return BREAK;}
{CONTINUE}    {return CONTINUE;}
{AND}         {return AND;}
{NOT}         {return NOT;}
{OR}          {return OR;}
{LOCAL_TOKEN} {return LOCAL_TOKEN;}
{TRUE}        {return TRUE;}
{FALSE}       {return FALSE;}
{NIL}         {return NIL;}

{OPERATOR_ASSIGN}               {return OPERATOR_ASSIGN;}
{OPERATOR_PLUS}                 {return OPERATOR_PLUS;}
{OPERATOR_MINUS}                {return OPERATOR_MINUS;}
{OPERATOR_MUL}                  {return OPERATOR_MUL;}
{OPERATOR_DIV}                  {return OPERATOR_DIV;}
{OPERATOR_MOD}                  {return OPERATOR_MOD;}
{OPERATOR_EQUALS}               {return OPERATOR_EQUALS;}
{OPERATOR_NOT_EQUALS}           {return OPERATOR_NOT_EQUALS;}
{OPERATOR_INCREMENT}            {return OPERATOR_INCREMENT;}
{OPERATOR_DECREMENT}            {return OPERATOR_DECREMENT;}
{OPERATOR_GREATER}              {return OPERATOR_GREATER;}
{OPERATOR_LESS}                 {return OPERATOR_LESS;}
{OPERATOR_GREATER_EVEN}         {return OPERATOR_GREATER_EVEN;}
{OPERATOR_LESS_EVEN}            {return OPERATOR_LESS_EVEN;}

{COMMENT_LINE_COMMENT}          {}
{BLOAT}                         {}
"0"                             {yylval.intValue = atoi(yytext); return CONST_INT;}
{CONST_INT}                     {yylval.intValue = atoi(yytext); return CONST_INT;}
{REAL_NUMBER}                   {yylval.realValue = atof(yytext); return REAL_NUMBER;}
{ID}                            {yylval.stringValue = strdup(yytext); return ID;}

\"      string_buffer_ptr = string_buffer; BEGIN(STRING);

<STRING>\"        {
    BEGIN(INITIAL);
    *string_buffer_ptr = '\0';
    yylval.stringValue = strdup(string_buffer);
    return STR;
}

<STRING>\n        {
    BEGIN(INITIAL);
    fprintf(yyout, "Unterminated string constant at line %d.\n", yylineno);
}

<STRING>\\n  *string_buffer_ptr++ = '\n';
<STRING>\\t  *string_buffer_ptr++ = '\t';
<STRING>\\r  *string_buffer_ptr++ = '\r';
<STRING>\\b  *string_buffer_ptr++ = '\b';
<STRING>\\f  *string_buffer_ptr++ = '\f';

<STRING>\\(.|\n)  *string_buffer_ptr++ = yytext[1];    fprintf(yyout, "This shit be bloat in line %d.\n", yylineno);


<STRING>[^\\\n\"]+        {
    char *temp_yytext = yytext;
    while ( *temp_yytext )
        *string_buffer_ptr++ = *temp_yytext++;
}



{COLON}		                      {return COLON;}
{SEMICOLON}		                  {return SEMICOLON;}
{COMMA}                         {return COMMA;}
{BRACKET_OPEN}                  {return BRACKET_OPEN;}
{BRACKET_CLOSE}                 {return BRACKET_CLOSE;}
{CURLY_BRACKET_OPEN}		        {return CURLY_BRACKET_OPEN;}
{CURLY_BRACKET_CLOSE}		        {return CURLY_BRACKET_CLOSE;}
{OPENING_PARENTHESIS}           {return OPENING_PARENTHESIS;}
{CLOSING_PARENTHESIS}           {return CLOSING_PARENTHESIS;}
{DOT}                           {return DOT;}
{SCOPE}                         {return SCOPE;}
{RANGE}                         {return RANGE;}

"/*"  starts_at = yylineno; ends_at = yylineno; BEGIN(MULTI_COMMENT);

<MULTI_COMMENT>"*/" {
  if( nesting > 0 ) {
    nesting--;
  }
  else{
  BEGIN(0);
  }
}

<MULTI_COMMENT>"/*" {
  nesting++;
}

<MULTI_COMMENT>\n  ends_at++;

<MULTI_COMMENT>. { }


<MULTI_COMMENT><<EOF>> { BEGIN(0); fprintf(yyout, "File ends without comment ending\n"); }

. {fprintf(yyout, "Character at line %d is undefined\n", yylineno);}

%%

