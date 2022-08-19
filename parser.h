/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    WHILE = 260,
    FOR = 261,
    FUNCTION = 262,
    RETURN = 263,
    BREAK = 264,
    CONTINUE = 265,
    AND = 266,
    OR = 267,
    NOT = 268,
    LOCAL_TOKEN = 269,
    TRUE = 270,
    FALSE = 271,
    NIL = 272,
    OPERATOR_ASSIGN = 273,
    OPERATOR_PLUS = 274,
    OPERATOR_MINUS = 275,
    OPERATOR_MUL = 276,
    OPERATOR_DIV = 277,
    OPERATOR_MOD = 278,
    OPERATOR_EQUALS = 279,
    OPERATOR_NOT_EQUALS = 280,
    OPERATOR_INCREMENT = 281,
    OPERATOR_DECREMENT = 282,
    OPERATOR_GREATER = 283,
    OPERATOR_GREATER_EVEN = 284,
    OPERATOR_LESS = 285,
    OPERATOR_LESS_EVEN = 286,
    CONST_INT = 287,
    REAL_NUMBER = 288,
    ID = 289,
    COLON = 290,
    SEMICOLON = 291,
    BRACKET_OPEN = 292,
    BRACKET_CLOSE = 293,
    CURLY_BRACKET_OPEN = 294,
    CURLY_BRACKET_CLOSE = 295,
    OPENING_PARENTHESIS = 296,
    CLOSING_PARENTHESIS = 297,
    SCOPE = 298,
    RANGE = 299,
    DOT = 300,
    STR = 301,
    COMMA = 302,
    UMINUS = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "parser.y"

    char* stringValue;
    int intValue;
    double realValue;
    struct expr *exprNode;
    struct call *calls;
    struct stmt_t* stmts;
    struct for_pref* fors;

#line 116 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
