/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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


#line 92 "parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 203 "parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  75
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   714

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  195

#define YYUNDEFTOK  2
#define YYMAXUTOK   303


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   149,   149,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   163,   164,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   186,   187,   188,   189,   190,   191,   192,   193,   196,
     199,   200,   201,   202,   203,   206,   207,   208,   209,   212,
     213,   214,   215,   218,   219,   220,   223,   224,   227,   231,
     234,   235,   238,   239,   242,   243,   246,   249,   250,   253,
     256,   257,   260,   264,   268,   272,   276,   280,   283,   283,
     284,   287,   288,   289,   290,   291,   292,   295,   295,   296,
     299,   299,   300,   303,   306,   309,   310,   313,   316,   319,
     319,   322,   325,   328,   331,   331,   334,   335,   338,   340
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "FOR", "FUNCTION",
  "RETURN", "BREAK", "CONTINUE", "AND", "OR", "NOT", "LOCAL_TOKEN", "TRUE",
  "FALSE", "NIL", "OPERATOR_ASSIGN", "OPERATOR_PLUS", "OPERATOR_MINUS",
  "OPERATOR_MUL", "OPERATOR_DIV", "OPERATOR_MOD", "OPERATOR_EQUALS",
  "OPERATOR_NOT_EQUALS", "OPERATOR_INCREMENT", "OPERATOR_DECREMENT",
  "OPERATOR_GREATER", "OPERATOR_GREATER_EVEN", "OPERATOR_LESS",
  "OPERATOR_LESS_EVEN", "CONST_INT", "REAL_NUMBER", "ID", "COLON",
  "SEMICOLON", "BRACKET_OPEN", "BRACKET_CLOSE", "CURLY_BRACKET_OPEN",
  "CURLY_BRACKET_CLOSE", "OPENING_PARENTHESIS", "CLOSING_PARENTHESIS",
  "SCOPE", "RANGE", "DOT", "STR", "COMMA", "UMINUS", "$accept", "program",
  "stmt", "stmt_list", "expr", "term", "assignexpr", "primary", "lvalue",
  "member", "call", "callsuffix", "normcall", "methodcall", "elist",
  "elistexpr_list", "objectdef", "indexed", "indexedelem_list",
  "indexedelem", "funcname", "funcprefix", "funcargs", "funcblockstart",
  "funcblockend", "funcbody", "funcdef", "block", "$@1", "const", "idlist",
  "@2", "moreID", "@3", "ifprefix", "elseprefix", "ifstmt", "whilestart",
  "whilecond", "whilestmt", "$@4", "N", "M", "forprefix", "forstmt", "$@5",
  "returnstmt", "breakstmt", "continuestmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF (-180)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-62)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     177,  -180,   -35,  -180,   -29,   -15,   245,   -10,    -3,   384,
      16,  -180,  -180,  -180,   384,    -7,    -7,  -180,  -180,  -180,
    -180,   211,    17,   282,    29,  -180,    64,  -180,   133,   545,
    -180,  -180,  -180,    73,  -180,    61,  -180,    26,  -180,  -180,
    -180,   177,  -180,    27,  -180,  -180,  -180,  -180,  -180,  -180,
     384,   316,  -180,  -180,  -180,   566,  -180,  -180,  -180,  -180,
    -180,    58,    25,    61,    25,   384,   412,    46,    48,    40,
    -180,   177,   427,    50,  -180,  -180,  -180,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
    -180,   384,  -180,  -180,   384,   350,    56,    59,  -180,  -180,
    -180,   384,   350,    63,    70,  -180,   101,   384,  -180,   350,
     442,    71,  -180,    66,   608,   384,  -180,  -180,  -180,    72,
    -180,    15,  -180,    75,   657,   644,   -12,   -12,  -180,  -180,
    -180,   670,   670,   683,   683,   683,   683,   629,   503,    77,
      79,  -180,   524,    80,  -180,  -180,    82,    74,  -180,  -180,
     177,   466,   177,    84,  -180,  -180,    75,   384,   412,    40,
    -180,   350,  -180,  -180,   350,  -180,  -180,    81,  -180,  -180,
    -180,  -180,  -180,  -180,   384,   481,  -180,  -180,    85,    87,
      96,  -180,  -180,  -180,   587,  -180,  -180,  -180,  -180,   177,
    -180,    81,  -180,  -180,  -180
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    30,     0,    97,     0,    71,     0,     0,     0,     0,
       0,    85,    86,    84,     0,     0,     0,    81,    82,    45,
      12,     0,    78,     0,     0,    83,     0,    13,     0,     0,
      29,    15,    32,    40,    48,    41,    42,     0,    11,    10,
      44,     0,     4,     0,     5,   101,     6,     7,     8,     9,
       0,     0,    70,    72,   107,     0,   108,   109,    34,    46,
      33,     0,    35,     0,    37,     0,    63,     0,     0,    68,
      80,     0,     0,     0,    47,     1,    14,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       3,     0,    36,    38,     0,     0,     0,     0,    54,    56,
      57,     0,     0,     0,    89,    74,    95,     0,    99,     0,
       0,     0,   106,     0,     0,     0,    60,    64,    65,     0,
      66,     0,    31,    43,    27,    28,    16,    17,    18,    19,
      20,    25,    26,    24,    23,    21,    22,    39,     0,     0,
       0,    49,     0,     0,    51,    87,     0,     0,    77,    94,
       0,     0,     0,     0,    93,   102,     0,     0,    63,    68,
      79,     0,    50,    58,     0,    52,    53,    92,    73,    75,
      96,    98,   100,   104,     0,     0,    62,    67,     0,     0,
       0,    88,    76,   101,     0,    69,    55,    59,    90,     0,
     103,    92,   101,    91,   105
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -180,  -180,   -27,    60,    -6,  -180,  -180,  -180,    22,  -180,
      24,  -180,  -180,  -180,   -49,   -37,  -180,  -180,   -24,    13,
    -180,  -180,  -180,  -180,  -180,  -180,   -18,    -2,  -180,  -180,
    -180,  -180,   -54,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -179,  -180,  -180,  -180,  -180,  -180,  -180,  -180
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    98,    99,   100,    67,   116,    36,    68,   120,    69,
      53,    37,   105,   147,   182,   148,    38,    39,    71,    40,
     146,   167,   181,   191,    41,   150,    42,    43,   108,    44,
     152,   109,   174,    45,    46,   183,    47,    48,    49
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      55,    76,   111,    58,   189,    73,    50,    10,    60,    81,
      82,    83,    51,   194,   106,    66,     1,    72,     2,    52,
       3,     4,     5,     6,     7,     8,    56,    19,     9,    10,
      11,    12,    13,    57,    61,    14,    24,    62,    64,    63,
      63,    15,    16,   113,   110,    66,   139,    17,    18,    19,
      59,    20,    21,   143,    22,   160,    23,    70,    24,   114,
     153,    25,    94,    74,    75,     5,    95,   104,   107,    96,
      97,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   117,   137,   118,   119,   138,    66,
     140,    91,   123,   141,    76,   142,    66,   144,   101,    92,
      93,   151,   102,    66,   145,   149,   103,   155,   156,   158,
      94,    65,   178,    22,    95,   179,   161,    96,    97,   163,
     164,   176,   166,   170,   168,   172,   173,   186,   180,   187,
     188,   121,   159,    -2,     1,   177,     2,   193,     3,     4,
       5,     6,     7,     8,     0,   169,     9,    10,    11,    12,
      13,   175,     0,    14,     0,    66,     0,     0,    66,    15,
      16,     0,   192,     0,     0,    17,    18,    19,   184,    20,
      21,     0,    22,     0,    23,     0,    24,     0,     1,    25,
       2,     0,     3,     4,     5,     6,     7,     8,     0,     0,
       9,    10,    11,    12,    13,     0,     0,    14,     0,     0,
       0,     0,     0,    15,    16,     0,     0,     0,     0,    17,
      18,    19,     1,    20,    21,     0,    22,     0,    23,     0,
      24,     0,     0,    25,     9,    10,    11,    12,    13,     0,
       0,    14,     0,     0,     0,     0,     0,    15,    16,     0,
       0,     0,     0,    17,    18,    19,     1,     0,    21,   -61,
      65,     0,    23,     0,    24,     0,     0,    25,     9,    10,
      11,    12,    13,     0,     0,    14,     0,     0,     0,     0,
       0,    15,    16,     0,     0,     0,     0,    17,    18,    19,
       0,    54,    21,     1,     0,     0,    23,     0,    24,     5,
       0,    25,     0,     0,     0,     9,    10,    11,    12,    13,
       0,     0,    14,     0,     0,     0,     0,     0,    15,    16,
       0,     0,     0,     0,    17,    18,    19,     1,     0,    21,
       0,     0,     0,    23,     0,    24,     0,     0,    25,     9,
      10,    11,    12,    13,     0,     0,    14,     0,     0,     0,
       0,     0,    15,    16,     0,     0,     0,     0,    17,    18,
      19,     1,   -61,    21,     0,     0,     0,    23,     0,    24,
       0,     0,    25,     9,    10,    11,    12,    13,     0,     0,
      14,     0,     0,     0,     0,     0,    15,    16,     0,     0,
       0,     0,    17,    18,    19,     1,     0,    21,     0,     0,
       0,    23,   -61,    24,     0,     0,    25,     9,    10,    11,
      12,    13,     0,     0,    14,     0,     0,     0,     0,     0,
      15,    16,     0,     0,     0,     0,    17,    18,    19,     0,
       0,    21,     0,    77,    78,    23,     0,    24,     0,     0,
      25,    79,    80,    81,    82,    83,    84,    85,    77,    78,
      86,    87,    88,    89,     0,     0,    79,    80,    81,    82,
      83,    84,    85,    77,    78,    86,    87,    88,    89,   115,
       0,    79,    80,    81,    82,    83,    84,    85,     0,   122,
      86,    87,    88,    89,     0,     0,     0,    77,    78,     0,
       0,     0,     0,     0,   154,    79,    80,    81,    82,    83,
      84,    85,    77,    78,    86,    87,    88,    89,     0,     0,
      79,    80,    81,    82,    83,    84,    85,     0,   171,    86,
      87,    88,    89,     0,    77,    78,     0,     0,     0,     0,
       0,   185,    79,    80,    81,    82,    83,    84,    85,     0,
       0,    86,    87,    88,    89,    77,    78,     0,     0,     0,
       0,   162,     0,    79,    80,    81,    82,    83,    84,    85,
       0,     0,    86,    87,    88,    89,    77,    78,     0,     0,
       0,     0,   165,     0,    79,    80,    81,    82,    83,    84,
      85,     0,     0,    86,    87,    88,    89,    77,    78,     0,
       0,    90,     0,     0,     0,    79,    80,    81,    82,    83,
      84,    85,     0,     0,    86,    87,    88,    89,    77,    78,
       0,     0,   112,     0,     0,     0,    79,    80,    81,    82,
      83,    84,    85,     0,     0,    86,    87,    88,    89,    77,
      78,     0,     0,   190,     0,     0,     0,    79,    80,    81,
      82,    83,    84,    85,     0,     0,    86,    87,    88,    89,
      77,    78,     0,   157,     0,     0,     0,     0,    79,    80,
      81,    82,    83,    84,    85,    77,     0,    86,    87,    88,
      89,     0,     0,    79,    80,    81,    82,    83,    84,    85,
       0,     0,    86,    87,    88,    89,    79,    80,    81,    82,
      83,    84,    85,     0,     0,    86,    87,    88,    89,    79,
      80,    81,    82,    83,   -62,   -62,     0,     0,    86,    87,
      88,    89,    79,    80,    81,    82,    83,     0,     0,     0,
       0,   -62,   -62,   -62,   -62
};

static const yytype_int16 yycheck[] =
{
       6,    28,    51,     9,   183,    23,    41,    14,    14,    21,
      22,    23,    41,   192,    41,    21,     1,    23,     3,    34,
       5,     6,     7,     8,     9,    10,    36,    34,    13,    14,
      15,    16,    17,    36,    41,    20,    43,    15,    16,    15,
      16,    26,    27,    61,    50,    51,    95,    32,    33,    34,
      34,    36,    37,   102,    39,    40,    41,    40,    43,    65,
     109,    46,    37,    34,     0,     7,    41,    41,    41,    44,
      45,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    38,    91,    38,    47,    94,    95,
      34,    18,    42,    34,   121,   101,   102,    34,    37,    26,
      27,   107,    41,   109,    34,     4,    45,    36,    42,   115,
      37,    39,   161,    39,    41,   164,    41,    44,    45,    42,
      41,   158,    42,   150,    42,   152,    42,    42,    47,    42,
      34,    71,   119,     0,     1,   159,     3,   191,     5,     6,
       7,     8,     9,    10,    -1,   147,    13,    14,    15,    16,
      17,   157,    -1,    20,    -1,   161,    -1,    -1,   164,    26,
      27,    -1,   189,    -1,    -1,    32,    33,    34,   174,    36,
      37,    -1,    39,    -1,    41,    -1,    43,    -1,     1,    46,
       3,    -1,     5,     6,     7,     8,     9,    10,    -1,    -1,
      13,    14,    15,    16,    17,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    32,
      33,    34,     1,    36,    37,    -1,    39,    -1,    41,    -1,
      43,    -1,    -1,    46,    13,    14,    15,    16,    17,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    27,    -1,
      -1,    -1,    -1,    32,    33,    34,     1,    -1,    37,    38,
      39,    -1,    41,    -1,    43,    -1,    -1,    46,    13,    14,
      15,    16,    17,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    26,    27,    -1,    -1,    -1,    -1,    32,    33,    34,
      -1,    36,    37,     1,    -1,    -1,    41,    -1,    43,     7,
      -1,    46,    -1,    -1,    -1,    13,    14,    15,    16,    17,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    27,
      -1,    -1,    -1,    -1,    32,    33,    34,     1,    -1,    37,
      -1,    -1,    -1,    41,    -1,    43,    -1,    -1,    46,    13,
      14,    15,    16,    17,    -1,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    32,    33,
      34,     1,    36,    37,    -1,    -1,    -1,    41,    -1,    43,
      -1,    -1,    46,    13,    14,    15,    16,    17,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    26,    27,    -1,    -1,
      -1,    -1,    32,    33,    34,     1,    -1,    37,    -1,    -1,
      -1,    41,    42,    43,    -1,    -1,    46,    13,    14,    15,
      16,    17,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      26,    27,    -1,    -1,    -1,    -1,    32,    33,    34,    -1,
      -1,    37,    -1,    11,    12,    41,    -1,    43,    -1,    -1,
      46,    19,    20,    21,    22,    23,    24,    25,    11,    12,
      28,    29,    30,    31,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    11,    12,    28,    29,    30,    31,    47,
      -1,    19,    20,    21,    22,    23,    24,    25,    -1,    42,
      28,    29,    30,    31,    -1,    -1,    -1,    11,    12,    -1,
      -1,    -1,    -1,    -1,    42,    19,    20,    21,    22,    23,
      24,    25,    11,    12,    28,    29,    30,    31,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    -1,    42,    28,
      29,    30,    31,    -1,    11,    12,    -1,    -1,    -1,    -1,
      -1,    40,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    11,    12,    -1,    -1,    -1,
      -1,    38,    -1,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    11,    12,    -1,    -1,
      -1,    -1,    38,    -1,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    11,    12,    -1,
      -1,    36,    -1,    -1,    -1,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    11,    12,
      -1,    -1,    36,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    11,
      12,    -1,    -1,    36,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      11,    12,    -1,    35,    -1,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    11,    -1,    28,    29,    30,
      31,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    19,    20,    21,    22,    23,    -1,    -1,    -1,
      -1,    28,    29,    30,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     5,     6,     7,     8,     9,    10,    13,
      14,    15,    16,    17,    20,    26,    27,    32,    33,    34,
      36,    37,    39,    41,    43,    46,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    65,    70,    75,    76,
      78,    83,    85,    86,    88,    92,    93,    95,    96,    97,
      41,    41,    34,    69,    36,    53,    36,    36,    53,    34,
      53,    41,    57,    59,    57,    39,    53,    63,    66,    68,
      40,    77,    53,    75,    34,     0,    51,    11,    12,    19,
      20,    21,    22,    23,    24,    25,    28,    29,    30,    31,
      36,    18,    26,    27,    37,    41,    44,    45,    60,    61,
      62,    37,    41,    45,    41,    71,    51,    41,    87,    90,
      53,    63,    36,    75,    53,    47,    64,    38,    38,    47,
      67,    52,    42,    42,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    63,
      34,    34,    53,    63,    34,    34,    79,    72,    74,     4,
      84,    53,    89,    63,    42,    36,    42,    35,    53,    68,
      40,    41,    38,    42,    41,    38,    42,    80,    42,    76,
      51,    42,    51,    42,    91,    53,    64,    67,    63,    63,
      47,    81,    73,    94,    53,    40,    42,    42,    34,    90,
      36,    82,    51,    81,    90
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    54,    54,    54,    54,    54,    54,    54,    54,    55,
      56,    56,    56,    56,    56,    57,    57,    57,    57,    58,
      58,    58,    58,    59,    59,    59,    60,    60,    61,    62,
      63,    63,    64,    64,    65,    65,    66,    67,    67,    68,
      69,    69,    70,    71,    72,    73,    74,    75,    77,    76,
      76,    78,    78,    78,    78,    78,    78,    80,    79,    79,
      82,    81,    81,    83,    84,    85,    85,    86,    87,    89,
      88,    90,    91,    92,    94,    93,    95,    95,    96,    97
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     3,     1,     2,     2,     2,     2,     2,     2,     3,
       1,     1,     1,     3,     1,     1,     2,     2,     1,     3,
       4,     3,     4,     4,     2,     6,     1,     1,     3,     5,
       2,     0,     3,     0,     3,     3,     2,     3,     0,     5,
       1,     0,     2,     3,     0,     0,     3,     3,     0,     4,
       2,     1,     1,     1,     1,     1,     1,     0,     3,     0,
       0,     4,     0,     4,     1,     2,     4,     1,     3,     0,
       4,     0,     0,     7,     0,     8,     3,     2,     2,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3:
#line 151 "parser.y"
                     {(yyval.stmts) = NULL; temp_c = 0;}
#line 1627 "parser.c"
    break;

  case 4:
#line 152 "parser.y"
               {(yyval.stmts) = (yyvsp[0].stmts); temp_c = 0;}
#line 1633 "parser.c"
    break;

  case 5:
#line 153 "parser.y"
               {(yyval.stmts) = NULL; temp_c = 0;}
#line 1639 "parser.c"
    break;

  case 6:
#line 154 "parser.y"
               {(yyval.stmts) = NULL; temp_c = 0;}
#line 1645 "parser.c"
    break;

  case 7:
#line 155 "parser.y"
               {(yyval.stmts) = NULL; temp_c = 0;}
#line 1651 "parser.c"
    break;

  case 8:
#line 156 "parser.y"
               {(yyval.stmts) = (yyvsp[0].stmts);}
#line 1657 "parser.c"
    break;

  case 9:
#line 157 "parser.y"
               {(yyval.stmts) = (yyvsp[0].stmts);}
#line 1663 "parser.c"
    break;

  case 10:
#line 158 "parser.y"
               {(yyval.stmts) = (yyvsp[0].stmts); temp_c = 0;}
#line 1669 "parser.c"
    break;

  case 11:
#line 159 "parser.y"
               {(yyval.stmts) = NULL; temp_c = 0;}
#line 1675 "parser.c"
    break;

  case 12:
#line 160 "parser.y"
               {(yyval.stmts) = NULL; temp_c = 0;}
#line 1681 "parser.c"
    break;

  case 13:
#line 163 "parser.y"
                {(yyval.stmts) = (yyvsp[0].stmts);}
#line 1687 "parser.c"
    break;

  case 14:
#line 164 "parser.y"
                  {(yyval.stmts) = do_stmtlist((yyvsp[-1].stmts), (yyvsp[0].stmts));}
#line 1693 "parser.c"
    break;

  case 15:
#line 167 "parser.y"
                                                    {(yyval.exprNode) = (yyvsp[0].exprNode);}
#line 1699 "parser.c"
    break;

  case 16:
#line 168 "parser.y"
                                                    {(yyval.exprNode) = do_op((yyvsp[-2].exprNode),(yyvsp[0].exprNode),add);}
#line 1705 "parser.c"
    break;

  case 17:
#line 169 "parser.y"
                                                    {(yyval.exprNode) = do_op((yyvsp[-2].exprNode),(yyvsp[0].exprNode),sub);}
#line 1711 "parser.c"
    break;

  case 18:
#line 170 "parser.y"
                                                    {(yyval.exprNode) = do_op((yyvsp[-2].exprNode),(yyvsp[0].exprNode),mul);}
#line 1717 "parser.c"
    break;

  case 19:
#line 171 "parser.y"
                                                    {(yyval.exprNode) = do_op((yyvsp[-2].exprNode),(yyvsp[0].exprNode),div_op);}
#line 1723 "parser.c"
    break;

  case 20:
#line 172 "parser.y"
                                                    {(yyval.exprNode) = do_op((yyvsp[-2].exprNode),(yyvsp[0].exprNode),mod);}
#line 1729 "parser.c"
    break;

  case 21:
#line 173 "parser.y"
                                                    {(yyval.exprNode) = do_relop((yyvsp[-2].exprNode),(yyvsp[0].exprNode),if_less);}
#line 1735 "parser.c"
    break;

  case 22:
#line 174 "parser.y"
                                                    {(yyval.exprNode) = do_relop((yyvsp[-2].exprNode),(yyvsp[0].exprNode),if_lesseq);}
#line 1741 "parser.c"
    break;

  case 23:
#line 175 "parser.y"
                                                    {(yyval.exprNode) = do_relop((yyvsp[-2].exprNode),(yyvsp[0].exprNode),if_greatereq);}
#line 1747 "parser.c"
    break;

  case 24:
#line 176 "parser.y"
                                                    {(yyval.exprNode) = do_relop((yyvsp[-2].exprNode),(yyvsp[0].exprNode),if_greater);}
#line 1753 "parser.c"
    break;

  case 25:
#line 177 "parser.y"
                                                    {(yyval.exprNode) = do_relop((yyvsp[-2].exprNode),(yyvsp[0].exprNode),if_eq);}
#line 1759 "parser.c"
    break;

  case 26:
#line 178 "parser.y"
                                                    {(yyval.exprNode) = do_relop((yyvsp[-2].exprNode),(yyvsp[0].exprNode),if_noteq);}
#line 1765 "parser.c"
    break;

  case 27:
#line 179 "parser.y"
                                                    {(yyval.exprNode) = do_boolop((yyvsp[-2].exprNode),(yyvsp[0].exprNode),and_op);}
#line 1771 "parser.c"
    break;

  case 28:
#line 180 "parser.y"
                                                    {(yyval.exprNode) = do_boolop((yyvsp[-2].exprNode),(yyvsp[0].exprNode),or_op);}
#line 1777 "parser.c"
    break;

  case 29:
#line 181 "parser.y"
                                                    {(yyval.exprNode) = (yyvsp[0].exprNode);}
#line 1783 "parser.c"
    break;

  case 30:
#line 182 "parser.y"
                                                    {yyclearin;}
#line 1789 "parser.c"
    break;

  case 31:
#line 186 "parser.y"
                                                    { (yyval.exprNode) = (yyvsp[-1].exprNode); }
#line 1795 "parser.c"
    break;

  case 32:
#line 187 "parser.y"
                                                    { (yyval.exprNode) = (yyvsp[0].exprNode); }
#line 1801 "parser.c"
    break;

  case 33:
#line 188 "parser.y"
                                                    {(yyval.exprNode) = do_uminus((yyvsp[0].exprNode));}
#line 1807 "parser.c"
    break;

  case 34:
#line 189 "parser.y"
                                                    {(yyval.exprNode) = do_not((yyvsp[0].exprNode));}
#line 1813 "parser.c"
    break;

  case 35:
#line 190 "parser.y"
                                                    {(yyval.exprNode) = do_pre_dec_inc((yyvsp[0].exprNode),add);}
#line 1819 "parser.c"
    break;

  case 36:
#line 191 "parser.y"
                                                    {(yyval.exprNode) = do_post_dec_inc((yyvsp[-1].exprNode),add);}
#line 1825 "parser.c"
    break;

  case 37:
#line 192 "parser.y"
                                                    {(yyval.exprNode) = do_pre_dec_inc((yyvsp[0].exprNode),sub);}
#line 1831 "parser.c"
    break;

  case 38:
#line 193 "parser.y"
                                                    {(yyval.exprNode) = do_post_dec_inc((yyvsp[-1].exprNode),sub);}
#line 1837 "parser.c"
    break;

  case 39:
#line 196 "parser.y"
                                                    {(yyval.exprNode) = do_assign((yyvsp[-2].exprNode) , (yyvsp[0].exprNode));}
#line 1843 "parser.c"
    break;

  case 40:
#line 199 "parser.y"
                                                    { (yyval.exprNode) = emit_iftableitem((yyvsp[0].exprNode)); }
#line 1849 "parser.c"
    break;

  case 41:
#line 200 "parser.y"
                                                    { (yyval.exprNode) = (yyvsp[0].exprNode); }
#line 1855 "parser.c"
    break;

  case 42:
#line 201 "parser.y"
                                                    { (yyval.exprNode) = (yyvsp[0].exprNode); }
#line 1861 "parser.c"
    break;

  case 43:
#line 202 "parser.y"
                                                    { (yyval.exprNode) = do_par_funcdef((yyvsp[-1].exprNode)); }
#line 1867 "parser.c"
    break;

  case 44:
#line 203 "parser.y"
                                                    { (yyval.exprNode) = (yyvsp[0].exprNode); }
#line 1873 "parser.c"
    break;

  case 45:
#line 206 "parser.y"
                        {(yyval.exprNode) = do_var((yyvsp[0].stringValue));}
#line 1879 "parser.c"
    break;

  case 46:
#line 207 "parser.y"
                        {(yyval.exprNode) = do_local_var((yyvsp[0].stringValue));}
#line 1885 "parser.c"
    break;

  case 47:
#line 208 "parser.y"
                        {(yyval.exprNode) = do_scope_var((yyvsp[0].stringValue));}
#line 1891 "parser.c"
    break;

  case 48:
#line 209 "parser.y"
                        {(yyval.exprNode) = (yyvsp[0].exprNode);}
#line 1897 "parser.c"
    break;

  case 49:
#line 212 "parser.y"
                                            {(yyval.exprNode) = member_item((yyvsp[-2].exprNode) , (yyvsp[0].stringValue));}
#line 1903 "parser.c"
    break;

  case 50:
#line 213 "parser.y"
                                            {(yyval.exprNode) = array_item((yyvsp[-3].exprNode) , (yyvsp[-1].exprNode));}
#line 1909 "parser.c"
    break;

  case 51:
#line 214 "parser.y"
                                            {(yyval.exprNode) = member_item((yyvsp[-2].exprNode) , (yyvsp[0].stringValue));}
#line 1915 "parser.c"
    break;

  case 52:
#line 215 "parser.y"
                                            {(yyval.exprNode) = array_item((yyvsp[-3].exprNode) , (yyvsp[-1].exprNode));}
#line 1921 "parser.c"
    break;

  case 53:
#line 218 "parser.y"
                                                          {(yyval.exprNode) = make_call((yyvsp[-3].exprNode),(yyvsp[-1].exprNode));}
#line 1927 "parser.c"
    break;

  case 54:
#line 219 "parser.y"
                    {(yyval.exprNode) = do_lvalue_call((yyvsp[-1].exprNode),(yyvsp[0].calls));}
#line 1933 "parser.c"
    break;

  case 55:
#line 220 "parser.y"
                                                                                                { (yyval.exprNode) = do_funcdef_call((yyvsp[-4].exprNode),(yyvsp[-1].exprNode)); }
#line 1939 "parser.c"
    break;

  case 56:
#line 223 "parser.y"
                     {(yyval.calls) = (yyvsp[0].calls);}
#line 1945 "parser.c"
    break;

  case 57:
#line 224 "parser.y"
                     {(yyval.calls) = (yyvsp[0].calls);}
#line 1951 "parser.c"
    break;

  case 58:
#line 227 "parser.y"
                                                         {(yyval.calls) = do_normcall((yyvsp[-1].exprNode));}
#line 1957 "parser.c"
    break;

  case 59:
#line 231 "parser.y"
                                                                    {(yyval.calls) = do_methodcall((yyvsp[-3].stringValue),(yyvsp[-1].exprNode));}
#line 1963 "parser.c"
    break;

  case 60:
#line 234 "parser.y"
                            { (yyval.exprNode) = do_elist((yyvsp[-1].exprNode),(yyvsp[0].exprNode)); }
#line 1969 "parser.c"
    break;

  case 61:
#line 235 "parser.y"
          { (yyval.exprNode) = NULL; }
#line 1975 "parser.c"
    break;

  case 62:
#line 238 "parser.y"
                                          { (yyval.exprNode) = do_elist((yyvsp[-1].exprNode),(yyvsp[0].exprNode)); }
#line 1981 "parser.c"
    break;

  case 63:
#line 239 "parser.y"
           { (yyval.exprNode) = NULL; }
#line 1987 "parser.c"
    break;

  case 64:
#line 242 "parser.y"
                                                { (yyval.exprNode) = make_table((yyvsp[-1].exprNode)); }
#line 1993 "parser.c"
    break;

  case 65:
#line 243 "parser.y"
                                                { (yyval.exprNode) = make_table_pairs((yyvsp[-1].exprNode));}
#line 1999 "parser.c"
    break;

  case 66:
#line 246 "parser.y"
                                       {(yyval.exprNode) = make_indexedelem_list((yyvsp[-1].exprNode),(yyvsp[0].exprNode));}
#line 2005 "parser.c"
    break;

  case 67:
#line 249 "parser.y"
                                                     {(yyval.exprNode) = make_indexedelem_list((yyvsp[-1].exprNode),(yyvsp[0].exprNode));}
#line 2011 "parser.c"
    break;

  case 68:
#line 250 "parser.y"
                    {(yyval.exprNode) = NULL;}
#line 2017 "parser.c"
    break;

  case 69:
#line 253 "parser.y"
                                                                    {(yyval.exprNode) = make_indexedelem((yyvsp[-3].exprNode),(yyvsp[-1].exprNode));}
#line 2023 "parser.c"
    break;

  case 70:
#line 256 "parser.y"
             {(yyval.stringValue) = (yyvsp[0].stringValue);}
#line 2029 "parser.c"
    break;

  case 71:
#line 257 "parser.y"
          {(yyval.stringValue) = new_afunction();}
#line 2035 "parser.c"
    break;

  case 72:
#line 260 "parser.y"
                              {(yyval.exprNode) = do_function((yyvsp[0].stringValue));}
#line 2041 "parser.c"
    break;

  case 73:
#line 264 "parser.y"
                                                         {enter_scopespace();}
#line 2047 "parser.c"
    break;

  case 74:
#line 268 "parser.y"
                {new_loop(loop_c); loop_c = 0;}
#line 2053 "parser.c"
    break;

  case 75:
#line 272 "parser.y"
              {void exit_loop();}
#line 2059 "parser.c"
    break;

  case 76:
#line 276 "parser.y"
                                            {(yyval.intValue) = functionLocalOffset;}
#line 2065 "parser.c"
    break;

  case 77:
#line 280 "parser.y"
                                      {exit_func((yyvsp[-2].exprNode), (yyvsp[0].intValue));}
#line 2071 "parser.c"
    break;

  case 78:
#line 283 "parser.y"
                          {curr_scope++;}
#line 2077 "parser.c"
    break;

  case 79:
#line 283 "parser.y"
                                                                        {curr_scope--; SymTable_hide(curr_scope); (yyval.stmts) = (yyvsp[-1].stmts);}
#line 2083 "parser.c"
    break;

  case 80:
#line 284 "parser.y"
                                               {(yyval.stmts) = NULL;}
#line 2089 "parser.c"
    break;

  case 81:
#line 287 "parser.y"
                       { (yyval.exprNode) = newexpr_constint((yyvsp[0].intValue));}
#line 2095 "parser.c"
    break;

  case 82:
#line 288 "parser.y"
                       { (yyval.exprNode) = newexpr_constnum((yyvsp[0].realValue));}
#line 2101 "parser.c"
    break;

  case 83:
#line 289 "parser.y"
                       { (yyval.exprNode) = newexpr_conststring((yyvsp[0].stringValue));}
#line 2107 "parser.c"
    break;

  case 84:
#line 290 "parser.y"
                       { (yyval.exprNode) = newexpr_constnil();}
#line 2113 "parser.c"
    break;

  case 85:
#line 291 "parser.y"
                       { (yyval.exprNode) = newexpr_constbool(1);}
#line 2119 "parser.c"
    break;

  case 86:
#line 292 "parser.y"
                       { (yyval.exprNode) = newexpr_constbool(0);}
#line 2125 "parser.c"
    break;

  case 87:
#line 295 "parser.y"
           { (yyval.exprNode) = do_idlist((yyvsp[0].stringValue));}
#line 2131 "parser.c"
    break;

  case 90:
#line 299 "parser.y"
                 { (yyval.exprNode) = do_moreID((yyvsp[0].stringValue)); }
#line 2137 "parser.c"
    break;

  case 93:
#line 303 "parser.y"
                                                           { (yyval.intValue) = do_ifprefix((yyvsp[-1].exprNode));}
#line 2143 "parser.c"
    break;

  case 94:
#line 306 "parser.y"
                 { (yyval.intValue) = nextquad(); emit(jump, NULL, NULL, NULL, 0, yylineno); }
#line 2149 "parser.c"
    break;

  case 95:
#line 309 "parser.y"
                      {(yyval.stmts) = (yyvsp[0].stmts);  patchlabel((yyvsp[-1].intValue), nextquad());}
#line 2155 "parser.c"
    break;

  case 96:
#line 310 "parser.y"
                                         {  patchlabel((yyvsp[-3].intValue), (yyvsp[-1].intValue) + 1); patchlabel((yyvsp[-1].intValue), nextquad()); (yyval.stmts) = do_ifelse((yyvsp[-2].stmts), (yyvsp[0].stmts));}
#line 2161 "parser.c"
    break;

  case 97:
#line 313 "parser.y"
                  { (yyval.intValue) = nextquad();}
#line 2167 "parser.c"
    break;

  case 98:
#line 316 "parser.y"
                                                       {(yyval.intValue) = do_whilecond((yyvsp[-1].exprNode));}
#line 2173 "parser.c"
    break;

  case 99:
#line 319 "parser.y"
                               {loop_c++;}
#line 2179 "parser.c"
    break;

  case 100:
#line 319 "parser.y"
                                                {loop_c--; do_whilestmt((yyvsp[-3].intValue),(yyvsp[-2].intValue),(yyvsp[0].stmts));}
#line 2185 "parser.c"
    break;

  case 101:
#line 322 "parser.y"
   {(yyval.intValue) = nextquad(); emit(jump,NULL, NULL, NULL, 0, yylineno);}
#line 2191 "parser.c"
    break;

  case 102:
#line 325 "parser.y"
   {(yyval.intValue) = nextquad();}
#line 2197 "parser.c"
    break;

  case 103:
#line 328 "parser.y"
                                                                    {(yyval.fors) = do_forprefix((yyvsp[-2].intValue),(yyvsp[-1].exprNode));}
#line 2203 "parser.c"
    break;

  case 104:
#line 331 "parser.y"
                                               {++loop_c;}
#line 2209 "parser.c"
    break;

  case 105:
#line 331 "parser.y"
                                                                    { do_forstmt((yyvsp[-7].fors),(yyvsp[-6].intValue),(yyvsp[-2].intValue),(yyvsp[-1].stmts),(yyvsp[0].intValue));}
#line 2215 "parser.c"
    break;

  case 106:
#line 334 "parser.y"
                                   { if (is_func <= 0) yyerror("Use of return out of function"); emit(ret,(yyvsp[-1].exprNode),NULL,NULL,nextquad(),yylineno); push_returnlist(nextquad()); emit(jump,NULL,NULL,NULL,0,yylineno); }
#line 2221 "parser.c"
    break;

  case 107:
#line 335 "parser.y"
                              { if (is_func <= 0) yyerror("Use of return out of function"); emit(ret,NULL,NULL,NULL,nextquad(),yylineno); push_returnlist(nextquad()); emit(jump,NULL,NULL,NULL,0,yylineno); }
#line 2227 "parser.c"
    break;

  case 108:
#line 338 "parser.y"
                           {(yyval.stmts) = do_break_continue(0);}
#line 2233 "parser.c"
    break;

  case 109:
#line 340 "parser.y"
                                 {(yyval.stmts) = do_break_continue(1);}
#line 2239 "parser.c"
    break;


#line 2243 "parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 341 "parser.y"


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
