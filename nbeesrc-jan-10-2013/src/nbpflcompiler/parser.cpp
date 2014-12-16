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
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse         pfl_parse
#define yylex           pfl_lex
#define yyerror         pfl_error
#define yylval          pfl_lval
#define yychar          pfl_char
#define yydebug         pfl_debug
#define yynerrs         pfl_nerrs
#define yylloc          pfl_lloc

/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 8 "gramm.y"



//#define YYDEBUG 1

/*
hack to overcome the  "warning C4273: 'malloc' : inconsistent dll linkage" in visual studio when linking the dll C runtime
*/
#ifdef WIN32
  #define YYMALLOC malloc
  #define YYFREE free
#endif

#include <stdlib.h>
#include "defs.h"
#include "compile.h"
#include "utils.h"
#include "pflexpression.h"
#include "tree.h"
#include "symbols.h"
#include "typecheck.h"
#include <limits.h>





/* Line 268 of yacc.c  */
#line 107 "parser.cpp"

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
     PFL_RETURN_PACKET = 258,
     PFL_EXTRACT_FIELDS = 259,
     PFL_ON = 260,
     PFL_PORT = 261,
     PFL_NUMBER = 262,
     PFL_HEXNUMBER = 263,
     PFL_PROTOCOL = 264,
     PFL_PROTOFIELD = 265,
     PFL_PROTOCOL_INDEX = 266,
     PFL_PROTOFIELD_INDEX = 267,
     PFL_PROTOMULTIFIELD_INDEX = 268,
     PFL_MULTIPROTOFIELD = 269,
     PFL_PROTOMULTIFIELD = 270,
     PFL_IPV4ADDR = 271,
     PFL_IPV6ADDR = 272,
     PFL_MACADDR = 273,
     PFL_ADD = 274,
     PFL_ADDADD = 275,
     PFL_SUB = 276,
     PFL_MULMUL = 277,
     PFL_BWAND = 278,
     PFL_BWOR = 279,
     PFL_BWXOR = 280,
     PFL_BWNOT = 281,
     PFL_SHL = 282,
     PFL_SHR = 283,
     PFL_AND = 284,
     PFL_OR = 285,
     PFL_NOT = 286,
     PFL_EQ = 287,
     PFL_NE = 288,
     PFL_LT = 289,
     PFL_LE = 290,
     PFL_GT = 291,
     PFL_GE = 292,
     PFL_MATCHES = 293,
     PFL_CONTAINS = 294,
     PFL_SENSITIVE = 295,
     PFL_STRING = 296,
     PFL_IN = 297,
     PFL_NOTIN = 298,
     PFL_QUESTION = 299,
     PFL_ANY = 300,
     PFL_TUNNELED = 301,
     PFL_FULLENCAP = 302,
     PFL_MUL = 303,
     PFL_MUOLMUL = 304
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 43 "gramm.y"

    FieldsList_t    			*FieldsList;
    SymbolField					*Field;
    PFLStatement    			*stmt;
    PFLAction       			*act;
    PFLExpression				*exp;
    uint32						index;
    Node						*IRExp;
    char						id[ID_LEN];
    uint32						number;	
    bool						flag;
    PFLRepeatOperator   		repOp;
    PFLSetExpression*			setExp;     
    list<PFLSetExpression*>* 	setExpList;  
    list<PFLExpression*>*   	expList; 



/* Line 293 of yacc.c  */
#line 211 "parser.cpp"
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
#line 62 "gramm.y"


//NOTE: these declarations are duplicated in scanner.l, so if you modify them here you need to do the same in the other file
int pfl_lex (YYSTYPE *lvalp, YYLTYPE *llocp, struct ParserInfo *parserInfo);
int pfl_error(YYLTYPE *llocp, struct ParserInfo *parserInfo, const char *s);

PFLExpression *GenUnOpNode(PFLOperator op, PFLExpression *kid);
PFLExpression *GenBinOpNode(PFLOperator op, PFLExpression *kid1, PFLExpression *kid2);
PFLExpression *GenTermNode(SymbolProto *protocol, Node *irExpr);
PFLExpression *MergeNotInTermNode(ParserInfo *parserInfo, PFLExpression *node1);
PFLExpression *MergeTermNodes(ParserInfo *parserInfo, HIROpcodes op, PFLExpression *node1, PFLExpression *node2);
PFLExpression *ManagePFLProtoField(char *protoName, ParserInfo *parserInfo, YYLTYPE *llocp);

PFLExpression *GenProtoBytesRef(YYLTYPE *llocp, ParserInfo *parserInfo, char *protocol, uint32 offs, uint32 len);
PFLExpression *GenNumber(struct ParserInfo *parserInfo, uint32 value);
PFLExpression *GenString(struct ParserInfo *parserInfo, string value);	
bool CheckOperandTypes(ParserInfo *parserInfo, PFLExpression *expr);
SymbolField *CheckField(ParserInfo *parserInfo, char * protoName, YYLTYPE *llocp, uint32 headerIndex = 0);

set<pair<SymbolProto*,uint32> > protocolsForExtraction;

#define STORE_EXP_TEXT(e, fc, fl, lc, ll)	do{\
							string tmp_s;\
							tmp_s.assign(parserInfo->FilterString, fc, lc - fc);\
							e->SetExprText(tmp_s);\
						}while(0)

#define PFL_ERROR(l, pi, s) do{ pfl_error(l, pi, s); YYERROR; }while(0)


/* Line 343 of yacc.c  */
#line 267 "parser.cpp"

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
#define YYFINAL  37
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   228

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNRULES -- Number of states.  */
#define YYNSTATES  153

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      50,    51,     2,     2,    52,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    57,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    55,     2,    56,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,    54,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    13,    14,    16,    18,    20,
      25,    27,    31,    33,    35,    37,    39,    41,    46,    50,
      53,    56,    61,    66,    67,    69,    71,    75,    79,    81,
      85,    89,    91,    93,    96,   100,   103,   105,   107,   111,
     113,   117,   119,   121,   123,   125,   129,   131,   135,   139,
     142,   144,   146,   148,   152,   154,   158,   160,   162,   163,
     165,   170,   175,   179,   183,   187,   191,   195,   199,   201,
     203,   205,   207,   209,   213,   217,   221,   224,   228,   230,
     234,   238,   240,   244,   248,   250,   254,   256,   258,   260,
     262,   264,   269,   276,   278
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      59,     0,    -1,    79,    60,    -1,    60,    61,    -1,    79,
      60,    61,    -1,    -1,    47,    -1,    65,    -1,    62,    -1,
       4,    50,    63,    51,    -1,    64,    -1,    63,    52,    64,
      -1,    10,    -1,    14,    -1,    15,    -1,    12,    -1,    13,
      -1,     3,     5,     6,    92,    -1,    50,    79,    51,    -1,
      82,    67,    -1,    31,    66,    -1,    82,    67,    42,    68,
      -1,    82,    67,    43,    69,    -1,    -1,    46,    -1,    70,
      -1,    68,    42,    70,    -1,    68,    43,    69,    -1,    71,
      -1,    69,    43,    71,    -1,    69,    42,    68,    -1,    71,
      -1,    45,    -1,    45,    75,    -1,    72,    75,    67,    -1,
      72,    67,    -1,    82,    -1,    73,    -1,    53,    74,    54,
      -1,    76,    -1,    74,    52,    76,    -1,    19,    -1,    48,
      -1,    44,    -1,    77,    -1,    76,    30,    77,    -1,    78,
      -1,    77,    29,    77,    -1,    50,    76,    51,    -1,    31,
      78,    -1,    82,    -1,    80,    -1,    81,    -1,    80,    30,
      81,    -1,    66,    -1,    81,    29,    81,    -1,    86,    -1,
      84,    -1,    -1,    40,    -1,    85,    38,    41,    83,    -1,
      85,    39,    41,    83,    -1,    87,    32,    87,    -1,    87,
      33,    87,    -1,    87,    36,    87,    -1,    87,    37,    87,
      -1,    87,    34,    87,    -1,    87,    35,    87,    -1,    10,
      -1,    12,    -1,     9,    -1,    11,    -1,    88,    -1,    87,
      23,    88,    -1,    87,    24,    88,    -1,    87,    25,    88,
      -1,    26,    88,    -1,    50,    87,    51,    -1,    89,    -1,
      88,    27,    89,    -1,    88,    28,    89,    -1,    90,    -1,
      89,    20,    90,    -1,    89,    21,    90,    -1,    91,    -1,
      90,    22,    90,    -1,    92,    -1,    16,    -1,    18,    -1,
      10,    -1,    12,    -1,     9,    55,    92,    56,    -1,     9,
      55,    92,    57,    92,    56,    -1,     7,    -1,     8,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   189,   189,   207,   220,   236,   239,   246,   247,   253,
     262,   269,   279,   294,   314,   344,   384,   433,   442,   447,
     465,   482,   500,   521,   524,   530,   539,   546,   560,   565,
     570,   581,   582,   594,   605,   614,   626,   632,   636,   642,
     649,   658,   663,   667,   673,   674,   688,   689,   703,   710,
     729,   740,   744,   745,   770,   771,   794,   795,   800,   803,
     808,   872,   932,   946,   961,   976,   991,  1006,  1024,  1032,
    1114,  1131,  1162,  1163,  1180,  1195,  1210,  1218,  1225,  1226,
    1241,  1259,  1260,  1275,  1293,  1294,  1311,  1318,  1328,  1339,
    1390,  1453,  1462,  1474,  1485
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PFL_RETURN_PACKET",
  "PFL_EXTRACT_FIELDS", "PFL_ON", "PFL_PORT", "PFL_NUMBER",
  "PFL_HEXNUMBER", "PFL_PROTOCOL", "PFL_PROTOFIELD", "PFL_PROTOCOL_INDEX",
  "PFL_PROTOFIELD_INDEX", "PFL_PROTOMULTIFIELD_INDEX",
  "PFL_MULTIPROTOFIELD", "PFL_PROTOMULTIFIELD", "PFL_IPV4ADDR",
  "PFL_IPV6ADDR", "PFL_MACADDR", "PFL_ADD", "PFL_ADDADD", "PFL_SUB",
  "PFL_MULMUL", "PFL_BWAND", "PFL_BWOR", "PFL_BWXOR", "PFL_BWNOT",
  "PFL_SHL", "PFL_SHR", "PFL_AND", "PFL_OR", "PFL_NOT", "PFL_EQ", "PFL_NE",
  "PFL_LT", "PFL_LE", "PFL_GT", "PFL_GE", "PFL_MATCHES", "PFL_CONTAINS",
  "PFL_SENSITIVE", "PFL_STRING", "PFL_IN", "PFL_NOTIN", "PFL_QUESTION",
  "PFL_ANY", "PFL_TUNNELED", "PFL_FULLENCAP", "PFL_MUL", "PFL_MUOLMUL",
  "'('", "')'", "','", "'{'", "'}'", "'['", "']'", "':'", "$accept",
  "Statement", "FullEncap", "Action", "ExtractFields", "FieldsList",
  "FieldsListItem", "ReturnPkt", "UnaryExpression", "Tunnel",
  "InExpression", "NotInExpression", "ProtoOrAny", "Proto",
  "ProtocolOrSet", "SetOfProtocol", "ElementOfSet", "Repeater",
  "SetOrExpression", "SetAndExpression", "SetUnaryExpression",
  "BoolExpression", "OrExpression", "AndExpression", "BoolOperand",
  "sensitive", "RelExpression", "ProtoFieldOrProtofieldIndex", "Protocol",
  "BitwiseExpression", "ShiftExpression", "AddExpression", "MulExpression",
  "Term", "GenericNumber", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
      40,    41,    44,   123,   125,    91,    93,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    58,    59,    59,    59,    60,    60,    61,    61,    62,
      63,    63,    64,    64,    64,    64,    64,    65,    66,    66,
      66,    66,    66,    67,    67,    68,    68,    68,    69,    69,
      69,    70,    70,    70,    71,    71,    72,    72,    73,    74,
      74,    75,    75,    75,    76,    76,    77,    77,    78,    78,
      78,    79,    80,    80,    81,    81,    82,    82,    83,    83,
      84,    84,    84,    84,    84,    84,    84,    84,    85,    85,
      86,    86,    87,    87,    87,    87,    87,    87,    88,    88,
      88,    89,    89,    89,    90,    90,    91,    91,    91,    91,
      91,    91,    91,    92,    92
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     3,     0,     1,     1,     1,     4,
       1,     3,     1,     1,     1,     1,     1,     4,     3,     2,
       2,     4,     4,     0,     1,     1,     3,     3,     1,     3,
       3,     1,     1,     2,     3,     2,     1,     1,     3,     1,
       3,     1,     1,     1,     1,     3,     1,     3,     3,     2,
       1,     1,     1,     3,     1,     3,     1,     1,     0,     1,
       4,     4,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     3,     3,     3,     2,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     1,     1,     1,     1,
       1,     4,     6,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,    93,    94,    70,    89,    71,    90,    87,    88,     0,
       0,     6,     0,     0,     0,    54,     5,    51,    52,    23,
      57,     0,    56,     0,    72,    78,    81,    84,    86,     0,
       0,    89,    90,    76,    20,     0,     0,     1,     0,     0,
       3,     8,     7,     2,     0,     0,    24,    19,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    18,    77,     0,     0,     4,
      53,    55,     0,     0,    58,    58,    73,    74,    75,     0,
      62,    63,    66,    67,    64,    65,    79,    80,    82,    83,
      85,    91,     0,     0,    12,    15,    16,    13,    14,     0,
      10,    32,     0,    21,    25,    31,    23,    37,    36,    22,
      28,    59,    60,    61,     0,     0,    17,     9,     0,    41,
      43,    42,    33,     0,     0,     0,    39,    44,    46,    50,
       0,     0,    35,    23,     0,     0,    92,    11,    49,     0,
       0,    38,     0,     0,    26,    27,    34,    30,    29,    48,
      40,    45,    47
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    40,    41,    99,   100,    42,    15,    47,
     103,   109,   104,   105,   106,   107,   125,   122,   126,   127,
     128,    16,    17,    18,   108,   112,    20,    21,    22,    23,
      24,    25,    26,    27,    28
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -119
static const yytype_int16 yypact[] =
{
      78,  -119,  -119,   -47,   -18,  -119,    20,  -119,  -119,   210,
     123,  -119,   123,    11,    67,  -119,   -23,    -4,    10,    15,
    -119,    59,  -119,   179,    72,    85,    31,  -119,  -119,   100,
     -47,  -119,  -119,    72,  -119,    32,   157,  -119,    90,    51,
    -119,  -119,  -119,    67,   123,   123,  -119,    68,    62,    77,
     210,   210,   210,   160,   160,   160,   160,   160,   160,   210,
     210,   210,   210,   210,    56,  -119,  -119,   114,    28,  -119,
      10,  -119,     7,    66,    89,    89,    72,    72,    72,   160,
      44,    44,    44,    44,    44,    44,    85,    85,    31,    31,
      31,  -119,   100,   100,  -119,  -119,  -119,  -119,  -119,    63,
    -119,   -16,   148,    79,  -119,  -119,   -17,  -119,  -119,    84,
    -119,  -119,  -119,  -119,    12,    82,  -119,  -119,    28,  -119,
    -119,  -119,  -119,   148,   148,    39,   120,   115,  -119,  -119,
       7,    66,  -119,    15,     7,    66,  -119,  -119,  -119,   -21,
     148,  -119,   148,   148,  -119,  -119,  -119,  -119,  -119,  -119,
     120,   115,  -119
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -119,  -119,   135,   109,  -119,  -119,    35,  -119,   151,   -99,
      29,    34,    41,   -69,  -119,  -119,  -119,    69,  -118,    -6,
      54,   150,  -119,   101,     0,   108,  -119,  -119,  -119,    -7,
       4,    88,    18,  -119,   -28
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -70
static const yytype_int16 yytable[] =
{
      19,    64,   119,   119,   110,    36,   139,   132,    29,   142,
      19,    37,    19,    33,     1,     2,     3,     4,     5,     6,
     -68,   -68,   150,     7,    11,     8,    44,   120,   120,    46,
     149,   121,   121,     9,   146,    50,    51,    52,    94,    45,
      95,    96,    97,    98,    19,    19,    80,    81,    82,    83,
      84,    85,   101,    63,    76,    77,    78,    79,   -69,   -69,
     102,    46,   110,    66,   115,   116,   148,    50,    51,    52,
      38,    39,   114,     1,     2,     3,     4,     5,     6,    88,
      89,    90,     7,    65,     8,     1,     2,     3,     4,     5,
       6,   140,     9,   141,     7,    67,     8,    48,    49,    59,
      60,    68,   129,    74,     9,    61,    62,     1,     2,    10,
      72,    73,    91,    92,   117,   118,    79,    36,    75,   102,
      93,   130,   131,   129,   129,    11,   134,   135,    12,   111,
       1,     2,     3,     4,     5,     6,   151,   152,   136,     7,
     129,     8,   129,   129,   143,    70,    71,    86,    87,     9,
     142,    43,    69,   137,    10,     1,     2,     3,     4,     5,
       6,    34,    35,   147,     7,   145,     8,     1,     2,    30,
      31,   144,    32,    12,     9,   133,     7,   138,     8,   123,
      50,    51,    52,   113,     0,     0,     9,     0,     0,    53,
      54,    55,    56,    57,    58,     0,     0,     0,   124,     0,
       0,     0,    50,    51,    52,     0,     0,     0,    66,     0,
      79,    53,    54,    55,    56,    57,    58,     1,     2,    30,
      31,     0,    32,     0,     0,     0,     7,     0,     8
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-119))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,    29,    19,    19,    73,    12,   124,   106,    55,    30,
      10,     0,    12,     9,     7,     8,     9,    10,    11,    12,
      38,    39,   140,    16,    47,    18,    30,    44,    44,    46,
      51,    48,    48,    26,   133,    23,    24,    25,    10,    29,
      12,    13,    14,    15,    44,    45,    53,    54,    55,    56,
      57,    58,    45,    22,    50,    51,    52,    50,    38,    39,
      53,    46,   131,    51,    92,    93,   135,    23,    24,    25,
       3,     4,    79,     7,     8,     9,    10,    11,    12,    61,
      62,    63,    16,    51,    18,     7,     8,     9,    10,    11,
      12,    52,    26,    54,    16,     5,    18,    38,    39,    27,
      28,    50,   102,    41,    26,    20,    21,     7,     8,    31,
      42,    43,    56,    57,    51,    52,    50,   124,    41,    53,
       6,    42,    43,   123,   124,    47,    42,    43,    50,    40,
       7,     8,     9,    10,    11,    12,   142,   143,    56,    16,
     140,    18,   142,   143,    29,    44,    45,    59,    60,    26,
      30,    16,    43,   118,    31,     7,     8,     9,    10,    11,
      12,    10,    12,   134,    16,   131,    18,     7,     8,     9,
      10,   130,    12,    50,    26,   106,    16,   123,    18,    31,
      23,    24,    25,    75,    -1,    -1,    26,    -1,    -1,    32,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    23,    24,    25,    -1,    -1,    -1,    51,    -1,
      50,    32,    33,    34,    35,    36,    37,     7,     8,     9,
      10,    -1,    12,    -1,    -1,    -1,    16,    -1,    18
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,     9,    10,    11,    12,    16,    18,    26,
      31,    47,    50,    59,    60,    66,    79,    80,    81,    82,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    55,
       9,    10,    12,    88,    66,    79,    87,     0,     3,     4,
      61,    62,    65,    60,    30,    29,    46,    67,    38,    39,
      23,    24,    25,    32,    33,    34,    35,    36,    37,    27,
      28,    20,    21,    22,    92,    51,    51,     5,    50,    61,
      81,    81,    42,    43,    41,    41,    88,    88,    88,    50,
      87,    87,    87,    87,    87,    87,    89,    89,    90,    90,
      90,    56,    57,     6,    10,    12,    13,    14,    15,    63,
      64,    45,    53,    68,    70,    71,    72,    73,    82,    69,
      71,    40,    83,    83,    87,    92,    92,    51,    52,    19,
      44,    48,    75,    31,    50,    74,    76,    77,    78,    82,
      42,    43,    67,    75,    42,    43,    56,    64,    78,    76,
      52,    54,    30,    29,    70,    69,    67,    68,    71,    51,
      76,    77,    77
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
      yyerror (&yylloc, parserInfo, YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, parserInfo)
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
		  Type, Value, Location, parserInfo); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct ParserInfo *parserInfo)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, parserInfo)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    struct ParserInfo *parserInfo;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (parserInfo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct ParserInfo *parserInfo)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, parserInfo)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    struct ParserInfo *parserInfo;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, parserInfo);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, struct ParserInfo *parserInfo)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, parserInfo)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    struct ParserInfo *parserInfo;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , parserInfo);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, parserInfo); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, struct ParserInfo *parserInfo)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, parserInfo)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    struct ParserInfo *parserInfo;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (parserInfo);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 79: /* "BoolExpression" */

/* Line 1391 of yacc.c  */
#line 183 "gramm.y"
	{delete (yyvaluep->exp);};

/* Line 1391 of yacc.c  */
#line 1394 "parser.cpp"
	break;
      case 82: /* "BoolOperand" */

/* Line 1391 of yacc.c  */
#line 183 "gramm.y"
	{delete (yyvaluep->exp);};

/* Line 1391 of yacc.c  */
#line 1403 "parser.cpp"
	break;
      case 84: /* "RelExpression" */

/* Line 1391 of yacc.c  */
#line 183 "gramm.y"
	{delete (yyvaluep->exp);};

/* Line 1391 of yacc.c  */
#line 1412 "parser.cpp"
	break;
      case 86: /* "Protocol" */

/* Line 1391 of yacc.c  */
#line 183 "gramm.y"
	{delete (yyvaluep->exp);};

/* Line 1391 of yacc.c  */
#line 1421 "parser.cpp"
	break;
      case 87: /* "BitwiseExpression" */

/* Line 1391 of yacc.c  */
#line 184 "gramm.y"
	{delete (yyvaluep->exp);};

/* Line 1391 of yacc.c  */
#line 1430 "parser.cpp"
	break;
      case 88: /* "ShiftExpression" */

/* Line 1391 of yacc.c  */
#line 184 "gramm.y"
	{delete (yyvaluep->exp);};

/* Line 1391 of yacc.c  */
#line 1439 "parser.cpp"
	break;
      case 89: /* "AddExpression" */

/* Line 1391 of yacc.c  */
#line 184 "gramm.y"
	{delete (yyvaluep->exp);};

/* Line 1391 of yacc.c  */
#line 1448 "parser.cpp"
	break;
      case 90: /* "MulExpression" */

/* Line 1391 of yacc.c  */
#line 184 "gramm.y"
	{delete (yyvaluep->exp);};

/* Line 1391 of yacc.c  */
#line 1457 "parser.cpp"
	break;
      case 91: /* "Term" */

/* Line 1391 of yacc.c  */
#line 183 "gramm.y"
	{delete (yyvaluep->exp);};

/* Line 1391 of yacc.c  */
#line 1466 "parser.cpp"
	break;

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
int yyparse (struct ParserInfo *parserInfo);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


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
yyparse (struct ParserInfo *parserInfo)
#else
int
yyparse (parserInfo)
    struct ParserInfo *parserInfo;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

    /* Number of syntax errors so far.  */
    int yynerrs;

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
#line 190 "gramm.y"
    {
									if (yynerrs > 0)
									{									
										parserInfo->Filter = NULL;
									}
									else
									{ 
										parserInfo->Filter = new PFLStatement((yyvsp[(1) - (2)].exp), new PFLReturnPktAction(1), NULL,(yyvsp[(2) - (2)].flag));
									}
									(yyval.stmt) = parserInfo->Filter;			
									if(parserInfo->FilterString.length() != (size_t)((yyloc).last_column-(yyloc).first_column)){
										printf("Error messages:\n  1. [PFL error] syntax error\n");
										exit(-1);	
									}	
									
								}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 208 "gramm.y"
    {
									if (yynerrs > 0)
									{									
										parserInfo->Filter = NULL;
									}
									else
									{ 
										parserInfo->Filter = new PFLStatement(NULL, (PFLAction*)(yyvsp[(2) - (2)].act), NULL,(yyvsp[(1) - (2)].flag));
									}
									
									(yyval.stmt) = parserInfo->Filter;
								}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 221 "gramm.y"
    {
									if (yynerrs > 0)
									{									
										parserInfo->Filter = NULL;
									}
									else
									{ 
										parserInfo->Filter = new PFLStatement((yyvsp[(1) - (3)].exp),(PFLAction*)(yyvsp[(3) - (3)].act), NULL,(yyvsp[(2) - (3)].flag));
									}
									
									(yyval.stmt) = parserInfo->Filter;
								}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 236 "gramm.y"
    { 
									(yyval.flag) = false;
								}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 240 "gramm.y"
    {
									(yyval.flag) = true;
								}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 248 "gramm.y"
    {
									(yyval.act) = (yyvsp[(1) - (1)].act);
								}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 254 "gramm.y"
    {
									PFLExtractFldsAction *action= new PFLExtractFldsAction();
									for(FieldsList_t::iterator i = ((yyvsp[(3) - (4)].FieldsList))->begin(); i != ((yyvsp[(3) - (4)].FieldsList))->end(); i++)
										action->AddField((*i));
									(yyval.act)=action;
								}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 263 "gramm.y"
    {
									//$1->Protocol->NeedExtraction = true;
									FieldsList_t *list = new FieldsList_t();
									list->push_back((yyvsp[(1) - (1)].Field));
									(yyval.FieldsList) = list;
								}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 270 "gramm.y"
    {
		   							//$3->Protocol->NeedExtraction = true;
									FieldsList_t *list = (yyvsp[(1) - (3)].FieldsList);
									list->push_back((yyvsp[(3) - (3)].Field));
									(yyval.FieldsList) = list;
								}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 280 "gramm.y"
    {
									//i.e. proto.field
									SymbolField *field = CheckField(parserInfo,(yyvsp[(1) - (1)].id), &pfl_lloc);
									if (field == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Unknown field in extraction statement");
									}
									field->HeaderIndex.push_back(1);//remember that: proto.field == proto%1.field
									
									if(field->MultiProto && field->HeaderIndex.size()>0)
										PFL_ERROR(&pfl_lloc, parserInfo, "Unallowed extraction list. You wrote something like: \"proto*.field,proto%n.field\" or \"proto*.field,proto.field\"");
										
									(yyval.Field) = field;
								}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 295 "gramm.y"
    {
									//i.e. proto*.field
									string field_name((yyvsp[(1) - (1)].id));
									//we remove the "*" symbol from the field name, so we can check it properly
									string field_no_star = remove_chars(field_name, "*", "");
									SymbolField *field = CheckField(parserInfo, (char*)field_no_star.c_str(), &pfl_lloc);
									if (field == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Unknown field in extraction statement");
									}
									field->MultiProto = true;
									
									if(field->MultiProto && field->HeaderIndex.size()>0)
										PFL_ERROR(&pfl_lloc, parserInfo, "Unallowed extraction list. You wrote something like: \"proto*.field,proto%n.field\" or \"proto*.field,proto.field\"");

										
									(yyval.Field) = field;
																
								}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 315 "gramm.y"
    {
									//i.e. proto.field*
									string field_name((yyvsp[(1) - (1)].id));
									//we remove the "*" symbol from the field name, so we can check it properly
									string field_no_star = remove_chars(field_name, "*", "");
									SymbolField *field = CheckField(parserInfo, (char*)field_no_star.c_str(), &pfl_lloc);
									if (field == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Unknown field in extraction statement");
									}
									if(field->Name == "allfields")
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "\"proto.allfields*\" is not supported"); 
									}
																		
									field->HeaderIndex.push_back(1);

									//field->MultiField = true;
									uint32 multifield = (field->MultiProto) ? field->HeaderIndex.size()+1 : field->HeaderIndex.size();
									field->MultiFields.insert(multifield);


									if(field->MultiProto && field->HeaderIndex.size()>0)
										PFL_ERROR(&pfl_lloc, parserInfo, "Unallowed extraction list. You wrote something like: \"proto*.field,proto%n.field\" or \"proto*.field,proto.field\"");

										
									(yyval.Field) = field;
																
								}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 344 "gramm.y"
    {
									//i.e. proto%n.field
									char *fieldName, *index;
									uint32 num = 0;
									fieldName = strchr((yyvsp[(1) - (1)].id), '.');
									if(fieldName != NULL)
									{
										*fieldName = '\0';
										fieldName++;
									}

									index = strchr((yyvsp[(1) - (1)].id), '%');
									if(index != NULL)
									{
										*index = '\0';
										index++;
										str2int(index, &num, 10);
									}
									
									char *field_name((yyvsp[(1) - (1)].id));
									
									strcat(field_name, (char*)("."));
									strcat(field_name, fieldName);
									
									string field_ok = field_name;
									SymbolField *field = CheckField(parserInfo, (char*)field_ok.c_str(), &pfl_lloc,num);

									if (field == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Unknown field in extraction statement");
									}
									
									field->HeaderIndex.push_back(num);
									
									if(field->MultiProto && field->HeaderIndex.size()>0)
										PFL_ERROR(&pfl_lloc, parserInfo, "Unallowed extraction list. You wrote something like: \"proto*.field,proto%n.field\" or \"proto*.field,proto.field\"");

										
									(yyval.Field) = field;
								}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 384 "gramm.y"
    {
									//i.e. proto%n.field*									
									char *element = (yyvsp[(1) - (1)].id);
									element[sizeof(element)] = '\0';
																	
									char *fieldName, *index;
									uint32 num = 0;
									fieldName = strchr(element, '.');
									if(fieldName != NULL)
									{
										*fieldName = '\0';
										fieldName++;
									}

									index = strchr(element, '%');
									if(index != NULL)
									{
										*index = '\0';
										index++;
										str2int(index, &num, 10);
									}
									
									char *field_name(element);
									
									strcat(field_name, (char*)("."));
									strcat(field_name, fieldName);
									
									string field_ok = field_name;
									SymbolField *field = CheckField(parserInfo, (char*)field_ok.c_str(), &pfl_lloc,num);

									if (field == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Unknown field in extraction statement");
									}
									
									field->HeaderIndex.push_back(num);
									//field->MultiField = true;
									uint32 multifield = (field->MultiProto) ? field->HeaderIndex.size()+1 : field->HeaderIndex.size();
									field->MultiFields.insert(multifield);
									
									
									if(field->MultiProto && field->HeaderIndex.size()>0)
										PFL_ERROR(&pfl_lloc, parserInfo, "Unallowed extraction list. You wrote something like: \"proto*.field,proto%n.field\" or \"proto*.field,proto.field\"");

									(yyval.Field) = field;			
								}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 434 "gramm.y"
    {
										
										PFLReturnPktAction *action= new PFLReturnPktAction((yyvsp[(4) - (4)].number));
										(yyval.act)=action;
																			
									}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 443 "gramm.y"
    {
									(yyval.exp) = (yyvsp[(2) - (3)].exp);
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 448 "gramm.y"
    {
							//$1 is a term expression
							//we have to create a list containing the single protocol
							list<PFLExpression*> *elementList = new list<PFLExpression*>();
							elementList->push_back((yyvsp[(1) - (2)].exp));
							PFLSetExpression *setExpr = new PFLSetExpression(elementList,SET_OP,(yyvsp[(2) - (2)].flag)); //DEFAULT_ROP - DEFAULT_INCLUSION
							if (setExpr == NULL)
								throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
							setExpr->SetAnyPlaceholder(false);
							list<PFLSetExpression*> *setList = new list<PFLSetExpression*>();
							setList->push_back(setExpr);
							PFLRegExpExpression *expr = new PFLRegExpExpression(setList, REGEXP_OP); 
							if (expr == NULL)
								throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
							(yyval.exp) = expr;
							STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
						}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 466 "gramm.y"
    {
									PFLExpression *child = (yyvsp[(2) - (2)].exp);
									if (child->GetType() == PFL_TERM_EXPRESSION)
									{
										(yyval.exp) = MergeNotInTermNode(parserInfo, child);
									}
									else
									{
										PFLUnaryExpression *expr = new PFLUnaryExpression(child, UNOP_BOOLNOT);
										if (expr == NULL)
											throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
										
										(yyval.exp) = expr;
									}
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 482 "gramm.y"
    {
						//$1 is a PFLTermExpression
						//$4 is a list<PFLSetExpression*>*
						(*(yyvsp[(4) - (4)].setExpList)->begin())->SetInclusionOperator(IN_OP);
						list<PFLExpression*> *setList = new list<PFLExpression*>();
						setList->push_front((yyvsp[(1) - (4)].exp));
						PFLSetExpression *setExpr = new PFLSetExpression(setList,SET_OP,(yyvsp[(2) - (4)].flag));
						if (setExpr == NULL)
							throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
						setExpr->SetAnyPlaceholder(false);
						(yyvsp[(4) - (4)].setExpList)->push_front(setExpr);
						PFLRegExpExpression *expr = new PFLRegExpExpression((yyvsp[(4) - (4)].setExpList), REGEXP_OP); 
						if (expr == NULL)
							throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
						(yyval.exp) = expr;
						STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
												
					}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 500 "gramm.y"
    {
						//$1 is a PFLTermExpression
						//$4 is a list<PFLSetExpression*>*
						(*(yyvsp[(4) - (4)].setExpList)->begin())->SetInclusionOperator(NOTIN);
						list<PFLExpression*> *setList = new list<PFLExpression*>();
						setList->push_front(static_cast<PFLExpression*>((yyvsp[(1) - (4)].exp)));						
						PFLSetExpression *setExpr = new PFLSetExpression(setList,SET_OP,(yyvsp[(2) - (4)].flag));
						if (setExpr == NULL)
							throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
						setExpr->SetAnyPlaceholder(false);
						(yyvsp[(4) - (4)].setExpList)->push_front(setExpr);
						PFLRegExpExpression *expr = new PFLRegExpExpression((yyvsp[(4) - (4)].setExpList), REGEXP_OP); 
						if (expr == NULL)
							throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
						(yyval.exp) = expr;
						STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
						
					}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 521 "gramm.y"
    {
			(yyval.flag) = false;
		}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 525 "gramm.y"
    {
			(yyval.flag) = true;
		}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 530 "gramm.y"
    {
					//$1 contains a PFLSetExpression*
					//we have to create the list of sets
					list<PFLSetExpression*>* setExpList = new list<PFLSetExpression*>();
					//we add the set to the list
					setExpList->push_back((yyvsp[(1) - (1)].setExp));
					(yyval.setExpList) = setExpList;
				}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 539 "gramm.y"
    {
					//$3 contains a PFLSetExpression*
					//$1 contantains list<PFLSetExpression*>*
					(yyvsp[(3) - (3)].setExp)->SetInclusionOperator(IN_OP);
					(yyvsp[(1) - (3)].setExpList)->push_back((yyvsp[(3) - (3)].setExp));
					(yyval.setExpList) = (yyvsp[(1) - (3)].setExpList);
				}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 546 "gramm.y"
    {
					//$1 contantains list<PFLSetExpression*>*
					//$3 contantains list<PFLSetExpression*>*
			
					//the first element of $3 is involved in a "notin" operation
					(*(yyvsp[(3) - (3)].setExpList)->begin())->SetInclusionOperator(NOTIN);
					for(list<PFLSetExpression*>::iterator it = (yyvsp[(3) - (3)].setExpList)->begin(); it != (yyvsp[(3) - (3)].setExpList)->end(); it++)
						(yyvsp[(1) - (3)].setExpList)->push_back(*it);
					(yyvsp[(3) - (3)].setExpList)->clear();
					delete((yyvsp[(3) - (3)].setExpList));
					(yyval.setExpList) = (yyvsp[(1) - (3)].setExpList);
				}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 560 "gramm.y"
    {
				list<PFLSetExpression*>* setExpList = new list<PFLSetExpression*>();
				setExpList->push_back((yyvsp[(1) - (1)].setExp));
				(yyval.setExpList) = setExpList;
			}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 565 "gramm.y"
    {
				(yyvsp[(3) - (3)].setExp)->SetInclusionOperator(NOTIN);
				(yyvsp[(1) - (3)].setExpList)->push_back((yyvsp[(3) - (3)].setExp));
				(yyval.setExpList) = (yyvsp[(1) - (3)].setExpList);
			}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 570 "gramm.y"
    {
				//$1 contantains list<PFLSetExpression*>*
				//$3 contantains list<PFLSetExpression*>*
				(*(yyvsp[(3) - (3)].setExpList)->begin())->SetInclusionOperator(IN_OP);
				for(list<PFLSetExpression*>::iterator it = (yyvsp[(3) - (3)].setExpList)->begin(); it != (yyvsp[(3) - (3)].setExpList)->end(); it++)
					(yyvsp[(1) - (3)].setExpList)->push_back(*it);
				(yyvsp[(3) - (3)].setExpList)->clear();
				delete((yyvsp[(3) - (3)].setExpList));
				(yyval.setExpList) = (yyvsp[(1) - (3)].setExpList);
			}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 582 "gramm.y"
    {
				//we have found the any placeholder.
				//we create the empty list
				list<PFLExpression*> *setList = new list<PFLExpression*>();
				//we create the set expression
				PFLSetExpression *setExpr = new PFLSetExpression(setList,SET_OP);
				if (setExpr == NULL)
					throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
				setExpr->SetAnyPlaceholder(true);
				(yyval.setExp) = setExpr;	
			}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 594 "gramm.y"
    {
				list<PFLExpression*> *setList = new list<PFLExpression*>();
				PFLSetExpression *setExpr = new PFLSetExpression(setList,SET_OP,false,(yyvsp[(2) - (2)].repOp));//we specify the repeat operator in the constructor
				if (setExpr == NULL)
					throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
				setExpr->SetAnyPlaceholder(true);
				(yyval.setExp) = setExpr;
					
			}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 605 "gramm.y"
    {
				//$1 is a list<PFLExpression>*
				//We have to create the set expression				
				PFLSetExpression *setExpr = new PFLSetExpression((yyvsp[(1) - (3)].expList),SET_OP,(yyvsp[(3) - (3)].flag),(yyvsp[(2) - (3)].repOp));//we specify the repeat operator in the constructor
				if (setExpr == NULL)
					throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
				setExpr->SetAnyPlaceholder(false);
				(yyval.setExp) = setExpr;
			}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 614 "gramm.y"
    {
				//$1 is a list<PFLExpression>*
				//We have to create the set expression
				PFLSetExpression *setExpr = new PFLSetExpression((yyvsp[(1) - (2)].expList),SET_OP,(yyvsp[(2) - (2)].flag));
				if (setExpr == NULL)
					throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
				setExpr->SetAnyPlaceholder(false);
				(yyval.setExp) = setExpr;			
			}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 626 "gramm.y"
    {
				//the current element of the header chain is a single protocol, eventually with header indexing and/or predicate, and which is not within the { }
				list<PFLExpression*> *setList = new list<PFLExpression*>();
				setList->push_back((yyvsp[(1) - (1)].exp));
				(yyval.expList) = setList;
			}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 636 "gramm.y"
    { 
			(yyval.expList) = (yyvsp[(2) - (3)].expList);
			}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 643 "gramm.y"
    {
				//we create a list containing the elements of the set
				list<PFLExpression*> *setList = new list<PFLExpression*>();
				setList->push_back((yyvsp[(1) - (1)].exp));
				(yyval.expList) = setList;
			}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 649 "gramm.y"
    {
			list<PFLExpression*> *setList = new list<PFLExpression*>();
			setList->push_back((yyvsp[(3) - (3)].exp));
			for(list<PFLExpression*>::iterator it = (yyvsp[(1) - (3)].expList)->begin(); it != (yyvsp[(1) - (3)].expList)->end(); it++)
				setList->push_back(*it);
			(yyval.expList) = setList;			
			//[icerrato]		
		}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 659 "gramm.y"
    {
				   (yyval.repOp)=PLUS;
				   
			    }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 664 "gramm.y"
    {
		 		   (yyval.repOp)=STAR;
		  	    }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 668 "gramm.y"
    {
				   (yyval.repOp)=QUESTION;
			    }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 675 "gramm.y"
    {
                    	PFLBinaryExpression *expr = new PFLBinaryExpression((yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), BINOP_BOOLOR);
						if (expr == NULL)
							throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
						(yyval.exp) = expr;
				
						STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
				
						//[icerrato]
					}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 690 "gramm.y"
    {
				           
							PFLBinaryExpression *expr = new PFLBinaryExpression((yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), BINOP_BOOLAND);
							if (expr == NULL)
								throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
							(yyval.exp) = expr;
							
							STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
					
							//[icerrato]
						}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 704 "gramm.y"
    {
				(yyval.exp) = (yyvsp[(2) - (3)].exp);
				STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
				//[icerrato]
			}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 711 "gramm.y"
    {
				PFLExpression *child = (yyvsp[(2) - (2)].exp);
				if (child->GetType() == PFL_TERM_EXPRESSION)
				{
					(yyval.exp) = MergeNotInTermNode(parserInfo, child);
				}
				else
				{
					PFLUnaryExpression *expr = new PFLUnaryExpression(child, UNOP_BOOLNOT);
					if (expr == NULL)
						throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
					
					(yyval.exp) = expr;
				}
				STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
				
				//[icerrato]
			}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 730 "gramm.y"
    {
					(yyval.exp) = (yyvsp[(1) - (1)].exp);
					STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
					//[icerrato]			
				}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 746 "gramm.y"
    {
		                             /*
		                               * Let the automaton algorithms apply the desired optimizations; do not try
		                               * to do anything at this level about predicates.
		                               *	PFLExpression *termNode = MergeTermNodes(parserInfo, IR_ORB, $1, $3);
		                               */
		                              PFLExpression *termNode = NULL;
									if (termNode != NULL)
									{
										(yyval.exp) = termNode;
									}
									else
									{
										PFLBinaryExpression *expr = new PFLBinaryExpression((yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), BINOP_BOOLOR);
										if (expr == NULL)
											throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
										(yyval.exp) = expr;
									}
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 772 "gramm.y"
    {
                                                                  /*
                                                                   * Let the automaton algorithms apply the desired optimizations; do not try
                                                                   * to do anything at this level about predicates.
                                                                   *	PFLExpression *termNode = MergeTermNodes(parserInfo, IR_ANDB, $1, $3);
                                                                   */
                                                                  PFLExpression *termNode = NULL;
									if (termNode != NULL)
									{
										(yyval.exp) = termNode;
									}
									else
									{
										PFLBinaryExpression *expr = new PFLBinaryExpression((yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), BINOP_BOOLAND);
										if (expr == NULL)
											throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
										(yyval.exp) = expr;
									}
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 800 "gramm.y"
    {
				(yyval.flag) = false;
				}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 803 "gramm.y"
    {
				(yyval.flag) = true;	
				}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 808 "gramm.y"
    { 
									/*
									*  PFL_PROTOFIELD|PFL_PROTOFIELD_INDEX 
									*/
									
									PFLTermExpression *protoExp = static_cast<PFLTermExpression*>((yyvsp[(1) - (4)].exp));
									
									Node *node = protoExp->GetIRExpr();
									
									SymbolField *fieldSym = static_cast<SymbolField*>(node->Sym);
																					
									switch(fieldSym->FieldType)
										{
											case PDL_FIELD_FIXED: 
												static_cast<SymbolFieldFixed*>(fieldSym)->Sensitive = (yyvsp[(4) - (4)].flag);//sensitive;
												break;
											case PDL_FIELD_VARLEN:
												static_cast<SymbolFieldVarLen*>(fieldSym)->Sensitive = (yyvsp[(4) - (4)].flag);//sensitive;
												break;
											case PDL_FIELD_TOKEND:
												cout << "PFL warning: tokenended fields are deprecated" << endl;
												static_cast<SymbolFieldTokEnd*>(fieldSym)->Sensitive = (yyvsp[(4) - (4)].flag);//sensitive;
												break;
											case PDL_FIELD_LINE:
												static_cast<SymbolFieldLine*>(fieldSym)->Sensitive = (yyvsp[(4) - (4)].flag);//sensitive;
												break;
											case PDL_FIELD_PATTERN:
												static_cast<SymbolFieldPattern*>(fieldSym)->Sensitive = (yyvsp[(4) - (4)].flag);//sensitive;
												break;
											case PDL_FIELD_EATALL:
												static_cast<SymbolFieldEatAll*>(fieldSym)->Sensitive = (yyvsp[(4) - (4)].flag);//sensitive;
												break;
											default:
												PFL_ERROR(&pfl_lloc, parserInfo, "Only fixed length, variable, tokenended, line, pattern and eatall fields are supported with kweword \"matches\" and \"contains\"");
										}
										
										
										
														
 									/*
									*  PFL_STRING
									*/
									
									PFLExpression *expr=GenString(parserInfo,(yyvsp[(3) - (4)].id));
									
									/*
									*  PFL_MATCHES
									*/
									
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_MATCH, /*protocol*/(yyvsp[(1) - (4)].exp), expr); 
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");
									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");
									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
									
					}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 872 "gramm.y"
    {
									/*
									*  PFL_PROTOFIELD|PFL_PROTOFIELD_INDEX 
									*/
								
									PFLTermExpression *protoExp = static_cast<PFLTermExpression*>((yyvsp[(1) - (4)].exp));
									
									Node *node = protoExp->GetIRExpr();
									
									SymbolField *fieldSym = static_cast<SymbolField*>(node->Sym);
																					
									switch(fieldSym->FieldType)
										{
											case PDL_FIELD_FIXED: 
												static_cast<SymbolFieldFixed*>(fieldSym)->Sensitive = (yyvsp[(4) - (4)].flag);//sensitive;
												break;
											case PDL_FIELD_VARLEN:
												static_cast<SymbolFieldVarLen*>(fieldSym)->Sensitive = (yyvsp[(4) - (4)].flag);//sensitive;
												break;
											case PDL_FIELD_TOKEND:
												cout << "PFL warning: tokenended fields are deprecated" << endl;
												static_cast<SymbolFieldTokEnd*>(fieldSym)->Sensitive = (yyvsp[(4) - (4)].flag);//sensitive;
												break;
											case PDL_FIELD_LINE:
												static_cast<SymbolFieldLine*>(fieldSym)->Sensitive = (yyvsp[(4) - (4)].flag);//sensitive;
												break;
											case PDL_FIELD_PATTERN:
												static_cast<SymbolFieldPattern*>(fieldSym)->Sensitive = (yyvsp[(4) - (4)].flag);//sensitive;
												break;
											case PDL_FIELD_EATALL:
												static_cast<SymbolFieldEatAll*>(fieldSym)->Sensitive = (yyvsp[(4) - (4)].flag);//sensitive;
												break;
											default:
												PFL_ERROR(&pfl_lloc, parserInfo, "Only fixed length, variable, tokenended, line, pattern and eatall fields are supported with kweword \"matches\" and \"contains\"");
										}				
 									/*
									*  PFL_STRING
									*/
									
									PFLExpression *expr=GenString(parserInfo,(yyvsp[(3) - (4)].id));
									
									/*
									*  PFL_CONTAINS
									*/
									
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_CONTAINS, /*protocol*/(yyvsp[(1) - (4)].exp), expr); 
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");
									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");
									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
									
					}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 933 "gramm.y"
    {
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_EQI, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");
									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");
									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 947 "gramm.y"
    {
									
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_NEI, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");
									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");
									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 962 "gramm.y"
    {
									
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_GTI, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");
									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");
									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 977 "gramm.y"
    {
									
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_GEI, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");
									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");
									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 992 "gramm.y"
    {
									
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_LTI, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");
									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");
									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 1007 "gramm.y"
    {
									
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_LEI, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");
									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");
									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 1025 "gramm.y"
    {
					PFLExpression *protocol = ManagePFLProtoField((yyvsp[(1) - (1)].id),parserInfo, &pfl_lloc);
						if(protocol == NULL)
							YYERROR;
					(yyval.exp) = protocol; 
					
					}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 1033 "gramm.y"
    {
					char *index;
					uint32 num = 0;
					char *protoName = (yyvsp[(1) - (1)].id), *fieldName;
					GlobalSymbols &globalSymbols = *parserInfo->GlobalSyms;									
					SymbolField *fieldSym(0);
					fieldName = strchr((yyvsp[(1) - (1)].id), '.');
					
					index = strchr(protoName, '%');
					
					index[strlen(index)-strlen(strchr(protoName, '.'))]='\0';
					if (index != NULL)
					{
						*index = '\0';
						index++;
						str2int(index, &num, 10);
					}


					if (fieldName != NULL)
					{
						*fieldName = '\0';
						fieldName++;
					}

					SymbolProto *protoSymbol = globalSymbols.LookUpProto(protoName);
					
					if (protoSymbol == NULL)
					{
						PFL_ERROR(&pfl_lloc, parserInfo, "Invalid PROTOCOL identifier");

					}
					fieldSym = globalSymbols.LookUpProtoFieldByName(protoName, fieldName);
					
					if (fieldSym == NULL)
					{
						PFL_ERROR(&pfl_lloc, parserInfo, "Field not valid for the specified protocol");
					}
					
					switch(fieldSym->FieldType)
					{
						case PDL_FIELD_TOKEND:
							cout << "PFL warning: tokenended fields are deprecated" << endl;
						case PDL_FIELD_FIXED: 
						case PDL_FIELD_VARLEN:
						case PDL_FIELD_LINE:
						case PDL_FIELD_PATTERN:
						case PDL_FIELD_EATALL:
						case PDL_FIELD_BITFIELD:
							break;
						default:
							PFL_ERROR(&pfl_lloc, parserInfo, "Only fixed length, variable, tokenended, line, pattern, eatall and bitfield fields are supported");
					}
					HIRCodeGen &codeGen = parserInfo->CodeGen;
					Node *irExpr = codeGen.TermNode(IR_FIELD, fieldSym);
					if (irExpr == NULL)
						throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");									
					(yyval.exp) = GenTermNode(protoSymbol, irExpr);
					static_cast<PFLTermExpression*>((yyval.exp))->SetHeaderIndex(num);
					STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
		
					}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 1115 "gramm.y"
    {
									GlobalSymbols &globalSymbols = *parserInfo->GlobalSyms;
									SymbolProto *protoSymbol = globalSymbols.LookUpProto((yyvsp[(1) - (1)].id));
									
									if (protoSymbol == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Invalid PROTOCOL identifier");
									}
									PFLTermExpression *expr = new PFLTermExpression(protoSymbol);
									if (expr == NULL)
										throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
									
									(yyval.exp) = expr;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 1132 "gramm.y"
    {
									char *index;
									uint32 num = 0;
									GlobalSymbols &globalSymbols = *parserInfo->GlobalSyms;
									
									index = strchr((yyvsp[(1) - (1)].id), '%');
									if (index != NULL)
									{
										*index = '\0';
										index++;
										str2int(index, &num, 10);
									}
									
									SymbolProto *protoSymbol = globalSymbols.LookUpProto((yyvsp[(1) - (1)].id));
									
									if (protoSymbol == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Invalid PROTOCOL identifier");
									}
									
								
									PFLTermExpression *expr = new PFLTermExpression(protoSymbol, num);
									if (expr == NULL)
										throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
									
									(yyval.exp) = expr;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 1164 "gramm.y"
    {
									
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_ANDI, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");

									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");

									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 1181 "gramm.y"
    {
									
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_ORI, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");
									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");
									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 1196 "gramm.y"
    {
									
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_XORI, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");
									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");
									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 1211 "gramm.y"
    {
									PFLTermExpression *termNode = (PFLTermExpression*)(yyvsp[(2) - (2)].exp);
									HIRCodeGen &codeGen = parserInfo->CodeGen;
									termNode->SetIRExpr(codeGen.UnOp(IR_NOTI, static_cast<HIRNode*>(termNode->GetIRExpr())));
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 1219 "gramm.y"
    {
									(yyval.exp) = (yyvsp[(2) - (3)].exp);
								}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 1227 "gramm.y"
    {
									
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_SHLI, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");
									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");
									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 1242 "gramm.y"
    {
									
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_SHRI, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");
									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");
									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 1261 "gramm.y"
    {
									
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_ADDI, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");
									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");
									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 1276 "gramm.y"
    {
									
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_SUBI, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");
									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");
									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 1295 "gramm.y"
    {
									
									PFLExpression *termNode = MergeTermNodes(parserInfo, IR_MULI, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));
									if (termNode == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Operations between fields of different protocols are not supported");
									}
									if (!CheckOperandTypes(parserInfo, termNode))
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "type mismatch in expression");
									}
									(yyval.exp) = termNode;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 1312 "gramm.y"
    {									
									(yyval.exp) = GenNumber(parserInfo, (yyvsp[(1) - (1)].number));
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1318 "gramm.y"
    {
									uint32 add = 0;
									if (IPaddr2int((yyvsp[(1) - (1)].id), &add) != 0)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "IP address not valid!");
									}
									(yyval.exp) = GenNumber(parserInfo, add);
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1328 "gramm.y"
    {
			
									uint32 add = 0;
									if (MACaddr2int((yyvsp[(1) - (1)].id), &add) != 0)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "MAC address not valid!");
									}
									(yyval.exp) = GenNumber(parserInfo, add);
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
									PFL_ERROR(&pfl_lloc, parserInfo, "MAC address are not supported!");
								}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 1339 "gramm.y"
    {
									char *protoName = (yyvsp[(1) - (1)].id), *fieldName;
									GlobalSymbols &globalSymbols = *parserInfo->GlobalSyms;									
									SymbolField *fieldSym(0);
									fieldName = strchr((yyvsp[(1) - (1)].id), '.');

									if (fieldName != NULL)
									{
										*fieldName = '\0';
										fieldName++;
									}
									
									SymbolProto *protoSymbol = globalSymbols.LookUpProto(protoName);
									
									if (protoSymbol == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Invalid PROTOCOL identifier");

									}
									fieldSym = globalSymbols.LookUpProtoFieldByName(protoName, fieldName);
									
									if (fieldSym == NULL)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Field not valid for the specified protocol");
									}
									
									switch(fieldSym->FieldType)
									{
										case PDL_FIELD_TOKEND:
											cout << "PFL warning: tokenended fields are deprecated" << endl;
										case PDL_FIELD_FIXED: 
										case PDL_FIELD_VARLEN:
										case PDL_FIELD_LINE:
										case PDL_FIELD_PATTERN:
										case PDL_FIELD_EATALL:
										case PDL_FIELD_BITFIELD:
											break;
										default:
											PFL_ERROR(&pfl_lloc, parserInfo, "Only fixed length, variable, tokenended, line, pattern, eatall and bitfield fields are supported");
									}
									HIRCodeGen &codeGen = parserInfo->CodeGen;
									Node *irExpr = codeGen.TermNode(IR_FIELD, fieldSym);
									if (irExpr == NULL)
										throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");									
									(yyval.exp) = GenTermNode(protoSymbol, irExpr);
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1391 "gramm.y"
    {
								char *index;
								uint32 num = 0;
								char *protoName = (yyvsp[(1) - (1)].id), *fieldName;
								GlobalSymbols &globalSymbols = *parserInfo->GlobalSyms;									
								SymbolField *fieldSym(0);
								fieldName = strchr((yyvsp[(1) - (1)].id), '.');
								
								index = strchr(protoName, '%');
								
								index[strlen(index)-strlen(strchr(protoName, '.'))]='\0';
								if (index != NULL)
								{
									*index = '\0';
									index++;
									str2int(index, &num, 10);
								}

								if (fieldName != NULL)
								{
									*fieldName = '\0';
									fieldName++;
								}

								SymbolProto *protoSymbol = globalSymbols.LookUpProto(protoName);
								
								if (protoSymbol == NULL)
								{
									PFL_ERROR(&pfl_lloc, parserInfo, "Invalid PROTOCOL identifier");

								}
								fieldSym = globalSymbols.LookUpProtoFieldByName(protoName, fieldName);
								
								if (fieldSym == NULL)
								{
									PFL_ERROR(&pfl_lloc, parserInfo, "Field not valid for the specified protocol");
								}
								
								switch(fieldSym->FieldType)
								{
									case PDL_FIELD_TOKEND:
										cout << "PFL warning: tokenended fields are deprecated" << endl;
									case PDL_FIELD_FIXED: 
									case PDL_FIELD_VARLEN:
									case PDL_FIELD_LINE:
									case PDL_FIELD_PATTERN:
									case PDL_FIELD_EATALL:
									case PDL_FIELD_BITFIELD:
										break;
									default:
										PFL_ERROR(&pfl_lloc, parserInfo, "Only fixed length, variable, tokenended, line, pattern, eatall and bitfield fields are supported");
								}
								HIRCodeGen &codeGen = parserInfo->CodeGen;
								Node *irExpr = codeGen.TermNode(IR_FIELD, fieldSym);
								if (irExpr == NULL)
									throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");									
								(yyval.exp) = GenTermNode(protoSymbol, irExpr);
								static_cast<PFLTermExpression*>((yyval.exp))->SetHeaderIndex(num);
								STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
							
							
								}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1454 "gramm.y"
    {
									PFLExpression *expr = GenProtoBytesRef(&pfl_lloc, parserInfo, (yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].number), 1);
									if (expr == NULL)
										YYERROR;
									(yyval.exp) = expr;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								
								}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 1463 "gramm.y"
    {
									PFLExpression *expr = GenProtoBytesRef(&pfl_lloc, parserInfo, (yyvsp[(1) - (6)].id), (yyvsp[(3) - (6)].number), (yyvsp[(5) - (6)].number));
									if (expr == NULL)
										YYERROR;
									(yyval.exp) = expr;
									STORE_EXP_TEXT((yyval.exp), (yyloc).first_column, (yyloc).first_line, (yyloc).last_column, (yyloc).last_line);
								}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 1475 "gramm.y"
    {
									uint32 num = 0;
									if (str2int((yyvsp[(1) - (1)].id), &num, 10) != 0)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Decimal number out of range");
									}
									
									(yyval.number) = num;
								}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 1486 "gramm.y"
    {
									uint32 num = 0;
									if (str2int((yyvsp[(1) - (1)].id), &num, 16) != 0)
									{
										PFL_ERROR(&pfl_lloc, parserInfo, "Hexadecimal number out of range");
									}
									
									(yyval.number) = num;
								}
    break;



/* Line 1806 of yacc.c  */
#line 3387 "parser.cpp"
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
      yyerror (&yylloc, parserInfo, YY_("syntax error"));
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
        yyerror (&yylloc, parserInfo, yymsgp);
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
		      yytoken, &yylval, &yylloc, parserInfo);
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
		  yystos[yystate], yyvsp, yylsp, parserInfo);
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
  yyerror (&yylloc, parserInfo, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, parserInfo);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, parserInfo);
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
#line 1496 "gramm.y"


SymbolField* CheckField(ParserInfo *parserInfo, char * protoName, YYLTYPE *llocp, uint32 headerIndex)
{
	char *fieldName;
	GlobalSymbols &globalSymbols = *parserInfo->GlobalSyms;									
	//SymbolField *fieldSym(0);
	fieldName = strchr(protoName, '.');

	if (fieldName != NULL)
	{
		*fieldName = '\0';
		fieldName++;
	}

	SymbolProto *protoSymbol = globalSymbols.LookUpProto(protoName);
	
	if (protoSymbol == NULL)
	{
		return NULL;
	}

	if(strcmp(fieldName,"allfields")==0)
   	{	
   		if(protocolsForExtraction.count(make_pair<SymbolProto*,uint32>(protoSymbol,headerIndex))!=0)
   		{
   			pfl_error(llocp, parserInfo, "You cannot specify a protocol two times for the field extraction, if the second of them is on \"allfields\"");
   			return NULL;
   		}
   		SymbolField *sym = new SymbolField(fieldName,PDL_FIELD_ALLFIELDS,NULL);
       	sym->Protocol=protoSymbol;
       	globalSymbols.StoreProtoField(protoSymbol, sym);
		return sym;
   	}
    else
    {
    	protocolsForExtraction.insert(make_pair<SymbolProto*,uint32>(protoSymbol,headerIndex)); //this set is needed in order to verify that the protocol with all field is not present in the extractfields yet
		return globalSymbols.LookUpProtoFieldByName(protoName, fieldName);
	}
	
}

PFLExpression *GenUnOpNode(PFLOperator op, PFLExpression *kid)
{
	PFLUnaryExpression *expr = new PFLUnaryExpression(kid, op);
	if (expr == NULL)
		throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
	return expr;
}


PFLExpression *GenBinOpNode(PFLOperator op, PFLExpression *kid1, PFLExpression *kid2)
{
	PFLBinaryExpression *expr = new PFLBinaryExpression(kid1, kid2, op);
	if (expr == NULL)
		throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
	return expr;
}

PFLExpression *GenTermNode(SymbolProto *protocol, Node *irExpr)
{
	PFLTermExpression *expr = new PFLTermExpression(protocol, irExpr);
	if (expr == NULL)
		throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
	return expr;
}

PFLExpression *MergeNotInTermNode(ParserInfo *parserInfo, PFLExpression *node1)
{
	nbASSERT(parserInfo != NULL, "parserInfo cannot be NULL");
	nbASSERT(node1 != NULL, "node1 cannot be NULL");
	nbASSERT(node1->GetType() == PFL_TERM_EXPRESSION, "node1 should be a terminal node");
	PFLTermExpression *kid1 = (PFLTermExpression*)node1;

	PFLUnaryExpression *expr = new PFLUnaryExpression(kid1, UNOP_BOOLNOT);
	if (expr == NULL)
		throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");
	return expr;
}


HIRNode *ConvToInt(ParserInfo *parserInfo, HIRNode *node)
{
	nbASSERT(parserInfo != NULL, "parserInfo cannot be NULL");
	nbASSERT(node != NULL, "Node cannot be NULL");
	if (CheckIntOperand(node))
	{
		switch(node->Op)
		{
			case IR_ICONST:
			case IR_IVAR:
				return node;
				break;
			case IR_SVAR:
			case IR_FIELD:
			{
				HIRCodeGen &codeGen = parserInfo->CodeGen;
				node->NRefs--; //otherwise it will appear as a dag and this is not the case
				return codeGen.UnOp(IR_CINT, node);
			}break;
			default:
				return node;
				break;
		}
	}
	return NULL;
}

HIRNode *StringToString(ParserInfo *parserInfo, HIRNode *node)
{
	nbASSERT(parserInfo != NULL, "parserInfo cannot be NULL");
	nbASSERT(node != NULL, "Node cannot be NULL");

	switch(node->Op)
	{
			return node;
			break;
		case IR_SVAR:
		case IR_FIELD:
		{	//SymbolField *sf=(SymbolField*)node->Sym;		
			HIRCodeGen &codeGen = parserInfo->CodeGen;
			node->NRefs--; //otherwise it will appear as a dag and this is not the case
			return codeGen.UnOp(IR_CINT, node);
		}break;
		default:
			return node;
			break;
	}
	return node;
}

bool CheckOperandTypes(ParserInfo *parserInfo, PFLExpression *expr)
{
	nbASSERT(expr->GetType() == PFL_TERM_EXPRESSION, "expression should be a terminal node");
	nbASSERT(parserInfo != NULL, "parserInfo cannot be NULL");
	nbASSERT(expr != NULL, "expr cannot be NULL");
	nbASSERT(expr->GetType() == PFL_TERM_EXPRESSION, "expr should be a terminal node");
	HIRNode *node = static_cast<HIRNode*>(((PFLTermExpression*)expr)->GetIRExpr());
	nbASSERT(node != NULL, "Contained Node cannot be NULL");
	
	if (GET_OP_TYPE(node->Op) == IR_TYPE_INT)
	{      
		HIRNode *leftChild = node->GetLeftChild();
		HIRNode *rightChild = node->GetRightChild();
		if (leftChild)
		{
			leftChild = ConvToInt(parserInfo, leftChild);
			if(leftChild == NULL)
			{
				return false;
			} 
			node->SetLeftChild(leftChild);
		}
		if (rightChild)
		{		
			rightChild = ConvToInt(parserInfo, rightChild);
			if(rightChild == NULL)
			{
				return false;
			} 
			node->SetRightChild(rightChild);
		}
			
		return true;
	}
	
	else if (GET_OP_TYPE(node->Op) == IR_TYPE_STR)
	{
	
		HIRNode *leftChild = node->GetLeftChild();
		HIRNode *rightChild = node->GetRightChild();
		if (leftChild)
		{
			leftChild = StringToString(parserInfo, leftChild);
			if(leftChild == NULL)
			{
				return false;
			} 
			node->SetLeftChild(leftChild);
		}
		if (rightChild)
		{		
			rightChild = StringToString(parserInfo, rightChild);
			if(rightChild == NULL)
			{
				return false;
			} 
			node->SetRightChild(rightChild);
		}
		
		return true; 		
	}	
	
	nbASSERT(false, "SHOULD NOT BE HERE");
	return true;
} 

PFLExpression *MergeTermNodes(ParserInfo *parserInfo, HIROpcodes op, PFLExpression *node1, PFLExpression *node2)
{
	nbASSERT(parserInfo != NULL, "parserInfo cannot be NULL");
	nbASSERT(node1 != NULL, "node1 cannot be NULL");
	nbASSERT(node2 != NULL, "node2 cannot be NULL");
	//node1 should be a terminal node
	if(node1->GetType() != PFL_TERM_EXPRESSION)
		return NULL;
	//node2 should be a terminal node
	if(node2->GetType() != PFL_TERM_EXPRESSION)	
		return NULL;
	nbASSERT(node2->GetType() == PFL_TERM_EXPRESSION, "node2 should be a terminal node");
	PFLTermExpression *kid1 = (PFLTermExpression*)node1;
	PFLTermExpression *kid2 = (PFLTermExpression*)node2;

	// save protocol information about the two terminal nodes
	SymbolProto *proto1 = kid1->GetProtocol();
	SymbolProto *proto2 = kid2->GetProtocol();
	
	// save the IR trees of the two terminal nodes
	HIRNode *irExpr1 = static_cast<HIRNode*>(kid1->GetIRExpr()); //i.e. IR_FILED
	HIRNode *irExpr2 = static_cast<HIRNode*>(kid2->GetIRExpr()); //i.e. IR_SCONST
	
	if (proto1 != proto2)
	{
		// the two terminal nodes refer to different protocols
		if (proto2 == NULL)
		{
			nbASSERT(irExpr2 != NULL, "irExpr2 cannot be NULL");
			// if the second has a NULL protocol (i.e. it contains a constant expression) we delete it
			kid2->SetIRExpr(NULL);
			delete kid2;
		}
		else if (proto1 == NULL)
		{
			nbASSERT(irExpr1 != NULL, "irExpr1 cannot be NULL");
			// if the first has a NULL protocol (i.e. it contains a constant expression) we copy the protocol 
			// information from the second, then we delete the second
			kid1->SetProtocol(proto2);
			kid2->SetIRExpr(NULL);
			delete kid2;
		}
		else
		{
			//The two terminal nodes cannot be merged in a single PFLTermExpression node
			return NULL;
		}
	}
	else
	{
			// the two terminal nodes refer to the same protocol
			// so we simply delete the second
			kid2->SetIRExpr(NULL);
			delete kid2;
	}
	
	//handle the cases such as (ip and (ip.src == 10.0.0.1)) where one operand is redundant
	
	if (irExpr1 == NULL)
	{
		kid1->SetIRExpr(irExpr2);
		return kid1;
	}
	if (irExpr2 == NULL)
	{
		kid1->SetIRExpr(irExpr1);
		return kid1;
	}
	
	// we create a new Node as an op between the two subexpressions
	// and we append it to the first terminal node

	HIRCodeGen &codeGen = parserInfo->CodeGen;
	kid1->SetIRExpr(codeGen.BinOp(op, irExpr1, irExpr2));
	return kid1;
}

PFLExpression *GenNumber(struct ParserInfo *parserInfo, uint32 value)
{
	HIRCodeGen &codeGen = parserInfo->CodeGen;
	HIRNode *irExpr = codeGen.TermNode(IR_ICONST, codeGen.ConstIntSymbol(value));
	return GenTermNode(NULL, irExpr);
}

PFLExpression *GenString(struct ParserInfo *parserInfo, string value)
{
	HIRCodeGen &codeGen = parserInfo->CodeGen;
	HIRNode *irExpr = codeGen.TermNode(IR_SCONST,codeGen.ConstStrSymbol(value));
	return GenTermNode(NULL, irExpr);

}


PFLExpression *GenProtoBytesRef(YYLTYPE *llocp, ParserInfo *parserInfo, char *protocol, uint32 offs, uint32 len)
{
	GlobalSymbols &globalSymbols = *parserInfo->GlobalSyms;
	HIRCodeGen &codeGen = parserInfo->CodeGen;
	SymbolProto *protoSymbol = globalSymbols.LookUpProto(protocol);

	if (protoSymbol == NULL)
	{
		pfl_error(llocp, parserInfo, "Invalid PROTOCOL identifier");
		return NULL;
	}

	HIRNode *irExpr = codeGen.ProtoBytesRef(protoSymbol, offs, len);

	if (irExpr == NULL)
		throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");

	return GenTermNode(protoSymbol, irExpr);
}

PFLExpression *ManagePFLProtoField(char *protoName, ParserInfo *parserInfo, YYLTYPE *llocp){ 
	char *fieldName;
	GlobalSymbols &globalSymbols = *parserInfo->GlobalSyms;									
	SymbolField *fieldSym(0);
	fieldName = strchr(protoName, '.');

	if (fieldName != NULL)
	{
		*fieldName = '\0';
		fieldName++;
	}
	
	SymbolProto *protoSymbol = globalSymbols.LookUpProto(protoName);
		
	if (protoSymbol == NULL)
	{
		pfl_error(llocp, parserInfo, "Invalid PROTOCOL identifier");
		return NULL;

	}
	fieldSym = globalSymbols.LookUpProtoFieldByName(protoName, fieldName);
										
	if (fieldSym == NULL)
	{
		pfl_error(llocp, parserInfo, "The specified field is not valid for the specified protocol");
		return NULL;
	}
			
	HIRCodeGen &codeGen = parserInfo->CodeGen;
	Node *irExpr = codeGen.TermNode(IR_FIELD, fieldSym);
							
	if (irExpr == NULL)
		throw ErrorInfo(ERR_FATAL_ERROR, "MEMORY ALLOCATION FAILURE");									
	
	return GenTermNode(protoSymbol, irExpr); 
}

int pfl_error(YYLTYPE *llocp, struct ParserInfo *parserInfo, const char *s)
{
	parserInfo->ErrRecorder->PFLError(s);
	//fprintf(stderr, "%s\n", s);
	return 1;
}


void compile(ParserInfo *parserInfo, const char *filter, int debug)
{

#ifdef YYDEBUG
#if YYDEBUG != 0
	pfl_debug = debug;
#endif
#endif
	parserInfo->FilterString = string(filter);
	parserInfo->ResetFilter();
	pflcompiler_lex_init(filter);
	pfl_parse(parserInfo);
	pflcompiler_lex_cleanup();

} 

