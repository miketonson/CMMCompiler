/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "syntax.y"

#include <stdio.h>
#include "tree.h"
#include "lex.yy.c"


/* Line 268 of yacc.c  */
#line 78 "syntax.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     FLOAT = 259,
     ID = 260,
     RELOP = 261,
     TYPE = 262,
     SEMI = 263,
     COMMA = 264,
     ASSIGNOP = 265,
     PLUS = 266,
     MINUS = 267,
     STAR = 268,
     DIV = 269,
     AND = 270,
     OR = 271,
     DOT = 272,
     NOT = 273,
     LP = 274,
     RP = 275,
     LB = 276,
     RB = 277,
     LC = 278,
     RC = 279,
     STRUCT = 280,
     RETURN = 281,
     IF = 282,
     ELSE = 283,
     WHILE = 284,
     LOWER_THEN_ELSE = 285,
     LOWER_THEN_ERROR = 286
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 7 "syntax.y"

	int type_int;
	float type_float;
	char  *type_id;
	int type_type;
	struct expnode *type_node;



/* Line 293 of yacc.c  */
#line 155 "syntax.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 180 "syntax.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   303

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNRULES -- Number of states.  */
#define YYNSTATES  126

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    13,    16,    20,    24,
      27,    29,    33,    35,    37,    43,    46,    48,    49,    51,
      53,    58,    63,    67,    70,    74,    76,    79,    84,    87,
      90,    91,    94,    96,   100,   106,   114,   120,   123,   126,
     127,   131,   134,   136,   140,   142,   146,   150,   154,   158,
     162,   166,   170,   174,   178,   182,   185,   188,   193,   197,
     202,   206,   208,   210,   212,   216,   221,   225
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      33,     0,    -1,    34,    -1,    35,    34,    -1,    -1,    37,
      36,     8,    -1,    37,     8,    -1,    37,    42,    45,    -1,
      37,    42,     8,    -1,     1,     8,    -1,    41,    -1,    41,
       9,    36,    -1,     7,    -1,    38,    -1,    25,    39,    23,
      48,    24,    -1,    25,    40,    -1,     5,    -1,    -1,     5,
      -1,     5,    -1,    41,    21,     3,    22,    -1,     5,    19,
      43,    20,    -1,     5,    19,    20,    -1,     1,    20,    -1,
      44,     9,    43,    -1,    44,    -1,    37,    41,    -1,    23,
      48,    46,    24,    -1,     1,    24,    -1,    47,    46,    -1,
      -1,    52,     8,    -1,    45,    -1,    26,    52,     8,    -1,
      27,    19,    52,    20,    47,    -1,    27,    19,    52,    20,
      47,    28,    47,    -1,    29,    19,    52,    20,    47,    -1,
       1,     8,    -1,    49,    48,    -1,    -1,    37,    50,     8,
      -1,     1,     8,    -1,    51,    -1,    51,     9,    50,    -1,
      41,    -1,    41,    10,    52,    -1,    52,    10,    52,    -1,
      52,    15,    52,    -1,    52,    16,    52,    -1,    52,     6,
      52,    -1,    52,    11,    52,    -1,    52,    12,    52,    -1,
      52,    13,    52,    -1,    52,    14,    52,    -1,    19,    52,
      20,    -1,    12,    52,    -1,    18,    52,    -1,     5,    19,
      53,    20,    -1,     5,    19,    20,    -1,    52,    21,    52,
      22,    -1,    52,    17,     5,    -1,     5,    -1,     3,    -1,
       4,    -1,    19,     1,    20,    -1,    52,    21,     1,    22,
      -1,    52,     9,    53,    -1,    52,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    54,    54,    58,    59,    61,    62,    63,    64,    65,
      67,    68,    70,    73,    75,    76,    78,    81,    83,    87,
      90,    94,    97,   100,   102,   103,   105,   107,   108,   110,
     111,   113,   114,   115,   116,   117,   118,   119,   121,   122,
     124,   125,   127,   128,   130,   131,   133,   134,   135,   136,
     139,   140,   141,   142,   143,   144,   145,   146,   149,   152,
     153,   156,   159,   162,   165,   166,   168,   169
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "RELOP", "TYPE",
  "SEMI", "COMMA", "ASSIGNOP", "PLUS", "MINUS", "STAR", "DIV", "AND", "OR",
  "DOT", "NOT", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN",
  "IF", "ELSE", "WHILE", "LOWER_THEN_ELSE", "LOWER_THEN_ERROR", "$accept",
  "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    35,
      36,    36,    37,    37,    38,    38,    39,    39,    40,    41,
      41,    42,    42,    42,    43,    43,    44,    45,    45,    46,
      46,    47,    47,    47,    47,    47,    47,    47,    48,    48,
      49,    49,    50,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    53,    53
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     2,
       1,     3,     1,     1,     5,     2,     1,     0,     1,     1,
       4,     4,     3,     2,     3,     1,     2,     4,     2,     2,
       0,     2,     1,     3,     5,     7,     5,     2,     2,     0,
       3,     2,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     4,     3,     4,
       3,     1,     1,     1,     3,     4,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    12,    17,     0,     2,     0,     0,    13,     9,
      18,     0,    15,     1,     3,     0,    19,     6,     0,    10,
       0,     0,    23,     0,     5,     0,     0,     0,     8,     0,
       7,     0,     0,     0,     0,    22,     0,     0,    25,    19,
      11,     0,    28,     0,    41,    44,     0,    42,    14,    38,
      26,    21,     0,    20,     0,    62,    63,    61,     0,     0,
       0,     0,     0,     0,    32,     0,     0,     0,     0,    40,
       0,    24,    37,     0,    55,    56,     0,     0,     0,     0,
       0,    27,    29,     0,    31,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    45,    43,    58,    67,     0,    64,
      54,    33,     0,     0,    49,    46,    50,    51,    52,    53,
      47,    48,    60,     0,     0,     0,    57,     0,     0,    65,
      59,    66,    34,    36,     0,    35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    18,    32,     8,    11,    12,    19,
      20,    37,    38,    64,    65,    66,    33,    34,    46,    47,
      67,    98
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -59
static const yytype_int16 yypact[] =
{
      12,    33,   -59,     0,    20,   -59,    12,    54,   -59,   -59,
      28,    30,   -59,   -59,   -59,    44,    31,   -59,    72,    27,
      15,    51,   -59,    19,   -59,    86,    74,    70,   -59,    42,
     -59,    94,    86,    79,    42,   -59,    86,    84,    97,   -59,
     -59,    83,   -59,    69,   -59,    -3,    99,   101,   -59,   -59,
      95,   -59,    -1,   -59,    32,   -59,   -59,    98,   156,   156,
     108,   156,   102,   105,   -59,   112,    69,   170,   156,   -59,
      86,   -59,   -59,   130,    65,    68,   109,   182,   198,   156,
     156,   -59,   -59,   156,   -59,   156,   156,   156,   156,   156,
     156,   156,   113,   127,   247,   -59,   -59,   211,   117,   -59,
     -59,   -59,   223,   235,   282,   247,    65,    65,    68,    68,
     271,   259,   -59,   116,   141,   156,   -59,    96,    96,   -59,
     -59,   -59,   115,   -59,    96,   -59
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -59,   -59,   134,   -59,   119,    11,   -59,   -59,   -59,   -28,
     -59,    89,   -59,   144,   100,   -34,   -20,   -59,   103,   -59,
     -58,    50
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -40
static const yytype_int8 yytable[] =
{
      74,    75,    77,    78,    45,    10,     2,    68,    50,    43,
      94,     7,    -4,     1,    49,    97,    27,     7,    26,     2,
      13,   102,   103,    28,     3,   104,     2,   105,   106,   107,
     108,   109,   110,   111,    36,   114,    25,     3,    29,    35,
      72,     9,    45,    31,     3,   -39,   -39,   -39,    26,     2,
      23,   -16,    31,    21,   -39,    15,    42,    97,     2,    16,
     -39,   -39,    17,    36,    22,   -39,   -39,     3,   -39,   -39,
      54,   -39,    55,    56,    57,   -39,     3,    41,    88,    89,
      24,    58,    92,   122,   123,    92,    93,    59,    60,    93,
     125,    39,    29,   -30,    42,    61,    62,    54,    63,    55,
      56,    57,    44,    48,    51,    53,    52,    69,    58,    76,
      70,    55,    56,    57,    59,    60,    26,    73,   112,    29,
      58,    79,    61,    62,    80,    63,    59,    60,   113,    99,
      55,    56,    57,    55,    56,    57,    81,   116,   119,    58,
      14,    71,    58,   124,    40,    59,    60,    83,    59,    60,
      96,    85,    86,    87,    88,    89,    90,    91,    92,    55,
      56,    57,    93,   120,    30,   121,    82,     0,    58,     0,
       0,     0,     0,    95,    59,    60,    83,     0,    84,     0,
      85,    86,    87,    88,    89,    90,    91,    92,    83,     0,
       0,    93,    85,    86,    87,    88,    89,    90,    91,    92,
       0,     0,   100,    93,    83,     0,   101,     0,    85,    86,
      87,    88,    89,    90,    91,    92,     0,    83,     0,    93,
     115,    85,    86,    87,    88,    89,    90,    91,    92,    83,
       0,     0,    93,    85,    86,    87,    88,    89,    90,    91,
      92,    83,     0,   117,    93,    85,    86,    87,    88,    89,
      90,    91,    92,    83,     0,   118,    93,    85,    86,    87,
      88,    89,    90,    91,    92,    83,     0,     0,    93,     0,
      86,    87,    88,    89,    90,     0,    92,    83,     0,     0,
      93,     0,    86,    87,    88,    89,     0,     0,    92,     0,
       0,     0,    93,    86,    87,    88,    89,     0,     0,    92,
       0,     0,     0,    93
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-59))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      58,    59,    60,    61,    32,     5,     7,    10,    36,    29,
      68,     0,     0,     1,    34,    73,     1,     6,    21,     7,
       0,    79,    80,     8,    25,    83,     7,    85,    86,    87,
      88,    89,    90,    91,    23,    93,     9,    25,    23,    20,
       8,     8,    70,     1,    25,     3,     4,     5,    21,     7,
      19,    23,     1,    23,    12,     1,    24,   115,     7,     5,
      18,    19,     8,    52,    20,    23,    24,    25,    26,    27,
       1,    29,     3,     4,     5,    24,    25,     3,    13,    14,
       8,    12,    17,   117,   118,    17,    21,    18,    19,    21,
     124,     5,    23,    24,    24,    26,    27,     1,    29,     3,
       4,     5,     8,    24,    20,    22,     9,     8,    12,     1,
       9,     3,     4,     5,    18,    19,    21,    19,     5,    23,
      12,    19,    26,    27,    19,    29,    18,    19,     1,    20,
       3,     4,     5,     3,     4,     5,    24,    20,    22,    12,
       6,    52,    12,    28,    25,    18,    19,     6,    18,    19,
      20,    10,    11,    12,    13,    14,    15,    16,    17,     3,
       4,     5,    21,    22,    20,   115,    66,    -1,    12,    -1,
      -1,    -1,    -1,    70,    18,    19,     6,    -1,     8,    -1,
      10,    11,    12,    13,    14,    15,    16,    17,     6,    -1,
      -1,    21,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    20,    21,     6,    -1,     8,    -1,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,     6,    -1,    21,
       9,    10,    11,    12,    13,    14,    15,    16,    17,     6,
      -1,    -1,    21,    10,    11,    12,    13,    14,    15,    16,
      17,     6,    -1,    20,    21,    10,    11,    12,    13,    14,
      15,    16,    17,     6,    -1,    20,    21,    10,    11,    12,
      13,    14,    15,    16,    17,     6,    -1,    -1,    21,    -1,
      11,    12,    13,    14,    15,    -1,    17,     6,    -1,    -1,
      21,    -1,    11,    12,    13,    14,    -1,    -1,    17,    -1,
      -1,    -1,    21,    11,    12,    13,    14,    -1,    -1,    17,
      -1,    -1,    -1,    21
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     7,    25,    33,    34,    35,    37,    38,     8,
       5,    39,    40,     0,    34,     1,     5,     8,    36,    41,
      42,    23,    20,    19,     8,     9,    21,     1,     8,    23,
      45,     1,    37,    48,    49,    20,    37,    43,    44,     5,
      36,     3,    24,    48,     8,    41,    50,    51,    24,    48,
      41,    20,     9,    22,     1,     3,     4,     5,    12,    18,
      19,    26,    27,    29,    45,    46,    47,    52,    10,     8,
       9,    43,     8,    19,    52,    52,     1,    52,    52,    19,
      19,    24,    46,     6,     8,    10,    11,    12,    13,    14,
      15,    16,    17,    21,    52,    50,    20,    52,    53,    20,
      20,     8,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,     5,     1,    52,     9,    20,    20,    20,    22,
      22,    53,    47,    47,    28,    47
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
      int yyn = yypact[*yyssp];
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
      yychar = YYLEX;
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 54 "syntax.y"
    {	(yyval.type_node) = InsertNode(Program, (yyloc).first_line, 1, 1, (yyvsp[(1) - (1)].type_node));
				RootNode = (yyval.type_node);
				}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 58 "syntax.y"
    { (yyval.type_node) = InsertNode(ExtDefList, (yyloc).first_line, 1, 2, (yyvsp[(1) - (2)].type_node), (yyvsp[(2) - (2)].type_node)); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 59 "syntax.y"
    { (yyval.type_node) = InsertNode(ExtDefList, (yyloc).first_line, 2, 0); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 61 "syntax.y"
    { (yyval.type_node) = InsertNode(ExtDef, (yyloc).first_line, 1, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 62 "syntax.y"
    { (yyval.type_node) = InsertNode(ExtDef, (yyloc).first_line, 2, 2, (yyvsp[(1) - (2)].type_node), (yyvsp[(2) - (2)].type_node)); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 63 "syntax.y"
    { (yyval.type_node) = InsertNode(ExtDef, (yyloc).first_line, 3, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 64 "syntax.y"
    { (yyval.type_node) = InsertNode(ExtDef, (yyloc).first_line, 4, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 65 "syntax.y"
    { (yyval.type_node) = InsertNode(ExtDef, yylineno, -1, 0); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 67 "syntax.y"
    { (yyval.type_node) = InsertNode(ExtDecList, (yyloc).first_line, 1, 1, (yyvsp[(1) - (1)].type_node)); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 68 "syntax.y"
    { (yyval.type_node) = InsertNode(ExtDecList, (yyloc).first_line, 2, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 70 "syntax.y"
    {	expnode *TYPEn = TypeNode(TYPEm, yylineno, (yyvsp[(1) - (1)].type_type));
	  			(yyval.type_node) = InsertNode(Specifier, (yyloc).first_line, 1, 1, TYPEn);
				}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 73 "syntax.y"
    { (yyval.type_node) = InsertNode(Specifier, (yyloc).first_line, 2, 1, (yyvsp[(1) - (1)].type_node)); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 75 "syntax.y"
    { (yyval.type_node) = InsertNode(StructSpecifier, (yyloc).first_line, 1, 5, (yyvsp[(1) - (5)].type_node), (yyvsp[(2) - (5)].type_node), (yyvsp[(3) - (5)].type_node), (yyvsp[(4) - (5)].type_node), (yyvsp[(5) - (5)].type_node)); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 76 "syntax.y"
    { (yyval.type_node) = InsertNode(StructSpecifier, (yyloc).first_line, 2, 2, (yyvsp[(1) - (2)].type_node), (yyvsp[(2) - (2)].type_node)); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 78 "syntax.y"
    {	expnode *IDn = IdNode(IDm, yylineno, (char*)(yyvsp[(1) - (1)].type_id));
       			(yyval.type_node) = InsertNode(OptTag, (yyloc).first_line, 1, 1, IDn);
			}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 81 "syntax.y"
    { (yyval.type_node) = InsertNode(OptTag, (yyloc).first_line, 2, 0); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 83 "syntax.y"
    {	expnode *IDn = IdNode(IDm, yylineno, (char*)(yyvsp[(1) - (1)].type_id));
    			(yyval.type_node) = InsertNode(Tag, (yyloc).first_line, 1, 1, IDn);
			}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 87 "syntax.y"
    {	expnode *IDn = IdNode(IDm, yylineno, (char*)(yyvsp[(1) - (1)].type_id));
       			(yyval.type_node) = InsertNode(VarDec, (yyloc).first_line, 1, 1, IDn);
			}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 90 "syntax.y"
    {	expnode *INTn = IntNode(INTm, yylineno, (yyvsp[(3) - (4)].type_int));
					(yyval.type_node) = InsertNode(VarDec, (yyloc).first_line, 2, 4, (yyvsp[(1) - (4)].type_node), (yyvsp[(2) - (4)].type_node), INTn, (yyvsp[(4) - (4)].type_node));
				}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 94 "syntax.y"
    {	expnode *IDn = IdNode(IDm, yylineno, (char*)(yyvsp[(1) - (4)].type_id));
					(yyval.type_node) = InsertNode(FunDec, (yyloc).first_line, 1, 4, IDn, (yyvsp[(2) - (4)].type_node), (yyvsp[(3) - (4)].type_node), (yyvsp[(4) - (4)].type_node));
					}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 97 "syntax.y"
    {	expnode *IDn = IdNode(IDm, yylineno, (char*)(yyvsp[(1) - (3)].type_id));
				(yyval.type_node) = InsertNode(FunDec, (yyloc).first_line, 2, 3, IDn, (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node));
				}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 100 "syntax.y"
    { (yyval.type_node) = InsertNode(FunDec, yylineno, -1, 0); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 102 "syntax.y"
    { (yyval.type_node) = InsertNode(VarList, (yyloc).first_line, 1, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 103 "syntax.y"
    { (yyval.type_node) = InsertNode(VarList, (yyloc).first_line, 2, 1, (yyvsp[(1) - (1)].type_node)); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 105 "syntax.y"
    { (yyval.type_node) = InsertNode(ParamDec, (yyloc).first_line, 1, 2, (yyvsp[(1) - (2)].type_node), (yyvsp[(2) - (2)].type_node)); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 107 "syntax.y"
    { (yyval.type_node) = InsertNode(CompSt, (yyloc).first_line, 1, 4, (yyvsp[(1) - (4)].type_node), (yyvsp[(2) - (4)].type_node), (yyvsp[(3) - (4)].type_node), (yyvsp[(4) - (4)].type_node)); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 108 "syntax.y"
    { (yyval.type_node) = InsertNode(CompSt, yylineno, -1, 0); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 110 "syntax.y"
    { (yyval.type_node) = InsertNode(StmtList, (yyloc).first_line, 1, 2, (yyvsp[(1) - (2)].type_node), (yyvsp[(2) - (2)].type_node)); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 111 "syntax.y"
    { (yyval.type_node) = InsertNode(StmtList, (yyloc).first_line, 2, 0); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 113 "syntax.y"
    { (yyval.type_node) = InsertNode(Stmt, (yyloc).first_line, 1, 2, (yyvsp[(1) - (2)].type_node), (yyvsp[(2) - (2)].type_node)); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 114 "syntax.y"
    { (yyval.type_node) = InsertNode(Stmt, (yyloc).first_line, 2, 1, (yyvsp[(1) - (1)].type_node)); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 115 "syntax.y"
    { (yyval.type_node) = InsertNode(Stmt, (yyloc).first_line, 3, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 116 "syntax.y"
    { (yyval.type_node) = InsertNode(Stmt, (yyloc).first_line, 4, 5, (yyvsp[(1) - (5)].type_node), (yyvsp[(2) - (5)].type_node), (yyvsp[(3) - (5)].type_node), (yyvsp[(4) - (5)].type_node), (yyvsp[(5) - (5)].type_node)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 117 "syntax.y"
    { (yyval.type_node) = InsertNode(Stmt, (yyloc).first_line, 5, 7, (yyvsp[(1) - (7)].type_node), (yyvsp[(2) - (7)].type_node), (yyvsp[(3) - (7)].type_node), (yyvsp[(4) - (7)].type_node), (yyvsp[(5) - (7)].type_node), (yyvsp[(6) - (7)].type_node), (yyvsp[(7) - (7)].type_node)); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 118 "syntax.y"
    { (yyval.type_node) = InsertNode(Stmt, (yyloc).first_line, 6, 5, (yyvsp[(1) - (5)].type_node), (yyvsp[(2) - (5)].type_node), (yyvsp[(3) - (5)].type_node), (yyvsp[(4) - (5)].type_node), (yyvsp[(5) - (5)].type_node)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 119 "syntax.y"
    {(yyval.type_node) = InsertNode(Stmt, yylineno, -1, 0);}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 121 "syntax.y"
    { (yyval.type_node) = InsertNode(DefList, (yyloc).first_line, 1, 2, (yyvsp[(1) - (2)].type_node), (yyvsp[(2) - (2)].type_node)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 122 "syntax.y"
    { (yyval.type_node) = InsertNode(DefList, (yyloc).first_line, 2, 0); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 124 "syntax.y"
    { (yyval.type_node) = InsertNode(Def, (yyloc).first_line, 1, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 125 "syntax.y"
    { (yyval.type_node) = InsertNode(Def, yylineno, -1, 0); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 127 "syntax.y"
    { (yyval.type_node) = InsertNode(DecList, (yyloc).first_line, 1, 1, (yyvsp[(1) - (1)].type_node)); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 128 "syntax.y"
    { (yyval.type_node) = InsertNode(DecList, (yyloc).first_line, 2, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 130 "syntax.y"
    { (yyval.type_node) = InsertNode(Dec, (yyloc).first_line, 1, 1, (yyvsp[(1) - (1)].type_node)); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 131 "syntax.y"
    { (yyval.type_node) = InsertNode(Dec, (yyloc).first_line, 2, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 133 "syntax.y"
    { (yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 1, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 134 "syntax.y"
    { (yyval.type_node) =InsertNode(Exp, (yyloc).first_line, 2, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 135 "syntax.y"
    { (yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 3, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 136 "syntax.y"
    { expnode *RELOPn = RelopNode(RELOPm, yylineno, (char*)(yyvsp[(2) - (3)].type_id));
				(yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 4, 3, (yyvsp[(1) - (3)].type_node), RELOPn, (yyvsp[(3) - (3)].type_node)); 
				}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 139 "syntax.y"
    { (yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 5, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 140 "syntax.y"
    { (yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 6, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 141 "syntax.y"
    { (yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 7, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 142 "syntax.y"
    { (yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 8, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 143 "syntax.y"
    { (yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 9, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 144 "syntax.y"
    { (yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 10, 2, (yyvsp[(1) - (2)].type_node), (yyvsp[(2) - (2)].type_node)); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 145 "syntax.y"
    { (yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 11, 2, (yyvsp[(1) - (2)].type_node), (yyvsp[(2) - (2)].type_node)); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 146 "syntax.y"
    {	expnode *IDn = IdNode(IDm, yylineno, (char*)(yyvsp[(1) - (4)].type_id));
				(yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 12, 4, IDn, (yyvsp[(2) - (4)].type_node), (yyvsp[(3) - (4)].type_node), (yyvsp[(4) - (4)].type_node));
				}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 149 "syntax.y"
    {	expnode *IDn = IdNode(IDm, yylineno, (char*)(yyvsp[(1) - (3)].type_id));
				(yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 13, 3, IDn, (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node));
				}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 152 "syntax.y"
    {	(yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 14, 4, (yyvsp[(1) - (4)].type_node), (yyvsp[(2) - (4)].type_node), (yyvsp[(3) - (4)].type_node), (yyvsp[(4) - (4)].type_node)); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 153 "syntax.y"
    { 	expnode *IDn = IdNode(IDm, yylineno, (char*)(yyvsp[(3) - (3)].type_id));
				(yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 15, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), IDn);
				}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 156 "syntax.y"
    {	expnode *IDn = IdNode(IDm, yylineno, (char*)(yyvsp[(1) - (1)].type_id));
			(yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 16, 1, IDn);
			}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 159 "syntax.y"
    {	expnode *INTn = IntNode(INTm, yylineno, (yyvsp[(1) - (1)].type_int));
			(yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 17, 1, INTn);
			}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 162 "syntax.y"
    {	expnode *FLOATn = FloatNode(FLOATm, yylineno, (yyvsp[(1) - (1)].type_float));
			(yyval.type_node) = InsertNode(Exp, (yyloc).first_line, 18, 1, FLOATn);
			}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 165 "syntax.y"
    { (yyval.type_node)  = InsertNode(Exp, yylineno, -1, 0); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 166 "syntax.y"
    { (yyval.type_node) = InsertNode(Exp, yylineno, -1, 0); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 168 "syntax.y"
    { (yyval.type_node) = InsertNode(Args, (yyloc).first_line, 1, 3, (yyvsp[(1) - (3)].type_node), (yyvsp[(2) - (3)].type_node), (yyvsp[(3) - (3)].type_node)); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 169 "syntax.y"
    { (yyval.type_node) = InsertNode(Args, (yyloc).first_line, 2, 1, (yyvsp[(1) - (1)].type_node)); }
    break;



/* Line 1806 of yacc.c  */
#line 2085 "syntax.tab.c"
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
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 171 "syntax.y"

yyerror(char* msg)
{
    fprintf(stderr,"Error type B at line %d: %s\n", yylineno, msg);
    have_wrong = 1;
}

void PrintKind(int t_num, KIND kind, int lineno)
{
	int i;
	for(i=0; i<t_num; i++)
	{
		printf("  ");
	}
	switch(kind)
	{
		case ExtDefList:
		{
			printf("ExtDefList (%d)\n", lineno);
			break;
		}
		case ExtDef:
		{
			printf("ExtDef (%d)\n", lineno);
			break;
		}
		case Specifier:
		{
			printf("Specifier (%d)\n", lineno);
			break;
		}
		case ExtDecList:
		{
			printf("ExtDecList (%d)\n", lineno);
			break;
		}
		case FunDec:
		{
			printf("FunDec (%d)\n", lineno);
			break;
		}
		case CompSt:
		{
			printf("CompSt (%d)\n", lineno);
			break;
		}
		case VarDec:
		{
			printf("VarDec (%d)\n", lineno);
			break;
		}
		case StructSpecifier:
		{
			printf("StructSpecifier (%d)\n", lineno);
			break;
		}
		case OptTag:
		{
			printf("OptTag (%d)\n", lineno);
			break;
		}
		case DefList:
		{
			printf("DefList (%d)\n", lineno);
			break;
		}
		case Tag:
		{
			printf("Tag (%d)\n", lineno);
			break;
		}
		case VarList:
		{
			printf("VarList (%d)\n", lineno);
			break;
		}
		case ParamDec:
		{
			printf("ParamDec (%d)\n", lineno);
			break;
		}
		case StmtList:
		{
			printf("StmtList (%d)\n", lineno);
			break;
		}
		case Stmt:
		{
			printf("Stmt (%d)\n", lineno);
			break;
		}
		case Exp:
		{
			printf("Exp (%d)\n", lineno);
			break;
		}
		case Def:
		{
			printf("Def (%d)\n", lineno);
			break;
		}
		case DecList:
		{
			printf("DecList (%d)\n", lineno);
			break;
		}
		case Dec:
		{
			printf("Dec (%d)\n", lineno);
			break;
		}
		case Args:
		{
			printf("Args (%d)\n", lineno);
			break;
		}
		default:
		{
			printf("error in type 1\n");
			break;
		}
	}
}

void PrintTerm(int t_num, TERM term)
{
	int i;
	for(i=0; i<t_num; i++)
	{
		printf("  ");
	}
	switch(term)
	{
		case SEMIm:
		{
			printf("SEMI\n");
			break;
		}
		case COMMAm:
		{
			printf("COMMA\n");
			break;
		}
		case ASSIGNOPm:
		{
			printf("ASSIGNOP\n");
			break;
		}
		case PLUSm:
		{
			printf("PLUS\n");
			break;
		}
		case MINUSm:
		{
			printf("MINUS\n");
			break;
		}
		case STARm:
		{
			printf("STAR\n");
			break;
		}
		case DIVm:
		{
			printf("DIV\n");
			break;
		}
		case ANDm:
		{
			printf("AND\n");
			break;
		}
		case ORm:
		{
			printf("OR\n");
			break;
		}
		case DOTm:
		{
			printf("DOT\n");
			break;
		}
		case NOTm:
		{
			printf("NOT\n");
			break;
		}
		case LPm:
		{
			printf("LP\n");
			break;
		}
		case RPm:
		{
			printf("RP\n");
			break;
		}
		case LBm:
		{
			printf("LB\n");
			break;
		}
		case RBm:
		{
			printf("RB\n");
			break;
		}
		case LCm:
		{
			printf("LC\n");
			break;
		}
		case RCm:
		{
			printf("RC\n");
			break;
		}
		case STRUCTm:
		{
			printf("STRUCT\n");
			break;
		}
		case RETURNm:
		{
			printf("RETURN\n");
			break;
		}
		case IFm:
		{
			printf("IF\n");
			break;
		}
		case ELSEm:
		{
			printf("ELSE\n");
			break;
		}
		case WHILEm:
		{
			printf("WHILE\n");
			break;
		}
		default:
		{
			printf("error at type 2\n");
			break;
		}
	}
}

void PrintMean(int t_num, expnode *mean_node)
{
	int i;
	for(i=0; i<t_num; i++)
	{
		printf("  ");
	}
	switch(mean_node->mean)
	{
		case IDm:
		{
			printf("ID: %s\n", mean_node->id_vaule);
			break;
		}
		case INTm:
		{
			printf("INT: %d\n", mean_node->int_vaule);
			break;
		}
		case FLOATm:
		{
			printf("FLOAT: %f\n", mean_node->float_vaule);
			break;
		}
		case TYPEm:
		{
			if(mean_node->type_vaule == 0)
			{
				printf("TYPE: int\n");
				break;
			}
			else
			{
				printf("TYPE: float\n");
				break;
			}
		}
		case RELOPm:
		{
			printf("RELOP: ");
			switch(mean_node->relop_vaule)
			{
				case 1:
				{
					printf(">\n");
					break;
				}
				case 2:
				{
					printf("<\n");
					break;
				}
				case 3:
				{
					printf(">=\n");
					break;
				}
				case 4:
				{
					printf("<=\n");
					break;
				}
				case 5:
				{
					printf("==\n");
					break;
				}
				case 6:
				{
					printf("!=\n");
					break;
				}
				default:
				{
					printf("relop error\n");
					break;
				}
			}
			break;
		}
		default:
		{
			printf("error print at type 3\n");
		}
	}
}

void PrintTree()
{
	if(have_wrong == 1)
	{
		return;
	}
//	printf("print start\n");
	expnode *NODE = RootNode;
	int tab_num = 0;
	if(NODE->kind == Program)
	{
		printf("Program (%d)\n", NODE->lineno);
		NODE->search_num = 1;
		NODE = NODE->son_node[0];
		tab_num++;
	}
	else
	{
		printf("error\n");
		return;
	}
	while(1)
	{
		if(NODE->kind == Program && NODE->node_type == 1)
		{
//			printf("print end\n");
			break;
		}
		switch(NODE->node_type)
		{
			case 1:
			{
				if(NODE->search_num == 0)
				{
					PrintKind(tab_num, NODE->kind, NODE->lineno);
				}
				if(NODE->search_num < NODE->node_sum)
				{
					int now_num = NODE->search_num;
					NODE->search_num++;
					tab_num++;
					if(NODE->son_node[now_num]->node_sum > 0 || NODE->son_node[now_num]->node_type != 1)
					{
						NODE = NODE->son_node[now_num];
					}
					else
					{
						tab_num--;
					}
				}
				else
				{
					NODE->search_num = 0;
					NODE = NODE->father_node;
					tab_num--;
				}
				break;
			}
			case 2:
			{
				PrintTerm(tab_num, NODE->term);
				NODE = NODE->father_node;
				tab_num--;
				break;
			}
			case 3:
			{
				PrintMean(tab_num, NODE);
				NODE = NODE->father_node;
				tab_num--;
				break;
			}
			default:
			{
				printf("error in the null\n");
				break;
			}
		}
	}
}

