/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "semantic.h"
#include "codegen.h"

extern int yylex();
extern int lineno;
extern FILE *yyin;
extern char *yytext;

void yyerror(const char *s);
static void set_syntax_context(const char *context);
static void clear_syntax_context(void);
static void write_summary(const char *input_file, int parse_result, int semantic_errors, int intermediate_generated, int intermediate_instructions);
static const char *friendly_token(const char *token);
static const char *syntax_message(const char *raw_message,const char *near_token);
static const char *syntax_suggestion(const char *raw_message,const char *near_token);
static void write_syntax_diagnostic(int line,const char *message,const char *near_token,const char *suggestion,int derived);

TreeNode *savedTree;

FILE *syntax_errors;
FILE *ast_file;
FILE *semantic_file;
FILE *summary_file;
FILE *code_file;

static const char *syntax_context = NULL;
static int syntax_error_count = 0;


#line 108 "parser/parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LOWER_THAN_ELSE = 3,            /* LOWER_THAN_ELSE  */
  YYSYMBOL_IF = 4,                         /* IF  */
  YYSYMBOL_ELSE = 5,                       /* ELSE  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_VOID = 7,                       /* VOID  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_RETURN = 9,                     /* RETURN  */
  YYSYMBOL_PLUS = 10,                      /* PLUS  */
  YYSYMBOL_MINUS = 11,                     /* MINUS  */
  YYSYMBOL_TIMES = 12,                     /* TIMES  */
  YYSYMBOL_OVER = 13,                      /* OVER  */
  YYSYMBOL_LT = 14,                        /* LT  */
  YYSYMBOL_LE = 15,                        /* LE  */
  YYSYMBOL_GT = 16,                        /* GT  */
  YYSYMBOL_GE = 17,                        /* GE  */
  YYSYMBOL_EQ = 18,                        /* EQ  */
  YYSYMBOL_NE = 19,                        /* NE  */
  YYSYMBOL_ASSIGN = 20,                    /* ASSIGN  */
  YYSYMBOL_SEMI = 21,                      /* SEMI  */
  YYSYMBOL_COMMA = 22,                     /* COMMA  */
  YYSYMBOL_LPAREN = 23,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 24,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 25,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 26,                  /* RBRACKET  */
  YYSYMBOL_LBRACE = 27,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 28,                    /* RBRACE  */
  YYSYMBOL_ID = 29,                        /* ID  */
  YYSYMBOL_NUM = 30,                       /* NUM  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_program = 32,                   /* program  */
  YYSYMBOL_declaration_list = 33,          /* declaration_list  */
  YYSYMBOL_type_specifier = 34,            /* type_specifier  */
  YYSYMBOL_declaration = 35,               /* declaration  */
  YYSYMBOL_var_declaration = 36,           /* var_declaration  */
  YYSYMBOL_fun_declaration = 37,           /* fun_declaration  */
  YYSYMBOL_params = 38,                    /* params  */
  YYSYMBOL_param_list = 39,                /* param_list  */
  YYSYMBOL_param = 40,                     /* param  */
  YYSYMBOL_compound_stmt = 41,             /* compound_stmt  */
  YYSYMBOL_local_declarations = 42,        /* local_declarations  */
  YYSYMBOL_statement_list = 43,            /* statement_list  */
  YYSYMBOL_statement = 44,                 /* statement  */
  YYSYMBOL_expression_stmt = 45,           /* expression_stmt  */
  YYSYMBOL_selection_stmt = 46,            /* selection_stmt  */
  YYSYMBOL_iteration_stmt = 47,            /* iteration_stmt  */
  YYSYMBOL_if_condition_context = 48,      /* if_condition_context  */
  YYSYMBOL_while_condition_context = 49,   /* while_condition_context  */
  YYSYMBOL_clear_condition_context = 50,   /* clear_condition_context  */
  YYSYMBOL_return_stmt = 51,               /* return_stmt  */
  YYSYMBOL_expression = 52,                /* expression  */
  YYSYMBOL_simple_expression = 53,         /* simple_expression  */
  YYSYMBOL_additive_expression = 54,       /* additive_expression  */
  YYSYMBOL_term = 55,                      /* term  */
  YYSYMBOL_factor = 56,                    /* factor  */
  YYSYMBOL_var = 57,                       /* var  */
  YYSYMBOL_call = 58,                      /* call  */
  YYSYMBOL_args = 59,                      /* args  */
  YYSYMBOL_arg_list = 60                   /* arg_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

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
# define YYCOPY_NEEDED 1
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   133

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    84,    84,    91,   108,   115,   120,   127,   128,   132,
     140,   152,   165,   167,   174,   186,   193,   201,   212,   222,
     241,   247,   266,   272,   274,   276,   278,   280,   282,   290,
     295,   302,   310,   319,   327,   338,   346,   357,   364,   371,
     377,   382,   391,   399,   403,   413,   423,   433,   443,   453,
     463,   470,   480,   490,   497,   507,   517,   524,   529,   531,
     533,   542,   549,   560,   571,   574,   580,   592
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "LOWER_THAN_ELSE", "IF",
  "ELSE", "INT", "VOID", "WHILE", "RETURN", "PLUS", "MINUS", "TIMES",
  "OVER", "LT", "LE", "GT", "GE", "EQ", "NE", "ASSIGN", "SEMI", "COMMA",
  "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "LBRACE", "RBRACE", "ID",
  "NUM", "$accept", "program", "declaration_list", "type_specifier",
  "declaration", "var_declaration", "fun_declaration", "params",
  "param_list", "param", "compound_stmt", "local_declarations",
  "statement_list", "statement", "expression_stmt", "selection_stmt",
  "iteration_stmt", "if_condition_context", "while_condition_context",
  "clear_condition_context", "return_stmt", "expression",
  "simple_expression", "additive_expression", "term", "factor", "var",
  "call", "args", "arg_list", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-58)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-14)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      26,   -58,   -58,     6,    26,    -9,   -58,   -58,   -58,   -58,
     -58,   -18,   -58,    42,    31,    12,    52,    81,    61,   -58,
      29,    62,    79,    26,    86,    82,   -58,   -58,   -58,   -58,
     -58,    26,    80,   -58,     0,    10,    89,    88,    90,    59,
     -58,    63,   -58,    20,   -58,   -58,   -58,   -58,   -58,   -58,
     -58,    91,   -58,    56,    46,   -58,    94,   -58,   -58,   -58,
     -58,   -58,    95,    93,    63,    63,   -58,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    21,    23,
     -58,   -58,   -58,    96,    97,    92,    46,   -58,    46,    58,
      58,    58,    58,    58,    58,   -58,   -58,   -58,    98,    99,
     100,   101,   -58,    63,   -58,   -58,   -58,   -58,   -58,   -58,
      33,    33,    33,    33,   110,   116,   -58,   -58,    33,    33,
     -58,   -58
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     5,     6,     0,     2,     0,     4,     7,     8,     1,
       3,     0,     9,     0,     0,     6,     0,     0,    12,    15,
       0,    16,     0,     0,     0,     0,    20,    11,    14,    10,
      17,    22,     0,    19,     0,     0,     0,     0,     0,     0,
      30,     0,    18,    61,    60,    24,    21,    23,    25,    26,
      27,     0,    43,    50,    53,    56,    58,    59,    28,    37,
      38,    40,     0,     0,    65,     0,    29,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      41,    57,    67,     0,    64,     0,    51,    58,    52,    44,
      45,    46,    47,    48,    49,    54,    55,    42,     0,     0,
       0,     0,    63,     0,    62,    39,    39,    39,    39,    66,
       0,     0,     0,     0,    33,    31,    36,    35,     0,     0,
      34,    32
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -58,   -58,   -58,    34,   122,   102,   -58,   -58,   -58,   104,
     106,   -58,   -58,   -34,   -58,   -58,   -58,   -58,   -58,    -6,
     -58,   -39,   -58,    25,    36,    15,   -57,   -58,   -58,   -58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,     7,     8,    17,    18,    19,
      45,    31,    34,    46,    47,    48,    49,    78,    79,   110,
      50,    51,    52,    53,    54,    55,    56,    57,    83,    84
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      62,    36,    63,    12,    37,    13,     9,    14,    38,    39,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      11,    40,    98,    41,   100,    82,    85,    26,    42,    43,
      44,    12,     1,     2,    36,    14,   -13,    37,    97,    99,
     101,    38,    39,    64,    41,    65,    41,    16,     1,    15,
      43,    44,    43,    44,    40,    24,    41,    16,    75,    76,
      26,    20,    43,    44,   109,    32,    67,    68,    67,    68,
      69,    70,    71,    72,    73,    74,   114,   115,   116,   117,
      61,    21,    41,    23,   120,   121,    41,    25,    43,    44,
      95,    96,    43,    44,    89,    90,    91,    92,    93,    94,
     111,   112,   113,    86,    88,    22,    26,    29,    30,    35,
      58,    59,    66,    60,    77,   118,    80,    81,   104,   103,
     102,   119,   105,   106,   107,   108,    10,    28,    27,     0,
       0,     0,     0,    33
};

static const yytype_int8 yycheck[] =
{
      39,     1,    41,    21,     4,    23,     0,    25,     8,     9,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      29,    21,     1,    23,     1,    64,    65,    27,    28,    29,
      30,    21,     6,     7,     1,    25,    24,     4,    77,    78,
      79,     8,     9,    23,    23,    25,    23,    13,     6,     7,
      29,    30,    29,    30,    21,    26,    23,    23,    12,    13,
      27,    30,    29,    30,   103,    31,    10,    11,    10,    11,
      14,    15,    16,    17,    18,    19,   110,   111,   112,   113,
      21,    29,    23,    22,   118,   119,    23,    25,    29,    30,
      75,    76,    29,    30,    69,    70,    71,    72,    73,    74,
     106,   107,   108,    67,    68,    24,    27,    21,    26,    29,
      21,    23,    21,    23,    20,     5,    21,    24,    26,    22,
      24,     5,    24,    24,    24,    24,     4,    23,    22,    -1,
      -1,    -1,    -1,    31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     7,    32,    33,    34,    35,    36,    37,     0,
      35,    29,    21,    23,    25,     7,    34,    38,    39,    40,
      30,    29,    24,    22,    26,    25,    27,    41,    40,    21,
      26,    42,    34,    36,    43,    29,     1,     4,     8,     9,
      21,    23,    28,    29,    30,    41,    44,    45,    46,    47,
      51,    52,    53,    54,    55,    56,    57,    58,    21,    23,
      23,    21,    52,    52,    23,    25,    21,    10,    11,    14,
      15,    16,    17,    18,    19,    12,    13,    20,    48,    49,
      21,    24,    52,    59,    60,    52,    55,    57,    55,    54,
      54,    54,    54,    54,    54,    56,    56,    52,     1,    52,
       1,    52,    24,    22,    26,    24,    24,    24,    24,    52,
      50,    50,    50,    50,    44,    44,    44,    44,     5,     5,
      44,    44
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    35,    35,    36,
      36,    37,    38,    38,    39,    39,    40,    40,    41,    42,
      42,    43,    43,    44,    44,    44,    44,    44,    44,    45,
      45,    46,    46,    46,    46,    47,    47,    48,    49,    50,
      51,    51,    52,    52,    53,    53,    53,    53,    53,    53,
      53,    54,    54,    54,    55,    55,    55,    56,    56,    56,
      56,    57,    57,    58,    59,    59,    60,    60
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     3,
       6,     6,     1,     1,     3,     1,     2,     4,     4,     2,
       0,     2,     0,     1,     1,     1,     1,     1,     2,     2,
       1,     7,     9,     7,     9,     7,     7,     0,     0,     0,
       2,     3,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     1,     1,
       1,     1,     4,     4,     1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        YY_LAC_DISCARD ("YYBACKUP");                              \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return YYENOMEM if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYPTRDIFF_T *yycapacity, YYPTRDIFF_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yy_state_t **yybottom,
                      yy_state_t *yybottom_no_free,
                      yy_state_t **yytop, yy_state_t *yytop_empty)
{
  YYPTRDIFF_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYPTRDIFF_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYPTRDIFF_T yyalloc = 2 * yysize_new;
      yy_state_t *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        YY_CAST (yy_state_t *,
                 YYSTACK_ALLOC (YY_CAST (YYSIZE_T,
                                         yyalloc * YYSIZEOF (*yybottom_new))));
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                                \
do {                                                                    \
  if (!yy_lac_established)                                              \
    {                                                                   \
      YYDPRINTF ((stderr,                                               \
                  "LAC: initial context established for %s\n",          \
                  yysymbol_name (yytoken)));                            \
      yy_lac_established = 1;                                           \
      switch (yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken))    \
        {                                                               \
        case YYENOMEM:                                                  \
          YYNOMEM;                                                      \
        case 1:                                                         \
          goto yyerrlab;                                                \
        }                                                               \
    }                                                                   \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      YYDPRINTF ((stderr, "LAC: initial context discarded due to "       \
                  Event "\n"));                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return YYENOMEM if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yy_state_t *yyesa, yy_state_t **yyes,
        YYPTRDIFF_T *yyes_capacity, yy_state_t *yyssp, yysymbol_kind_t yytoken)
{
  yy_state_t *yyes_prev = yyssp;
  yy_state_t *yyesp = yyes_prev;
  /* Reduce until we encounter a shift and thereby accept the token.  */
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yysymbol_name (yytoken)));
  if (yytoken == YYSYMBOL_YYUNDEF)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[+*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          /* Use the default action.  */
          yyrule = yydefact[+*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          /* Use the action from yytable.  */
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      /* By now we know we have to simulate a reduce.  */
      YYDPRINTF ((stderr, " R%d", yyrule - 1));
      {
        /* Pop the corresponding number of values from the stack.  */
        YYPTRDIFF_T yylen = yyr2[yyrule];
        /* First pop from the LAC stack as many tokens as possible.  */
        if (yyesp != yyes_prev)
          {
            YYPTRDIFF_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yyesp = yyes_prev;
                yylen -= yysize;
              }
          }
        /* Only afterwards look at the main stack.  */
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      /* Push the resulting state of the reduction.  */
      {
        yy_state_fast_t yystate;
        {
          const int yylhs = yyr1[yyrule] - YYNTOKENS;
          const int yyi = yypgoto[yylhs] + *yyesp;
          yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyesp
                     ? yytable[yyi]
                     : yydefgoto[yylhs]);
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            YY_IGNORE_USELESS_CAST_BEGIN
            *yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return YYENOMEM;
              }
            YY_IGNORE_USELESS_CAST_BEGIN
            *++yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}

/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yy_state_t *yyesa;
  yy_state_t **yyes;
  YYPTRDIFF_T *yyes_capacity;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;

  int yyx;
  for (yyx = 0; yyx < YYNTOKENS; ++yyx)
    {
      yysymbol_kind_t yysym = YY_CAST (yysymbol_kind_t, yyx);
      if (yysym != YYSYMBOL_YYerror && yysym != YYSYMBOL_YYUNDEF)
        switch (yy_lac (yyctx->yyesa, yyctx->yyes, yyctx->yyes_capacity, yyctx->yyssp, yysym))
          {
          case YYENOMEM:
            return YYENOMEM;
          case 1:
            continue;
          default:
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif



static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
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
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else if (yyn == 0)
        YYDPRINTF ((stderr, "No expected tokens.\n"));
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store or if
   yy_lac returned YYENOMEM.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yystrlen (yysymbol_name (yyarg[yyi]));
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

    yy_state_t yyesa[20];
    yy_state_t *yyes = yyesa;
    YYPTRDIFF_T yyes_capacity = 20 < YYMAXDEPTH ? 20 : YYMAXDEPTH;

  /* Whether LAC context is established.  A Boolean.  */
  int yy_lac_established = 0;
  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      YY_LAC_ESTABLISH;
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
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
  case 2: /* program: declaration_list  */
#line 85 "src/parser.y"
        {
            savedTree = (yyvsp[0].tree);
        }
#line 1812 "parser/parser.tab.c"
    break;

  case 3: /* declaration_list: declaration_list declaration  */
#line 92 "src/parser.y"
        {
            TreeNode *t = (yyvsp[-1].tree);

            if(t != NULL) {

                while(t->sibling != NULL)
                    t = t->sibling;

                t->sibling = (yyvsp[0].tree);

                (yyval.tree) = (yyvsp[-1].tree);
            }
            else
                (yyval.tree) = (yyvsp[0].tree);
        }
#line 1832 "parser/parser.tab.c"
    break;

  case 4: /* declaration_list: declaration  */
#line 109 "src/parser.y"
        {
            (yyval.tree) = (yyvsp[0].tree);
        }
#line 1840 "parser/parser.tab.c"
    break;

  case 5: /* type_specifier: INT  */
#line 116 "src/parser.y"
        {
            (yyval.string) = "int";
        }
#line 1848 "parser/parser.tab.c"
    break;

  case 6: /* type_specifier: VOID  */
#line 121 "src/parser.y"
        {
            (yyval.string) = "void";
        }
#line 1856 "parser/parser.tab.c"
    break;

  case 9: /* var_declaration: type_specifier ID SEMI  */
#line 133 "src/parser.y"
        {
            (yyval.tree) = newDeclNode(VarDeclK);

            (yyval.tree)->attr = (yyvsp[-1].string);
            (yyval.tree)->type = (yyvsp[-2].string);
        }
#line 1867 "parser/parser.tab.c"
    break;

  case 10: /* var_declaration: type_specifier ID LBRACKET NUM RBRACKET SEMI  */
#line 141 "src/parser.y"
        {
            (yyval.tree) = newDeclNode(VarDeclK);

            (yyval.tree)->attr = (yyvsp[-4].string);
            (yyval.tree)->type = (yyvsp[-5].string);
            (yyval.tree)->arraySize = (yyvsp[-2].string);
            (yyval.tree)->isArray = 1;
        }
#line 1880 "parser/parser.tab.c"
    break;

  case 11: /* fun_declaration: type_specifier ID LPAREN params RPAREN compound_stmt  */
#line 153 "src/parser.y"
        {
            (yyval.tree) = newDeclNode(FunDeclK);

            (yyval.tree)->attr = (yyvsp[-4].string);
            (yyval.tree)->type = (yyvsp[-5].string);

            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 1894 "parser/parser.tab.c"
    break;

  case 13: /* params: VOID  */
#line 168 "src/parser.y"
        {
            (yyval.tree) = NULL;
        }
#line 1902 "parser/parser.tab.c"
    break;

  case 14: /* param_list: param_list COMMA param  */
#line 175 "src/parser.y"
        {
            TreeNode *t = (yyvsp[-2].tree);

            while(t->sibling != NULL)
                t = t->sibling;

            t->sibling = (yyvsp[0].tree);

            (yyval.tree) = (yyvsp[-2].tree);
        }
#line 1917 "parser/parser.tab.c"
    break;

  case 15: /* param_list: param  */
#line 187 "src/parser.y"
        {
            (yyval.tree) = (yyvsp[0].tree);
        }
#line 1925 "parser/parser.tab.c"
    break;

  case 16: /* param: type_specifier ID  */
#line 194 "src/parser.y"
        {
            (yyval.tree) = newDeclNode(ParamK);

            (yyval.tree)->attr = (yyvsp[0].string);
            (yyval.tree)->type = (yyvsp[-1].string);
        }
#line 1936 "parser/parser.tab.c"
    break;

  case 17: /* param: type_specifier ID LBRACKET RBRACKET  */
#line 202 "src/parser.y"
        {
            (yyval.tree) = newDeclNode(ParamK);

            (yyval.tree)->attr = (yyvsp[-2].string);
            (yyval.tree)->type = (yyvsp[-3].string);
            (yyval.tree)->isArray = 1;
        }
#line 1948 "parser/parser.tab.c"
    break;

  case 18: /* compound_stmt: LBRACE local_declarations statement_list RBRACE  */
#line 213 "src/parser.y"
        {
            (yyval.tree) = newStmtNode(CompoundK);

            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[-1].tree);
        }
#line 1959 "parser/parser.tab.c"
    break;

  case 19: /* local_declarations: local_declarations var_declaration  */
#line 223 "src/parser.y"
        {
            TreeNode *t = (yyvsp[-1].tree);

            if(t == NULL)
                (yyval.tree) = (yyvsp[0].tree);

            else {

                while(t->sibling != NULL)
                    t = t->sibling;

                t->sibling = (yyvsp[0].tree);

                (yyval.tree) = (yyvsp[-1].tree);
            }
        }
#line 1980 "parser/parser.tab.c"
    break;

  case 20: /* local_declarations: %empty  */
#line 241 "src/parser.y"
        {
            (yyval.tree) = NULL;
        }
#line 1988 "parser/parser.tab.c"
    break;

  case 21: /* statement_list: statement_list statement  */
#line 248 "src/parser.y"
        {
            TreeNode *t = (yyvsp[-1].tree);

            if(t == NULL)
                (yyval.tree) = (yyvsp[0].tree);

            else {

                while(t->sibling != NULL)
                    t = t->sibling;

                t->sibling = (yyvsp[0].tree);

                (yyval.tree) = (yyvsp[-1].tree);
            }
        }
#line 2009 "parser/parser.tab.c"
    break;

  case 22: /* statement_list: %empty  */
#line 266 "src/parser.y"
        {
            (yyval.tree) = NULL;
        }
#line 2017 "parser/parser.tab.c"
    break;

  case 28: /* statement: error SEMI  */
#line 283 "src/parser.y"
        {
            yyerrok;
            (yyval.tree) = NULL;
        }
#line 2026 "parser/parser.tab.c"
    break;

  case 29: /* expression_stmt: expression SEMI  */
#line 291 "src/parser.y"
        {
            (yyval.tree) = (yyvsp[-1].tree);
        }
#line 2034 "parser/parser.tab.c"
    break;

  case 30: /* expression_stmt: SEMI  */
#line 296 "src/parser.y"
        {
            (yyval.tree) = NULL;
        }
#line 2042 "parser/parser.tab.c"
    break;

  case 31: /* selection_stmt: IF LPAREN if_condition_context expression RPAREN clear_condition_context statement  */
#line 303 "src/parser.y"
        {
            (yyval.tree) = newStmtNode(IfK);

            (yyval.tree)->child[0] = (yyvsp[-3].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 2053 "parser/parser.tab.c"
    break;

  case 32: /* selection_stmt: IF LPAREN if_condition_context expression RPAREN clear_condition_context statement ELSE statement  */
#line 311 "src/parser.y"
        {
            (yyval.tree) = newStmtNode(IfK);

            (yyval.tree)->child[0] = (yyvsp[-5].tree);
            (yyval.tree)->child[1] = (yyvsp[-2].tree);
            (yyval.tree)->child[2] = (yyvsp[0].tree);
        }
#line 2065 "parser/parser.tab.c"
    break;

  case 33: /* selection_stmt: IF LPAREN if_condition_context error RPAREN clear_condition_context statement  */
#line 320 "src/parser.y"
        {
            yyerrok;

            (yyval.tree) = newStmtNode(IfK);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 2076 "parser/parser.tab.c"
    break;

  case 34: /* selection_stmt: IF LPAREN if_condition_context error RPAREN clear_condition_context statement ELSE statement  */
#line 328 "src/parser.y"
        {
            yyerrok;

            (yyval.tree) = newStmtNode(IfK);
            (yyval.tree)->child[1] = (yyvsp[-2].tree);
            (yyval.tree)->child[2] = (yyvsp[0].tree);
        }
#line 2088 "parser/parser.tab.c"
    break;

  case 35: /* iteration_stmt: WHILE LPAREN while_condition_context expression RPAREN clear_condition_context statement  */
#line 339 "src/parser.y"
        {
            (yyval.tree) = newStmtNode(WhileK);

            (yyval.tree)->child[0] = (yyvsp[-3].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 2099 "parser/parser.tab.c"
    break;

  case 36: /* iteration_stmt: WHILE LPAREN while_condition_context error RPAREN clear_condition_context statement  */
#line 347 "src/parser.y"
        {
            yyerrok;

            (yyval.tree) = newStmtNode(WhileK);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 2110 "parser/parser.tab.c"
    break;

  case 37: /* if_condition_context: %empty  */
#line 357 "src/parser.y"
        {
            set_syntax_context("en la condicion del if");
        }
#line 2118 "parser/parser.tab.c"
    break;

  case 38: /* while_condition_context: %empty  */
#line 364 "src/parser.y"
        {
            set_syntax_context("en la condicion del while");
        }
#line 2126 "parser/parser.tab.c"
    break;

  case 39: /* clear_condition_context: %empty  */
#line 371 "src/parser.y"
        {
            clear_syntax_context();
        }
#line 2134 "parser/parser.tab.c"
    break;

  case 40: /* return_stmt: RETURN SEMI  */
#line 378 "src/parser.y"
        {
            (yyval.tree) = newStmtNode(ReturnK);
        }
#line 2142 "parser/parser.tab.c"
    break;

  case 41: /* return_stmt: RETURN expression SEMI  */
#line 383 "src/parser.y"
        {
            (yyval.tree) = newStmtNode(ReturnK);

            (yyval.tree)->child[0] = (yyvsp[-1].tree);
        }
#line 2152 "parser/parser.tab.c"
    break;

  case 42: /* expression: var ASSIGN expression  */
#line 392 "src/parser.y"
        {
            (yyval.tree) = newStmtNode(AssignK);

            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 2163 "parser/parser.tab.c"
    break;

  case 44: /* simple_expression: additive_expression LT additive_expression  */
#line 404 "src/parser.y"
        {
            (yyval.tree) = newExpNode(OpK);

            (yyval.tree)->attr = "<";

            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 2176 "parser/parser.tab.c"
    break;

  case 45: /* simple_expression: additive_expression LE additive_expression  */
#line 414 "src/parser.y"
        {
            (yyval.tree) = newExpNode(OpK);

            (yyval.tree)->attr = "<=";

            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 2189 "parser/parser.tab.c"
    break;

  case 46: /* simple_expression: additive_expression GT additive_expression  */
#line 424 "src/parser.y"
        {
            (yyval.tree) = newExpNode(OpK);

            (yyval.tree)->attr = ">";

            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 2202 "parser/parser.tab.c"
    break;

  case 47: /* simple_expression: additive_expression GE additive_expression  */
#line 434 "src/parser.y"
        {
            (yyval.tree) = newExpNode(OpK);

            (yyval.tree)->attr = ">=";

            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 2215 "parser/parser.tab.c"
    break;

  case 48: /* simple_expression: additive_expression EQ additive_expression  */
#line 444 "src/parser.y"
        {
            (yyval.tree) = newExpNode(OpK);

            (yyval.tree)->attr = "==";

            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 2228 "parser/parser.tab.c"
    break;

  case 49: /* simple_expression: additive_expression NE additive_expression  */
#line 454 "src/parser.y"
        {
            (yyval.tree) = newExpNode(OpK);

            (yyval.tree)->attr = "!=";

            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 2241 "parser/parser.tab.c"
    break;

  case 50: /* simple_expression: additive_expression  */
#line 464 "src/parser.y"
        {
            (yyval.tree) = (yyvsp[0].tree);
        }
#line 2249 "parser/parser.tab.c"
    break;

  case 51: /* additive_expression: additive_expression PLUS term  */
#line 471 "src/parser.y"
        {
            (yyval.tree) = newExpNode(OpK);

            (yyval.tree)->attr = "+";

            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 2262 "parser/parser.tab.c"
    break;

  case 52: /* additive_expression: additive_expression MINUS term  */
#line 481 "src/parser.y"
        {
            (yyval.tree) = newExpNode(OpK);

            (yyval.tree)->attr = "-";

            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 2275 "parser/parser.tab.c"
    break;

  case 53: /* additive_expression: term  */
#line 491 "src/parser.y"
        {
            (yyval.tree) = (yyvsp[0].tree);
        }
#line 2283 "parser/parser.tab.c"
    break;

  case 54: /* term: term TIMES factor  */
#line 498 "src/parser.y"
        {
            (yyval.tree) = newExpNode(OpK);

            (yyval.tree)->attr = "*";

            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 2296 "parser/parser.tab.c"
    break;

  case 55: /* term: term OVER factor  */
#line 508 "src/parser.y"
        {
            (yyval.tree) = newExpNode(OpK);

            (yyval.tree)->attr = "/";

            (yyval.tree)->child[0] = (yyvsp[-2].tree);
            (yyval.tree)->child[1] = (yyvsp[0].tree);
        }
#line 2309 "parser/parser.tab.c"
    break;

  case 56: /* term: factor  */
#line 518 "src/parser.y"
        {
            (yyval.tree) = (yyvsp[0].tree);
        }
#line 2317 "parser/parser.tab.c"
    break;

  case 57: /* factor: LPAREN expression RPAREN  */
#line 525 "src/parser.y"
        {
            (yyval.tree) = (yyvsp[-1].tree);
        }
#line 2325 "parser/parser.tab.c"
    break;

  case 60: /* factor: NUM  */
#line 534 "src/parser.y"
        {
            (yyval.tree) = newExpNode(ConstK);

            (yyval.tree)->attr = (yyvsp[0].string);
        }
#line 2335 "parser/parser.tab.c"
    break;

  case 61: /* var: ID  */
#line 543 "src/parser.y"
        {
            (yyval.tree) = newExpNode(IdK);

            (yyval.tree)->attr = (yyvsp[0].string);
        }
#line 2345 "parser/parser.tab.c"
    break;

  case 62: /* var: ID LBRACKET expression RBRACKET  */
#line 550 "src/parser.y"
        {
            (yyval.tree) = newExpNode(IdK);

            (yyval.tree)->attr = (yyvsp[-3].string);
            (yyval.tree)->child[0] = (yyvsp[-1].tree);
            (yyval.tree)->isArray = 1;
        }
#line 2357 "parser/parser.tab.c"
    break;

  case 63: /* call: ID LPAREN args RPAREN  */
#line 561 "src/parser.y"
        {
            (yyval.tree) = newExpNode(CallK);

            (yyval.tree)->attr = (yyvsp[-3].string);

            (yyval.tree)->child[0] = (yyvsp[-1].tree);
        }
#line 2369 "parser/parser.tab.c"
    break;

  case 65: /* args: %empty  */
#line 574 "src/parser.y"
        {
            (yyval.tree) = NULL;
        }
#line 2377 "parser/parser.tab.c"
    break;

  case 66: /* arg_list: arg_list COMMA expression  */
#line 581 "src/parser.y"
        {
            TreeNode *t = (yyvsp[-2].tree);

            while(t->sibling != NULL)
                t = t->sibling;

            t->sibling = (yyvsp[0].tree);

            (yyval.tree) = (yyvsp[-2].tree);
        }
#line 2392 "parser/parser.tab.c"
    break;

  case 67: /* arg_list: expression  */
#line 593 "src/parser.y"
        {
            (yyval.tree) = (yyvsp[0].tree);
        }
#line 2400 "parser/parser.tab.c"
    break;


#line 2404 "parser/parser.tab.c"

        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yyesa, &yyes, &yyes_capacity, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 598 "src/parser.y"


static void set_syntax_context(const char *context) {

    syntax_context = context;
}

static void clear_syntax_context(void) {

    syntax_context = NULL;
}

void yyerror(const char *s) {

    extern int lex_error_count;
    int line = yylloc.first_line > 0 ? yylloc.first_line : lineno;
    const char *near_token = yytext != NULL ? yytext : "";
    const char *message = syntax_message(s,near_token);
    const char *suggestion = syntax_suggestion(s,near_token);
    syntax_error_count++;

    write_syntax_diagnostic(line,message,near_token,suggestion,lex_error_count > 0);
}

static const char *friendly_token(const char *token) {

    if(token == NULL)
        return "";
    if(strcmp(token,"RPAREN") == 0)
        return "')'";
    if(strcmp(token,"LPAREN") == 0)
        return "'('";
    if(strcmp(token,"SEMI") == 0)
        return "';'";
    if(strcmp(token,"COMMA") == 0)
        return "','";
    if(strcmp(token,"LBRACKET") == 0)
        return "'['";
    if(strcmp(token,"RBRACKET") == 0)
        return "']'";
    if(strcmp(token,"LBRACE") == 0)
        return "'{'";
    if(strcmp(token,"RBRACE") == 0)
        return "'}'";
    if(strcmp(token,"ID") == 0)
        return "identificador";
    if(strcmp(token,"NUM") == 0)
        return "numero";
    if(strcmp(token,"INT") == 0)
        return "'int'";
    if(strcmp(token,"VOID") == 0)
        return "'void'";
    if(strcmp(token,"ASSIGN") == 0)
        return "'='";
    if(strcmp(token,"PLUS") == 0)
        return "'+'";
    if(strcmp(token,"end of file") == 0)
        return "fin de archivo";

    return token;
}

static const char *syntax_message(const char *raw_message,const char *near_token) {

    if(raw_message != NULL && strstr(raw_message,"unexpected end of file") != NULL)
        return "Fin de archivo inesperado.";
    if(near_token != NULL && strcmp(near_token,")") == 0 &&
       raw_message != NULL && strstr(raw_message,"expecting INT or VOID") != NULL)
        return "Lista de parametros invalida en declaracion de funcion.";
    if(near_token != NULL && strcmp(near_token,"=") == 0)
        return "Declaracion invalida: Kenneth C- no permite inicializar variables en la declaracion.";
    if(near_token != NULL && strcmp(near_token,"+") == 0)
        return "Expresion incompleta o operador '+' fuera de lugar.";
    if(near_token != NULL && strcmp(near_token,"}") == 0)
        return "Bloque cerrado antes de completar la sentencia anterior.";
    if(raw_message != NULL && strstr(raw_message,"expecting SEMI or LBRACKET") != NULL)
        return "Declaracion de variable incompleta.";
    if(raw_message != NULL && strstr(raw_message,"unexpected ID") != NULL)
        return "Token inesperado en esta posicion.";

    return "Token inesperado durante el analisis sintactico.";
}

static const char *syntax_suggestion(const char *raw_message,const char *near_token) {

    if(raw_message != NULL && strstr(raw_message,"unexpected end of file") != NULL)
        return "Revise si falta cerrar '}', ')' o completar una sentencia antes del fin de archivo.";
    if(near_token != NULL && strcmp(near_token,")") == 0 &&
       raw_message != NULL && strstr(raw_message,"expecting INT or VOID") != NULL)
        return "Use 'void' para funciones sin parametros, por ejemplo void main(void).";
    if(near_token != NULL && strcmp(near_token,"=") == 0)
        return "Declare primero la variable y asigne despues: int i; i = 0;";
    if(near_token != NULL && strcmp(near_token,"+") == 0)
        return "Complete ambos operandos del operador o elimine el '+'. Kenneth C- tampoco incluye i++.";
    if(near_token != NULL && strcmp(near_token,"}") == 0)
        return "Revise si falta una sentencia despues de if/while o si falta ';'.";
    if(raw_message != NULL && strstr(raw_message,"expecting SEMI or LBRACKET") != NULL)
        return "Termine la declaracion con ';' o declare un arreglo con '[NUM]'.";

    return "Compare la linea con la gramatica de Kenneth C- y revise el token indicado.";
}

static void write_syntax_diagnostic(int line,const char *message,const char *near_token,const char *suggestion,int derived) {

    fprintf(syntax_errors,"[Sintactico][Linea %-4d] %s\n",line,message);
    if(syntax_context != NULL)
        fprintf(syntax_errors,"Contexto: %s\n",syntax_context);
    if(near_token != NULL && strlen(near_token) > 0)
        fprintf(syntax_errors,"Cerca de: '%s'\n",near_token);
    if(suggestion != NULL && strlen(suggestion) > 0)
        fprintf(syntax_errors,"Sugerencia: %s\n",suggestion);
    if(derived)
        fprintf(syntax_errors,"Nota: este error puede ser derivado de errores lexicos previos.\n");
    fprintf(syntax_errors,"\n");
}

static void write_summary(const char *input_file, int parse_result, int semantic_errors, int intermediate_generated, int intermediate_instructions) {

    extern int lex_error_count;
    extern int token_count;
    const char *first_error_stage = "ninguna";

    fprintf(summary_file,"=== RESUMEN DE COMPILACION ===\n");
    fprintf(summary_file,"Entrada: %s\n\n",input_file != NULL ? input_file : "stdin");

    if(lex_error_count > 0)
        first_error_stage = "Lexico";
    else if(syntax_error_count > 0 || parse_result != 0)
        first_error_stage = "Sintactico";
    else if(semantic_errors > 0)
        first_error_stage = "Semantico";

    fprintf(summary_file,"Etapa        Estado        Detalle\n");
    fprintf(summary_file,"-----------------------------------------------\n");
    fprintf(summary_file,"Lexico       %-12s %d error(es), %d token(s)\n",
            lex_error_count == 0 ? "correcto" : "con errores",
            lex_error_count,
            token_count);
    fprintf(summary_file,"Sintactico   %-12s %d error(es)\n",
            syntax_error_count == 0 && parse_result == 0 ? "correcto" : "con errores",
            syntax_error_count);
    if(lex_error_count > 0 && syntax_error_count > 0)
        fprintf(summary_file,"              %-12s errores sintacticos posiblemente derivados del lexico\n","");

    if(lex_error_count > 0 || syntax_error_count > 0 || parse_result != 0 || savedTree == NULL) {
        fprintf(summary_file,"AST          %-12s revise output/LexErr.txt y output/SintaxErr.txt\n","no generado");
        fprintf(summary_file,"Semantico    %-12s requiere AST valido\n","omitido");
        fprintf(summary_file,"Intermedio   %-12s requiere AST valido\n","omitido");
    }
    else {
        fprintf(summary_file,"AST          %-12s output/Arbol.txt\n","generado");
        fprintf(summary_file,"Semantico    %-12s %d error(es)\n",
                semantic_errors == 0 ? "correcto" : "con errores",
                semantic_errors);
        fprintf(summary_file,"Intermedio   %-12s %s\n",
                intermediate_generated ? "generado" : "omitido",
                intermediate_generated ? "output/CodigoIntermedio.txt" : "requiere semantica correcta");
        if(intermediate_generated)
            fprintf(summary_file,"              %-12s %d instruccion(es)\n","",intermediate_instructions);
    }

    fprintf(summary_file,"\nPrimer error real: %s\n",first_error_stage);
    if(lex_error_count > 0)
        fprintf(summary_file,"Gestion: AST, semantico e intermedio omitidos por errores lexicos.\n");
    else if(syntax_error_count > 0 || parse_result != 0)
        fprintf(summary_file,"Gestion: AST, semantico e intermedio omitidos por errores sintacticos.\n");
    else if(semantic_errors > 0)
        fprintf(summary_file,"Gestion: codigo intermedio omitido por errores semanticos.\n");
    else
        fprintf(summary_file,"Gestion: todas las etapas completadas.\n");

    fprintf(summary_file,"\nArchivos generados:\n");
    fprintf(summary_file,"- Tokens:     output/tokens.txt\n");
    fprintf(summary_file,"- Lexico:     output/LexErr.txt\n");
    fprintf(summary_file,"- Sintactico: output/SintaxErr.txt\n");
    fprintf(summary_file,"- AST:        output/Arbol.txt\n");
    fprintf(summary_file,"- Semantico:  output/Semantic.txt\n");
    fprintf(summary_file,"- Intermedio: output/CodigoIntermedio.txt\n");
}

int main(int argc,char *argv[]) {

    extern FILE *tokens_file;
    extern FILE *lex_errors;
    extern int lex_error_count;
    extern void finishTokenOutput(void);
    int parse_result;
    int semantic_errors = 0;
    int intermediate_generated = 0;
    int intermediate_instructions = 0;
    const char *input_file = argc > 1 ? argv[1] : NULL;

    tokens_file = fopen("output/tokens.txt","w");
    lex_errors = fopen("output/LexErr.txt","w");

    syntax_errors = fopen("output/SintaxErr.txt","w");

    ast_file = fopen("output/Arbol.txt","w");
    semantic_file = fopen("output/Semantic.txt","w");
    summary_file = fopen("output/Resumen.txt","w");
    code_file = fopen("output/CodigoIntermedio.txt","w");

    fprintf(tokens_file,"=== TOKENS POR LINEA ===\n\n");
    fprintf(lex_errors,"=== ANALISIS LEXICO ===\n\n");
    fprintf(syntax_errors,"=== ANALISIS SINTACTICO ===\n\n");

    if(argc > 1) {

        yyin = fopen(argv[1],"r");

        if(!yyin) {

            printf("No se pudo abrir archivo\n");

            return 1;
        }
    }

    parse_result = yyparse();

    finishTokenOutput();

    if(lex_error_count == 0)
        fprintf(lex_errors,"No se encontraron errores lexicos.\n");

    fprintf(lex_errors,"\nTotal de errores lexicos: %d\n",lex_error_count);

    if(syntax_error_count == 0)
        fprintf(syntax_errors,"No se encontraron errores sintacticos.\n");

    fprintf(syntax_errors,"\nTotal de errores sintacticos: %d\n",syntax_error_count);

    fprintf(ast_file,"=== ARBOL SINTACTICO ABSTRACTO ===\n\n");

    if(lex_error_count > 0 || syntax_error_count > 0 || parse_result != 0 || savedTree == NULL) {
        fprintf(ast_file,"Estado: no generado\n\n");
        fprintf(ast_file,"No se genero el AST porque existen errores lexicos o sintacticos.\n");

        fprintf(semantic_file,"=== ANALISIS SEMANTICO ===\n\n");
        fprintf(semantic_file,"Estado: omitido\n\n");
        fprintf(semantic_file,"No se ejecuto el analisis semantico porque no existe un AST valido.\n");
        fprintf(semantic_file,"Revise output/LexErr.txt y output/SintaxErr.txt.\n");

        fprintf(code_file,"=== CODIGO INTERMEDIO ===\n\n");
        fprintf(code_file,"Estado: omitido\n\n");
        fprintf(code_file,"Codigo intermedio omitido por errores previos.\n");
    }
    else {
        fprintf(ast_file,"Estado: generado\n\n");
        printTree(savedTree,0,ast_file);
        semantic_errors = semanticAnalyze(savedTree,semantic_file);

        if(semantic_errors == 0) {
            intermediate_instructions = generateIntermediateCode(savedTree,code_file);
            intermediate_generated = 1;
        }
        else {
            fprintf(code_file,"=== CODIGO INTERMEDIO ===\n\n");
            fprintf(code_file,"Estado: omitido\n\n");
            fprintf(code_file,"Codigo intermedio omitido por errores previos.\n");
            fprintf(code_file,"Revise output/Semantic.txt.\n");
        }
    }

    write_summary(input_file, parse_result, semantic_errors, intermediate_generated, intermediate_instructions);

    fclose(tokens_file);
    fclose(lex_errors);
    fclose(syntax_errors);
    fclose(ast_file);
    fclose(semantic_file);
    fclose(summary_file);
    fclose(code_file);

    return 0;
}
