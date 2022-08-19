%{
    #include "utils/utils.h"
    #include "utils/symtable.h"
    #include "utils/final_code.h"
    #include "parser.h"

    int yyerror (const char* message);
    int yylex();
    void print_all();
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;
    extern FILE* yyout;
    extern int curr_scope;
    extern int loop_c;
    extern int temp_c;
    extern int is_func;
    extern int functionLocalOffset;
    extern SymTable_T hash_table;

%}

%defines
%start program
%expect 1


%union {
    char* stringValue;
    int intValue;
    double realValue;
    struct expr *exprNode;
    struct call *calls;
    struct stmt_t* stmts;
    struct for_pref* fors;
}


%token IF
%token ELSE
%token WHILE
%token FOR
%token FUNCTION
%token RETURN
%token BREAK
%token CONTINUE
%token AND
%token OR
%token NOT
%token LOCAL_TOKEN
%token TRUE
%token FALSE
%token NIL

%token OPERATOR_ASSIGN
%token OPERATOR_PLUS
%token OPERATOR_MINUS
%token OPERATOR_MUL
%token OPERATOR_DIV
%token OPERATOR_MOD
%token OPERATOR_EQUALS
%token OPERATOR_NOT_EQUALS
%token OPERATOR_INCREMENT
%token OPERATOR_DECREMENT
%token OPERATOR_GREATER
%token OPERATOR_GREATER_EVEN
%token OPERATOR_LESS
%token OPERATOR_LESS_EVEN

%token <intValue> CONST_INT
%token <realValue> REAL_NUMBER
%token <stringValue> ID
%token COLON
%token SEMICOLON
%token BRACKET_OPEN
%token BRACKET_CLOSE
%token CURLY_BRACKET_OPEN
%token CURLY_BRACKET_CLOSE
%token OPENING_PARENTHESIS
%token CLOSING_PARENTHESIS
%token SCOPE
%token RANGE
%token DOT
%token <stringValue> STR
%token COMMA


%right OPERATOR_ASSIGN

%left COMMA
%left OR
%left AND

%nonassoc OPERATOR_EQUALS OPERATOR_NOT_EQUALS
%nonassoc OPERATOR_GREATER OPERATOR_GREATER_EVEN OPERATOR_LESS OPERATOR_LESS_EVEN

%left OPERATOR_PLUS OPERATOR_MINUS
%left OPERATOR_MUL OPERATOR_DIV OPERATOR_MOD

%right NOT OPERATOR_INCREMENT OPERATOR_DECREMENT UMINUS

%left DOT RANGE
%left BRACKET_OPEN BRACKET_CLOSE
%left OPENING_PARENTHESIS CLOSING_PARENTHESIS
%left CURLY_BRACKET_OPEN CURLY_BRACKET_CLOSE

%type <exprNode> elist
%type <exprNode> expr
%type <exprNode> const
%type <exprNode> term
%type <exprNode> primary
%type <exprNode> assignexpr
%type <exprNode> member
%type <exprNode> call
%type <exprNode> funcdef
%type <exprNode> objectdef
%type <exprNode> lvalue
%type <exprNode> elistexpr_list
%type <exprNode> funcprefix
%type <exprNode> indexedelem
%type <exprNode> indexedelem_list
%type <exprNode> indexed

%type <calls> callsuffix
%type <calls> normcall
%type <calls> methodcall

%type <stmts> breakstmt
%type <stmts> continuestmt
%type <stmts> stmt
%type <stmts> stmt_list
%type <stmts> block
%type <stmts> ifstmt

%type <fors> forprefix

%type <stringValue> funcname
%type <intValue> funcbody

%type <intValue> whilestart
%type <intValue> whilecond
%type <intValue> N
%type <intValue> M
%type <intValue> ifprefix
%type <intValue> elseprefix

%%

program: stmt_list;

stmt: expr SEMICOLON {$$ = NULL; temp_c = 0;}
| ifstmt       {$$ = $1; temp_c = 0;}
| whilestmt    {$$ = NULL; temp_c = 0;}
| forstmt      {$$ = NULL; temp_c = 0;}
| returnstmt   {$$ = NULL; temp_c = 0;}
| breakstmt    {$$ = $1;}
| continuestmt {$$ = $1;}
| block        {$$ = $1; temp_c = 0;}
| funcdef      {$$ = NULL; temp_c = 0;}
| SEMICOLON    {$$ = NULL; temp_c = 0;}
;

stmt_list: stmt {$$ = $1;}
|  stmt_list stmt {$$ = do_stmtlist($1, $2);}
;

expr: assignexpr                                    {$$ = $1;}
| expr OPERATOR_PLUS expr                           {$$ = do_op($1,$3,add);}
| expr OPERATOR_MINUS expr                          {$$ = do_op($1,$3,sub);}
| expr OPERATOR_MUL expr                            {$$ = do_op($1,$3,mul);}
| expr OPERATOR_DIV expr                            {$$ = do_op($1,$3,div_op);}
| expr OPERATOR_MOD expr                            {$$ = do_op($1,$3,mod);}
| expr OPERATOR_LESS expr                           {$$ = do_relop($1,$3,if_less);}
| expr OPERATOR_LESS_EVEN expr                      {$$ = do_relop($1,$3,if_lesseq);}
| expr OPERATOR_GREATER_EVEN expr                   {$$ = do_relop($1,$3,if_greatereq);}
| expr OPERATOR_GREATER expr                        {$$ = do_relop($1,$3,if_greater);}
| expr OPERATOR_EQUALS expr                         {$$ = do_relop($1,$3,if_eq);}
| expr OPERATOR_NOT_EQUALS expr                     {$$ = do_relop($1,$3,if_noteq);}
| expr AND expr                                     {$$ = do_boolop($1,$3,and_op);}
| expr OR expr                                      {$$ = do_boolop($1,$3,or_op);}
| term                                              {$$ = $1;}
| error                                             {yyclearin;}
;


term : OPENING_PARENTHESIS expr CLOSING_PARENTHESIS { $$ = $2; }
| primary                                           { $$ = $1; }
| OPERATOR_MINUS expr %prec UMINUS                  {$$ = do_uminus($2);}
| NOT expr                                          {$$ = do_not($2);}
| OPERATOR_INCREMENT lvalue                         {$$ = do_pre_dec_inc($2,add);}
| lvalue OPERATOR_INCREMENT                         {$$ = do_post_dec_inc($1,add);}
| OPERATOR_DECREMENT lvalue                         {$$ = do_pre_dec_inc($2,sub);}
| lvalue OPERATOR_DECREMENT                         {$$ = do_post_dec_inc($1,sub);}
;

assignexpr : lvalue OPERATOR_ASSIGN expr            {$$ = do_assign($1 , $3);}
            ;

primary : lvalue                                    { $$ = emit_iftableitem($1); }
| call                                              { $$ = $1; }
| objectdef                                         { $$ = $1; }
| OPENING_PARENTHESIS funcdef CLOSING_PARENTHESIS   { $$ = do_par_funcdef($2); }
| const                                             { $$ = $1; }
;

lvalue : ID             {$$ = do_var($1);}
| LOCAL_TOKEN ID        {$$ = do_local_var($2);}
| SCOPE ID              {$$ = do_scope_var($2);}
| member                {$$ = $1;}
;

member : lvalue DOT ID                      {$$ = member_item($1 , $3);}
| lvalue BRACKET_OPEN expr BRACKET_CLOSE    {$$ = array_item($1 , $3);}
| call DOT ID                               {$$ = member_item($1 , $3);}
| call BRACKET_OPEN expr BRACKET_CLOSE      {$$ = array_item($1 , $3);}
;

call : call OPENING_PARENTHESIS elist CLOSING_PARENTHESIS {$$ = make_call($1,$3);}
| lvalue callsuffix {$$ = do_lvalue_call($1,$2);}
| OPENING_PARENTHESIS funcdef CLOSING_PARENTHESIS OPENING_PARENTHESIS elist CLOSING_PARENTHESIS { $$ = do_funcdef_call($2,$5); }
;

callsuffix: normcall {$$ = $1;}
| methodcall         {$$ = $1;}
;

normcall : OPENING_PARENTHESIS elist CLOSING_PARENTHESIS {$$ = do_normcall($2);}
            ;


methodcall : RANGE ID OPENING_PARENTHESIS elist CLOSING_PARENTHESIS {$$ = do_methodcall($2,$4);}
        ;

elist : expr elistexpr_list { $$ = do_elist($1,$2); }
        | { $$ = NULL; }
        ;

elistexpr_list: COMMA expr elistexpr_list { $$ = do_elist($2,$3); }
         | { $$ = NULL; }
         ;

objectdef: BRACKET_OPEN elist BRACKET_CLOSE     { $$ = make_table($2); }
           | BRACKET_OPEN indexed BRACKET_CLOSE { $$ = make_table_pairs($2);}
           ;

indexed : indexedelem indexedelem_list {$$ = make_indexedelem_list($1,$2);}
          ;

indexedelem_list: COMMA indexedelem indexedelem_list {$$ = make_indexedelem_list($2,$3);}
                  | {$$ = NULL;}
                  ;

indexedelem: CURLY_BRACKET_OPEN expr COLON expr CURLY_BRACKET_CLOSE {$$ = make_indexedelem($2,$4);}
            ;

funcname: ID {$$ = $1;}
        | {$$ = new_afunction();}
        ;

funcprefix: FUNCTION funcname {$$ = do_function($2);}
          ;


funcargs: OPENING_PARENTHESIS idlist CLOSING_PARENTHESIS {enter_scopespace();}
        ;


funcblockstart: {new_loop(loop_c); loop_c = 0;}
              ;


funcblockend: {void exit_loop();}
            ;


funcbody: funcblockstart block funcblockend {$$ = functionLocalOffset;}
        ;


funcdef: funcprefix funcargs funcbody {exit_func($1, $3);}
         ;

block: CURLY_BRACKET_OPEN {curr_scope++;} stmt_list CURLY_BRACKET_CLOSE {curr_scope--; SymTable_hide(curr_scope); $$ = $3;}
       |CURLY_BRACKET_OPEN CURLY_BRACKET_CLOSE {$$ = NULL;};
       ;

const: CONST_INT       { $$ = newexpr_constint($1);}
        | REAL_NUMBER  { $$ = newexpr_constnum($1);}
        | STR          { $$ = newexpr_conststring($1);}
        | NIL          { $$ = newexpr_constnil();}
        | TRUE         { $$ = newexpr_constbool(1);}
        | FALSE        { $$ = newexpr_constbool(0);}
        ;

idlist: ID { $<exprNode>$ = do_idlist($1);} moreID
        |
        ;

moreID: COMMA ID { $<exprNode>$ = do_moreID($2); } moreID
        |
        ;

ifprefix:  IF OPENING_PARENTHESIS expr CLOSING_PARENTHESIS { $$ = do_ifprefix($3);}
        ;

elseprefix: ELSE { $$ = nextquad(); emit(jump, NULL, NULL, NULL, 0, yylineno); }
        ;

ifstmt: ifprefix stmt {$$ = $2;  patchlabel($1, nextquad());}
        | ifprefix stmt elseprefix stmt  {  patchlabel($1, $3 + 1); patchlabel($3, nextquad()); $$ = do_ifelse($2, $4);}
        ;

whilestart: WHILE { $$ = nextquad();}
        ;

whilecond: OPENING_PARENTHESIS expr CLOSING_PARENTHESIS{$$ = do_whilecond($2);}
        ;

whilestmt: whilestart whilecond{loop_c++;} stmt {loop_c--; do_whilestmt($1,$2,$4);}
        ;

N: {$$ = nextquad(); emit(jump,NULL, NULL, NULL, 0, yylineno);}
        ;

M: {$$ = nextquad();}
        ;

forprefix: FOR OPENING_PARENTHESIS elist SEMICOLON M expr SEMICOLON {$$ = do_forprefix($5,$6);}
        ;

forstmt: forprefix N elist CLOSING_PARENTHESIS {++loop_c;} N stmt N { do_forstmt($1,$2,$6,$7,$8);}
         ;

returnstmt: RETURN  expr SEMICOLON { if (is_func <= 0) yyerror("Use of return out of function"); emit(ret,$2,NULL,NULL,nextquad(),yylineno); push_returnlist(nextquad()); emit(jump,NULL,NULL,NULL,0,yylineno); }
          | RETURN SEMICOLON  { if (is_func <= 0) yyerror("Use of return out of function"); emit(ret,NULL,NULL,NULL,nextquad(),yylineno); push_returnlist(nextquad()); emit(jump,NULL,NULL,NULL,0,yylineno); }
          ;

breakstmt: BREAK SEMICOLON {$$ = do_break_continue(0);}

continuestmt: CONTINUE SEMICOLON {$$ = do_break_continue(1);}
%%

int main(int argc, char **argv)
{

    if (argc > 1)
    {
        if (!(yyin = fopen(argv[1], "r")))
        {
            fprintf(stderr, "Can't open file: %s\n", argv[1]);
            return 1;
        }
    }
    else
    {
        yyin = stdin;
    }
    if (argc > 2)
    {
        yyout = fopen(argv[2], "w");
    }
    else
        yyout = stdout;

    hash_table = SymTable_new();
    siuuuu_lib_funcs();
    yyparse();
    printQuads();
    generator();

    return 0;
}