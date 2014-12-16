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
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         nvmparser_parse
#define yylex           nvmparser_lex
#define yyerror         nvmparser_error
#define yylval          nvmparser_lval
#define yychar          nvmparser_char
#define yydebug         nvmparser_debug
#define yynerrs         nvmparser_nerrs


/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 9 "../../assembler/nvm_gramm.y"


#define YYDEBUG 1


#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#define YYMALLOC malloc
#define YYFREE free
#else
#include <sys/socket.h>
#include <netdb.h>
#endif

#include <stdio.h>

#if defined(_WIN32) && defined(_DEBUG)
#include <crtdbg.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <nbnetvm.h>
#include <netvm_bytecode.h>

#include "../opcodes.h"
#include "compiler.h"

#ifdef WIN32
#define snprintf _snprintf
#endif


/* compiler pass */
int pass;

void warn(const char *s);
int nvmparser_error(const char *s);

int eline = 1;			// line number, to keep track of errors
int stream_pointer = 0;		// current position in the created binary stream
int n_ports = 0;		// number of ports of this PE
int n_copros = 0;		// number of coprocessors this PE uses
int nwarns = 0;
int nerrs = 0;
char *errbuf = NULL;
int errbufpos = 0;
int errbufsize = 0;

char *warnbuf = NULL;
int warnbufpos = 0;
int warnbufsize = 0;

pvar	var_head = NULL;	// head of the variable list
pref	ref_head = NULL;	// head of the reference list
pseg	seg_head = NULL;	// head of the segment list
pport	port_head = NULL;	// head of the port list
pcopro	copro_head = NULL;	// head of the coprocessor list
pseg	cur_seg;
pseg	ip_to_lines_seg;

char tmp_char_buf[256];

uint32_t ij, id = 0;


swinfo *sw_head;
swinfo *sw_current;
int isnewswitch = 1;

metadata pe_metadata;

/*********************************/
/*   Winsock functions           */
/*********************************/

#ifdef _MSC_VER

/*start winsock*/
// FULVIO PER GIANLUCA: queste routine vengono create in automatico? In caso negativo, non possiamo mettere quelle
// che sono definite in sockutils?
int
wsockinit()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 1, 1);
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 )
	{
		return -1;
	}
	return 0;
}

int wsockcleanup()
{
	return WSACleanup();
}

struct addrinfo *
nametoaddrinfo(const char *name)
{
	struct addrinfo hints, *res;
	int error;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;	/*not really*/
	error = getaddrinfo(name, NULL, &hints, &res);
	if (error)
		return NULL;
	else
		return res;
}

#else
int wsockinit()
{
	return 0;
}

int wsockcleanup()
{
	return 0;
}
#endif



/*********************************/
/* Emit structures and functions */
/*********************************/

typedef void (*emit_func)(pseg segment, uint32_t value, uint32_t n);
emit_func emitm;	// current code emitter

// emit routine that returns the instructions length
void emit_lenght (pseg segment, uint32_t value, uint32_t len) {
	segment->cur_ip += len;
}

// emit routine that outputs the actual binary code
void emit_code (pseg segment, uint32_t value, uint32_t len) {
	switch (len) {
		case 1:
			segment->istream[segment->cur_ip] = (uint8_t) value;
			segment->cur_ip++;
			break;

		case 2:
			*((uint16_t *)(segment->istream + segment->cur_ip)) = (uint16_t) value;
			segment->cur_ip += 2;
			break;

		case 4:
			*((uint32_t *)(segment->istream + segment->cur_ip)) = value;
			segment->cur_ip += 4;
			break;

		default:;

	}

	return;
}


/**************************************************************/
/* Functions for the implementation of the switch instruction */
/**************************************************************/
swinfo *new_swinfo()
{
	swinfo *info = malloc(sizeof(struct SW_INFO));
	if (info == NULL)
		return NULL;
	memset(info, 0, sizeof(struct SW_INFO));
	if (sw_head == NULL)
	{
		sw_head = info;
		sw_current = info;
	}
	else
	{
		sw_current->next = info;
		sw_current = info;
	}
	return info;
}


/*************************************************/
/* Functions for the implementation of variables */
/*************************************************/

pvar search_var (char *label) {
	pvar v;

	v = var_head;
	while (v != NULL) {
		if (strcmp (v->label, label) == 0)
			return (v);
		else
			v = v->next;
	}
	return (NULL);
}

int insert_var (char *label, int val){
	pvar v;

	v = search_var (label);

	if (v != NULL) {
		nvmparser_error ("Variable already defined");
		return 0;
	}

	if((v = (pvar) malloc (sizeof (var))) != NULL) {
		strcpy (v->label, label);
		v->val = val;
		v->next = var_head;
		var_head = v;
		return 1;
	} else {
		nvmparser_error ("Out of memory");
		return 0;
	}
}

/***************************************************/
/* Functions for the implementation of jump labels */
/***************************************************/

pref search_ref (char *label) {
	pref v;

	v = ref_head;
	while (v != NULL) {
		if (strcmp (v->label, label) == 0)
			return (v);
		else
			v = v->next;
	}
	return (NULL);
}

pref insert_ref (char *label) {
	pref v;

	v = search_ref (label);

	if (v != NULL){
		nvmparser_error ("label already defined");
		return NULL;
	}

	if ((v = (pref) malloc (sizeof (ref))) != NULL) {
		strcpy (v->label, label);
		v->target = 0;
		v->next = ref_head;
		ref_head = v;
		return v;
	} else {
		nvmparser_error ("Out of memory");
		return NULL;
	}
}

/************************************************/
/* Functions for the implementation of segments */
/************************************************/

pseg search_seg (char *label) {
	pseg v;

	v = seg_head;
	while (v != NULL) {
		if (strcmp (v->label, label) == 0)
			return (v);
		else
			v = v->next;
	}
	return (NULL);
}

pseg insert_seg (char *label, int flags) {
	pseg v;

	v = search_seg (label);

	if (v != NULL) {
			nvmparser_error ("Segment declared twice");
			return NULL;
	}

	if ((v = (pseg) malloc (sizeof (seg))) != NULL) {
		strcpy (v->label, label);
		v->references = NULL;
		v->istream = NULL;
		v->flags = flags;
		v->cur_ip = 0;
		v->num_instr = 0;
		v->next = seg_head;
		seg_head = v;
		return v;
	} else {
		nvmparser_error ("Out of memory");
		return NULL;
	}
	
}

int allocate_istream (pseg v, uint32_t size){
	//printf ("Allocating %d bytes for a segment\n", size);
	v->istream = (char *) malloc (size);
	if (v->istream == NULL){
		nvmparser_error ("Out of memory");
		return 0;
	}
	v->cur_ip = 0;
	return 1;
}


/*********************************************/
/* Functions for the implementation of ports */
/*********************************************/

pport search_port (char *label) {
	pport v;

	v = port_head;
	while (v != NULL) {
		if (strcmp(v->label, label) == 0)
			return (v);
		else
			v = v->next;
	}
	return (NULL);
}

int add_port(char *label, int type) {
	pport v;

	v = search_port (label);

	if (v != NULL) {
		nvmparser_error ("port declared twice");
		return 0;
	}

	if ((v = (pport) malloc (sizeof (port))) != NULL) {
		strcpy (v->label, label);
		v->type = type;
		v->number = n_ports;
		v->next = port_head;
		port_head = v;

		// keep track of the number of ports allocated until now
		n_ports++;

		return 1;
	} else {
		nvmparser_error ("Out of memory");
		return 0;
	}
}


/****************************************************/
/* Functions for the implementation of coprocessors */
/****************************************************/

pcopro search_copro (char *label) {
	pcopro v;

	v = copro_head;
	while (v != NULL) {
		if (strcmp(v->label, label) == 0)
			return (v);
		else
			v = v->next;
	}
	return (NULL);
}

int add_copro (char *label, int regs) {
	pcopro v;

	v = search_copro (label);

	if (v != NULL) {
		nvmparser_error ("coprocessor declared twice");
		return -1;
	}

	if ((v = (pcopro) malloc (sizeof (copro))) != NULL) {
		strcpy (v->label, label);
		v->regs = regs;
		v->number = n_copros;
		v->next = copro_head;
		copro_head = v;

		// keep track of the number of ports allocated until now
		n_copros++;

		return v->number;
	} else {
		nvmparser_error ("Out of memory");
		return -1;
	}
}



/**************************************************************/
/* Functions for the implementation of data section variables */
/**************************************************************/

int search_dataval (char *label, uint32_t *target) {
	uint32_t *target2;
	int ret;

	ret = hash_table_lookup (htval, label, strlen (label), (void *) &target2);
	if (target)
		*target = *target2;

	return (ret);
}

int insert_dataval (char *label, uint32_t target) {
	int ret;
	uint32_t *ptr32;
	char *ptrstr;

	ret = nvmFAILURE;

	if (search_dataval (label, NULL)) {
		fprintf (stderr, "dataval label \"%s\" already defined\n", label);
	} else {
		/* We have to duplicate the data to be inserted in the hash table, as the hash table itself only uses
		 * pointers */
		if (!(ptr32 = (uint32_t *) malloc (sizeof (uint32_t)))) {
			nvmparser_error ("Cannot allocate memory");
		} else if (!(ptrstr = strdup (label))) {
			nvmparser_error ("Cannot allocate memory");
		} else {
			*ptr32 = target;
			if (!(hash_table_add (htval, ptrstr, strlen (ptrstr), ptr32))) {
				nvmparser_error ("Cannot add dataval to hash table");
			} else {
				ret = nvmSUCCESS;
			}
		}
	}

	return (ret);
}

/**
 * Parse a C-style string and convert escape sequencies.
 * @param[in] str The string to be parsed.
 * @param[inout] len The input string length (if -1 strlen() will be used), will be updated to the new string length upon return.
 */
char *c_string_unescape (char *str, int *len) {
	int i, j;
	char c, tmp[4], *eptr;

	if (*len == -1)
		*len = strlen (str);

	/* i is the index in the input string, j in the output */
	i = 0, j = 0;
	while (i < *len) {
		c = str[i];

		if (c == '\\' && i + 1 < *len) {
			switch (str[i + 1]) {
				case 'x':
				case 'X':
					if (i + 1 + 2 < *len) {
						/* Copy relevant part to temp string and parse it */
						tmp[0] = str[i + 2];
						tmp[1] = str[i + 3];
						tmp[2] = '\0';
						str[j] = (char) strtol (tmp, &eptr, 16);
						if (tmp[0] != '\0' && *eptr != '\0')
							fprintf (stderr, "WARNING: Cannot convert hexadecimal number\n");
						i += 4, j++;
					} else {
						fprintf (stderr, "ERROR: Premature end of string\n");
						i++;
					}
					break;
				case '\\':
					/* Turn 2 backslashes into 1 */
					str[j] = c;
					i += 2, j++;
					break;
				default:
					/* Actually this should be an octal number... */
					fprintf (stderr, "WARNING: Unsupported escape sequence \"\\%c\", leaving as is\n", str[i + 1]);
					fprintf (stderr, "--> %s\n", str);
					str[j] = c;
					i++, j++;
					break;
			}
		} else {
			str[j] = c;
			i++, j++;
		}
	}

	/* Terminate (so that we have chances the output string remains C-style, but it depends on strin string contents) */
	str[j] = '\0';
	*len = j;

	return (str);
}




/* Line 268 of yacc.c  */
#line 606 "../../assembler/nvm_gramm.tab.c"

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
     T_DB = 258,
     T_DW = 259,
     T_DD = 260,
     T_EQU = 261,
     SEGMENT = 262,
     ENDS = 263,
     S_PORT = 264,
     S_DATA = 265,
     S_METADATA = 266,
     T_HOST = 267,
     T_PORT = 268,
     T_ADDR = 269,
     NUMBER = 270,
     STRING = 271,
     IDENTIFIER = 272,
     LABEL = 273,
     PORT_TYPE = 274,
     COPRO_DECL = 275,
     DATAMEMSIZE = 276,
     NETPENAME = 277,
     INFOPARTSIZE = 278,
     LOCALS = 279,
     STACKSIZE = 280,
     BYTEORDER = 281,
     DEFAULTCASE = 282,
     T_NO_ARG_INST = 283,
     T_1BYTE_ARG_INST = 284,
     T_1WORD_ARG_INST = 285,
     T_1INT_ARG_INST = 286,
     T_2INT_ARG_INST = 287,
     T_1LABEL_INST = 288,
     T_1_SHORT_LABEL_INST = 289,
     T_1LABEL_1BYTE_ARG_INST = 290,
     T_1LABEL_1WORD_ARG_INST = 291,
     T_1LABEL_1INT_ARG_INST = 292,
     T_1_PUSH_PORT_ARG_INST = 293,
     T_1_PULL_PORT_ARG_INST = 294,
     T_JMP_TBL_LKUP_INST = 295,
     T_COPRO_INIT_INST = 296,
     T_2_COPRO_IO_ARG_INST = 297
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 587 "../../assembler/nvm_gramm.y"

int	number;
char	id[1024];



/* Line 293 of yacc.c  */
#line 691 "../../assembler/nvm_gramm.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 703 "../../assembler/nvm_gramm.tab.c"

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
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYLAST   223

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNRULES -- Number of states.  */
#define YYNSTATES  180

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      49,    50,    45,    43,    47,    44,     2,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    16,    17,    23,    24,
      30,    31,    39,    40,    46,    48,    50,    52,    54,    56,
      59,    62,    65,    68,    70,    73,    75,    78,    80,    82,
      84,    87,    90,    93,    95,    96,    97,   100,   102,   104,
     106,   108,   111,   112,   114,   116,   119,   122,   124,   126,
     130,   132,   135,   139,   141,   144,   146,   148,   150,   152,
     154,   156,   158,   160,   162,   164,   166,   168,   170,   172,
     175,   180,   185,   188,   190,   193,   196,   199,   204,   207,
     210,   215,   220,   225,   230,   232,   235,   239,   243,   247,
     251,   255,   259,   262,   264,   266,   268,   270,   274,   278,
     282,   286,   290,   293,   295,   297,   299,   301,   304,   306,
     308
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      52,     0,    -1,    64,    -1,    81,    64,    -1,    -1,     7,
      17,    54,    65,    70,     8,    -1,    -1,     7,    17,    55,
      70,     8,    -1,    -1,     7,     9,    56,    74,     8,    -1,
      -1,     7,    10,    26,    18,    57,   102,     8,    -1,    -1,
       7,    11,    58,    60,     8,    -1,    63,    -1,    67,    -1,
      61,    -1,    62,    -1,    59,    -1,    60,    59,    -1,    22,
      18,    -1,    23,    15,    -1,    20,    18,    -1,    53,    -1,
      64,    53,    -1,    66,    -1,    65,    66,    -1,    67,    -1,
      68,    -1,    69,    -1,    21,    15,    -1,    24,    15,    -1,
      25,    15,    -1,    73,    -1,    -1,    -1,    72,    82,    -1,
      79,    -1,    80,    -1,     1,    -1,    71,    -1,    73,    71,
      -1,    -1,    75,    -1,    76,    -1,    76,    75,    -1,    19,
      77,    -1,     1,    -1,    78,    -1,    77,    47,    78,    -1,
      18,    -1,    18,    48,    -1,    18,     6,   104,    -1,    80,
      -1,    81,    80,    -1,    86,    -1,    87,    -1,    88,    -1,
      89,    -1,    90,    -1,    91,    -1,    92,    -1,    93,    -1,
      94,    -1,    95,    -1,    83,    -1,    85,    -1,    84,    -1,
      96,    -1,    38,    18,    -1,    42,    18,    47,   104,    -1,
      41,    18,    47,    18,    -1,    39,    18,    -1,    28,    -1,
      29,   104,    -1,    30,   104,    -1,    31,   104,    -1,    32,
     104,    47,   104,    -1,    33,    18,    -1,    34,    18,    -1,
      35,   104,    47,    18,    -1,    36,   104,    47,    18,    -1,
      37,   104,    47,    18,    -1,    40,    15,    48,    97,    -1,
      98,    -1,    97,    98,    -1,    15,    48,    18,    -1,    27,
      48,    18,    -1,    18,     3,   104,    -1,    18,     3,    16,
      -1,    18,     4,   104,    -1,    18,     5,   104,    -1,   102,
     103,    -1,   103,    -1,    99,    -1,   100,    -1,   101,    -1,
     104,    43,   104,    -1,   104,    44,   104,    -1,   104,    45,
     104,    -1,   104,    46,   104,    -1,    49,   104,    50,    -1,
      44,   104,    -1,    15,    -1,    18,    -1,   105,    -1,   107,
      -1,    12,   106,    -1,    14,    -1,    18,    -1,    13,    18,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   637,   637,   638,   641,   641,   680,   680,   718,   718,
     735,   735,   770,   770,   824,   825,   826,   827,   830,   831,
     834,   848,   865,   883,   884,   887,   888,   891,   892,   893,
     896,   913,   928,   943,   944,   948,   948,   959,   960,   961,
     964,   965,   969,   970,   974,   975,   979,   980,   984,   985,
     989,  1001,  1011,  1017,  1018,  1021,  1022,  1023,  1024,  1025,
    1026,  1027,  1028,  1029,  1030,  1031,  1032,  1033,  1034,  1039,
    1062,  1081,  1110,  1133,  1138,  1144,  1150,  1156,  1163,  1186,
    1215,  1235,  1255,  1274,  1314,  1315,  1318,  1340,  1367,  1378,
    1398,  1421,  1444,  1445,  1448,  1449,  1450,  1453,  1454,  1455,
    1456,  1457,  1458,  1459,  1460,  1476,  1477,  1481,  1504,  1505,
    1508
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_DB", "T_DW", "T_DD", "T_EQU",
  "SEGMENT", "ENDS", "S_PORT", "S_DATA", "S_METADATA", "T_HOST", "T_PORT",
  "T_ADDR", "NUMBER", "STRING", "IDENTIFIER", "LABEL", "PORT_TYPE",
  "COPRO_DECL", "DATAMEMSIZE", "NETPENAME", "INFOPARTSIZE", "LOCALS",
  "STACKSIZE", "BYTEORDER", "DEFAULTCASE", "T_NO_ARG_INST",
  "T_1BYTE_ARG_INST", "T_1WORD_ARG_INST", "T_1INT_ARG_INST",
  "T_2INT_ARG_INST", "T_1LABEL_INST", "T_1_SHORT_LABEL_INST",
  "T_1LABEL_1BYTE_ARG_INST", "T_1LABEL_1WORD_ARG_INST",
  "T_1LABEL_1INT_ARG_INST", "T_1_PUSH_PORT_ARG_INST",
  "T_1_PULL_PORT_ARG_INST", "T_JMP_TBL_LKUP_INST", "T_COPRO_INIT_INST",
  "T_2_COPRO_IO_ARG_INST", "'+'", "'-'", "'*'", "'/'", "','", "':'", "'('",
  "')'", "$accept", "source", "segment", "$@1", "$@2", "$@3", "$@4", "$@5",
  "metadata_directive", "metadata_directives", "netpename_directive",
  "infosize_directive", "copro_directive", "segments", "directives",
  "directive", "datamem_directive", "local_directive",
  "stacksize_directive", "code", "line", "$@6", "lines", "port_table",
  "port_decls", "port_decl", "port_list", "port_id", "label",
  "equivalence", "equivalences", "instr", "push_port_arg_inst",
  "copro_io_arg_inst", "pull_port_arg_inst", "no_arg_inst",
  "byte_arg_inst", "word_arg_inst", "int_arg_inst", "double_int_arg_inst",
  "jump_inst", "short_jump_inst", "byte_jump_inst", "word_jump_inst",
  "int_jump_inst", "jmp_tbl_lkup_inst", "pairs", "pair", "db", "dw", "dd",
  "data_decls", "data_decl", "expr", "ip_address", "literaladdr",
  "ip_port", 0
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
     295,   296,   297,    43,    45,    42,    47,    44,    58,    40,
      41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    52,    54,    53,    55,    53,    56,    53,
      57,    53,    58,    53,    59,    59,    59,    59,    60,    60,
      61,    62,    63,    64,    64,    65,    65,    66,    66,    66,
      67,    68,    69,    70,    70,    72,    71,    71,    71,    71,
      73,    73,    74,    74,    75,    75,    76,    76,    77,    77,
      78,    79,    80,    81,    81,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    83,
      84,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    97,    98,    98,    99,    99,
     100,   101,   102,   102,   103,   103,   103,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   105,   106,   106,
     107
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     6,     0,     5,     0,     5,
       0,     7,     0,     5,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     1,     2,     1,     2,     1,     1,     1,
       2,     2,     2,     1,     0,     0,     2,     1,     1,     1,
       1,     2,     0,     1,     1,     2,     2,     1,     1,     3,
       1,     2,     3,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       4,     4,     2,     1,     2,     2,     2,     4,     2,     2,
       4,     4,     4,     4,     1,     2,     3,     3,     3,     3,
       3,     3,     2,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     2,     1,     1,     1,     1,     2,     1,     1,
       2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    23,     2,    53,     0,     8,     0,
      12,     6,     0,     1,    24,     3,    54,     0,     0,     0,
       0,     0,     0,     0,   103,   104,     0,     0,    52,   105,
     106,    47,     0,     0,    43,     0,    10,     0,     0,     0,
       0,    18,     0,    16,    17,    14,    15,     0,     0,     0,
      25,    27,    28,    29,    39,     0,     0,    40,     0,     0,
      37,    38,   108,   109,   107,   110,   102,     0,     0,     0,
       0,     0,    50,    46,    48,     9,    45,     0,    22,    30,
      20,    21,    13,    19,    31,    32,    26,     0,    51,     7,
      73,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    36,    65,    67,    66,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    68,
      41,   101,    97,    98,    99,   100,     0,     0,    94,    95,
      96,     0,    93,     5,    74,    75,    76,     0,    78,    79,
       0,     0,     0,    69,    72,     0,     0,     0,    49,     0,
       0,     0,    11,    92,     0,     0,     0,     0,     0,     0,
       0,    89,    88,    90,    91,    77,    80,    81,    82,     0,
       0,    83,    84,    71,    70,     0,     0,    85,    86,    87
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    20,    21,    17,    77,    19,    41,    42,
      43,    44,    45,     5,    49,    50,    46,    52,    53,    56,
      57,    58,    59,    33,    34,    35,    73,    74,    60,    61,
       7,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   171,   172,   128,   129,
     130,   131,   132,    28,    29,    64,    30
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -27
static const yytype_int16 yypact[] =
{
       2,    16,     7,    29,   -27,    30,   -27,     2,   -27,    14,
     -27,    54,     3,   -27,   -27,    30,   -27,     9,    45,    28,
     131,   108,    90,    58,   -27,   -27,     3,     3,   116,   -27,
     -27,   -27,    64,    27,   -27,    11,   -27,    65,    84,    87,
      91,   -27,    33,   -27,   -27,   -27,   -27,   100,   107,    56,
     -27,   -27,   -27,   -27,   -27,    -2,   119,   -27,   165,   150,
     -27,   -27,   -27,   -27,   -27,   -27,    24,    57,     3,     3,
       3,     3,   -27,    88,   -27,   -27,   -27,   135,   -27,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,   146,   -27,   -27,
     -27,     3,     3,     3,     3,   139,   148,     3,     3,     3,
     149,   151,   155,   153,   154,   -27,   -27,   -27,   -27,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,
     -27,   -27,    24,    24,   -27,   -27,    64,   160,   -27,   -27,
     -27,     6,   -27,   -27,   116,   116,   116,    15,   -27,   -27,
      67,    74,    86,   -27,   -27,   125,   127,   128,   -27,   -10,
       3,     3,   -27,   -27,     3,   158,   159,   190,    -4,   191,
       3,   -27,   116,   116,   116,   116,   -27,   -27,   -27,   162,
     163,    -4,   -27,   -27,   116,   194,   195,   -27,   -27,   -27
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -27,   -27,    17,   -27,   -27,   -27,   -27,   -27,   172,   -27,
     -27,   -27,   -27,   208,   -27,   167,   -13,   -27,   -27,   168,
     161,   -27,   -27,   -27,   183,   -27,   -27,    93,   -27,    31,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,    50,   -27,   -27,
     -27,   -27,    92,   -26,   -27,   -27,   -27
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -45
static const yytype_int16 yytable[] =
{
      66,    67,    22,    23,    12,    24,   161,    51,    25,     1,
      31,   169,    31,    12,   152,    22,    23,   -42,    24,   -44,
       2,    25,    14,   170,   127,     8,     9,    10,    32,    13,
      32,     6,    14,    11,    26,    75,    51,     1,    16,    27,
      18,    82,   122,   123,   124,   125,    88,    26,    37,    38,
      39,    40,    27,    37,    38,    39,    40,    54,    68,    69,
      70,    71,   154,    36,   -34,   134,   135,   136,   137,    70,
      71,   140,   141,   142,    55,    -4,    65,    38,    -4,    -4,
      47,    48,    72,    78,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,    79,
      68,    69,    70,    71,    62,    80,    81,   121,    63,    54,
      68,    69,    70,    71,   155,    84,   -34,    68,    69,    70,
      71,   156,    85,   162,   163,   164,    55,    89,   165,    68,
      69,    70,    71,   157,   174,   126,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,    54,    38,   127,   133,    47,    48,   138,   -33,    68,
      69,    70,    71,   149,   150,   151,   139,   143,    55,   144,
     145,   146,   147,   158,   159,   160,   166,   167,   -35,   -35,
     -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   168,   173,
     175,   176,   178,   179,    83,    15,    86,    87,    76,   148,
     120,   177,     0,   153
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-27))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      26,    27,    12,    13,     6,    15,    16,    20,    18,     7,
       1,    15,     1,     6,     8,    12,    13,     8,    15,     8,
      18,    18,     5,    27,    18,     9,    10,    11,    19,     0,
      19,     0,    15,    17,    44,     8,    49,     7,     7,    49,
      26,     8,    68,    69,    70,    71,    48,    44,    20,    21,
      22,    23,    49,    20,    21,    22,    23,     1,    43,    44,
      45,    46,    47,    18,     8,    91,    92,    93,    94,    45,
      46,    97,    98,    99,    18,    21,    18,    21,    24,    25,
      24,    25,    18,    18,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    15,
      43,    44,    45,    46,    14,    18,    15,    50,    18,     1,
      43,    44,    45,    46,    47,    15,     8,    43,    44,    45,
      46,    47,    15,   149,   150,   151,    18,     8,   154,    43,
      44,    45,    46,    47,   160,    47,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,     1,    21,    18,     8,    24,    25,    18,     8,    43,
      44,    45,    46,     3,     4,     5,    18,    18,    18,    18,
      15,    18,    18,    48,    47,    47,    18,    18,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    18,    18,
      48,    48,    18,    18,    42,     7,    49,    49,    35,   126,
      59,   171,    -1,   131
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    18,    52,    53,    64,    80,    81,     9,    10,
      11,    17,     6,     0,    53,    64,    80,    56,    26,    58,
      54,    55,    12,    13,    15,    18,    44,    49,   104,   105,
     107,     1,    19,    74,    75,    76,    18,    20,    21,    22,
      23,    59,    60,    61,    62,    63,    67,    24,    25,    65,
      66,    67,    68,    69,     1,    18,    70,    71,    72,    73,
      79,    80,    14,    18,   106,    18,   104,   104,    43,    44,
      45,    46,    18,    77,    78,     8,    75,    57,    18,    15,
      18,    15,     8,    59,    15,    15,    66,    70,    48,     8,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      71,    50,   104,   104,   104,   104,    47,    18,    99,   100,
     101,   102,   103,     8,   104,   104,   104,   104,    18,    18,
     104,   104,   104,    18,    18,    15,    18,    18,    78,     3,
       4,     5,     8,   103,    47,    47,    47,    47,    48,    47,
      47,    16,   104,   104,   104,   104,    18,    18,    18,    15,
      27,    97,    98,    18,   104,    48,    48,    98,    18,    18
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:

/* Line 1806 of yacc.c  */
#line 641 "../../assembler/nvm_gramm.y"
    {
				Output_1("segment %s\n", (yyvsp[(2) - (2)].id));
				if(pass == CALCULATE_REFERENCES){
					emitm = emit_lenght;
					cur_seg = insert_seg((yyvsp[(2) - (2)].id), 0);
					cur_seg->max_stack_size = -1;
					cur_seg->locals_num	= -1;
					if (strcmp((yyvsp[(2) - (2)].id), ".pull") == 0)
						cur_seg->flags = BC_CODE_SCN|BC_PULL_SCN;
					if (strcmp((yyvsp[(2) - (2)].id), ".push") == 0)
						cur_seg->flags = BC_CODE_SCN|BC_PUSH_SCN;
					if (strcmp((yyvsp[(2) - (2)].id), ".init") == 0)
						cur_seg->flags = BC_CODE_SCN|BC_INIT_SCN;
				} else {
					emitm = emit_code;
					cur_seg = search_seg((yyvsp[(2) - (2)].id));
					if(allocate_istream(cur_seg, cur_seg->cur_ip) == 0){
						nvmparser_error("failed to allocate segment memory");
					}

					if (cur_seg->max_stack_size == -1)
						cur_seg->max_stack_size = 0;

					if (cur_seg->locals_num == -1)
						cur_seg->locals_num = 0;
					
					sprintf(tmp_char_buf, "%s_ilm", (yyvsp[(2) - (2)].id));
					tmp_char_buf[8] = '\0';
					ip_to_lines_seg = insert_seg(tmp_char_buf, (cur_seg->flags & ~BC_CODE_SCN) | BC_INSN_LINES_SCN);
					
					if(allocate_istream(ip_to_lines_seg, cur_seg->num_instr*8) == 0)
						nvmparser_error("failed to allocate segment memory");
				}

				cur_seg->cur_ip = 0;
				cur_seg->num_instr = 0;
				emitm(cur_seg, cur_seg->max_stack_size, 4);
				emitm(cur_seg, cur_seg->locals_num, 4);
			}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 680 "../../assembler/nvm_gramm.y"
    {
				Output_1("segment %s\n", (yyvsp[(2) - (2)].id));
				if(pass == CALCULATE_REFERENCES){
					emitm = emit_lenght;
					cur_seg = insert_seg((yyvsp[(2) - (2)].id), 0);
					cur_seg->max_stack_size = -1;
					cur_seg->locals_num	= -1;
					if (strcmp((yyvsp[(2) - (2)].id), ".pull") == 0)
						cur_seg->flags = BC_CODE_SCN|BC_PULL_SCN;
					if (strcmp((yyvsp[(2) - (2)].id), ".push") == 0)
						cur_seg->flags = BC_CODE_SCN|BC_PUSH_SCN;
					if (strcmp((yyvsp[(2) - (2)].id), ".init") == 0)
						cur_seg->flags = BC_CODE_SCN|BC_INIT_SCN;
				} else {
					emitm = emit_code;
					cur_seg = search_seg((yyvsp[(2) - (2)].id));
					if(allocate_istream(cur_seg, cur_seg->cur_ip) == 0){
						nvmparser_error("failed to allocate segment memory");
					}

					if (cur_seg->max_stack_size == -1)
						cur_seg->max_stack_size = 0;

					if (cur_seg->locals_num == -1)
						cur_seg->locals_num = 0;
					
					sprintf(tmp_char_buf, "%s_ilm", (yyvsp[(2) - (2)].id));
					tmp_char_buf[8] = '\0';
					ip_to_lines_seg = insert_seg(tmp_char_buf, (cur_seg->flags & ~BC_CODE_SCN) | BC_INSN_LINES_SCN);
					
					if(allocate_istream(ip_to_lines_seg, cur_seg->num_instr*8) == 0)
						nvmparser_error("failed to allocate segment memory");
				}

				cur_seg->cur_ip = 0;
				emitm(cur_seg, cur_seg->max_stack_size, 4);
				emitm(cur_seg, cur_seg->locals_num, 4);
			}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 718 "../../assembler/nvm_gramm.y"
    {
				Output_2("%s segment at line %d\n", (yyvsp[(2) - (2)].id), eline);

				if(pass == CALCULATE_REFERENCES){
					emitm = emit_lenght;
					cur_seg = insert_seg((yyvsp[(2) - (2)].id), BC_PORT_SCN);
				} else {
					emitm = emit_code;
					cur_seg = search_seg((yyvsp[(2) - (2)].id));
					if(allocate_istream(cur_seg, cur_seg->cur_ip) == 0) {
						nvmparser_error("failed to allocate segment memory");
					}
				}

				cur_seg->cur_ip = 0;
				emitm(cur_seg, n_ports, 4);
			}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 735 "../../assembler/nvm_gramm.y"
    {
				Output_2("%s segment at line %d\n", (yyvsp[(2) - (4)].id), eline);

				if (pass == CALCULATE_REFERENCES) {
					emitm = emit_lenght;
					cur_seg = insert_seg((yyvsp[(2) - (4)].id), BC_INITIALIZED_DATA_SCN);
					cur_seg->max_stack_size = 0;
					cur_seg->locals_num	= 0;

					if (strcmp ((yyvsp[(4) - (4)].id), "big_endian") == 0 || strcmp ((yyvsp[(4) - (4)].id), "network") == 0) {
						Output("Requested byte order is BIG endian\n");
						cur_seg -> endianness = SEGMENT_BIG_ENDIAN;
					} else if (strcmp ((yyvsp[(4) - (4)].id), "little_endian") == 0) {
						Output("Requested byte order is LITTLE endian\n");
						cur_seg -> endianness = SEGMENT_LITTLE_ENDIAN;
					} else {
						Output("Requested byte order is UNDEFINED\n");
						cur_seg -> endianness = SEGMENT_UNDEFINED_ENDIANNESS;
					}

					if (htval)
						nvmparser_error("dataval hash table already allocated, this should not happen");
					else
						htval = hash_table_new (0);
				} else {
					emitm = emit_code;
					cur_seg = search_seg((yyvsp[(2) - (4)].id));
					if(allocate_istream(cur_seg, cur_seg->cur_ip) == 0){
						nvmparser_error("failed to allocate segment memory");
					}
				}

				cur_seg -> cur_ip = 0;
				emitm(cur_seg, cur_seg -> endianness, 4);
			}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 770 "../../assembler/nvm_gramm.y"
    {
				Output_2("%s segment at line %d\n", (yyvsp[(2) - (2)].id), eline);

				if (pass == CALCULATE_REFERENCES){
					emitm = emit_lenght;
					cur_seg = insert_seg((yyvsp[(2) - (2)].id), BC_METADATA_SCN);
					cur_seg -> cur_ip = 0;
					cur_seg->max_stack_size = 0;
					cur_seg->locals_num	= 0;
					pe_metadata.datamem_size = -1;
					pe_metadata.infopart_size = -1;
					pe_metadata.copros_no = 0;
					pe_metadata.netpename[0] = '\0';
				} else {
					emitm = emit_code;
					cur_seg = search_seg((yyvsp[(2) - (2)].id));

					if (pe_metadata.datamem_size == -1)
						pe_metadata.datamem_size = 0;

					if (pe_metadata.infopart_size == -1)
						pe_metadata.infopart_size = 0;

					/* This segment is fully emitted here */
					if (allocate_istream(cur_seg, 4 + strlen (pe_metadata.netpename) + 4 + 4 + 4 + cur_seg -> cur_ip) == 0){
						nvmparser_error("failed to allocate segment memory");
					}
					cur_seg -> cur_ip = 0;

					/* PE name length and actual name */
					emitm (cur_seg, (uint32_t) strlen (pe_metadata.netpename), 4);
					for (id = 0; id < strlen (pe_metadata.netpename); id++)
						emitm(cur_seg, pe_metadata.netpename[id], 1);

					/* Requested data memory size */
					emitm(cur_seg, (uint32_t) pe_metadata.datamem_size, 4);

					/* Requested info partition size */
					emitm(cur_seg, (uint32_t) pe_metadata.infopart_size, 4);

					/* Number of used coprocessors */
					emitm(cur_seg, (uint32_t) pe_metadata.copros_no, 4);

					/* For every coprocessor, name length and actual name */
					for (ij = 0; ij < pe_metadata.copros_no; ij++) {
						emitm (cur_seg, (uint32_t) strlen (pe_metadata.copros[ij]), 4);
						for (id = 0; id < strlen (pe_metadata.copros[ij]); id++)
							emitm(cur_seg, pe_metadata.copros[ij][id], 1);
					}
				}
			}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 834 "../../assembler/nvm_gramm.y"
    {
				if (cur_seg->flags != BC_METADATA_SCN) {
					nvmparser_error("The .infopart_size directive can only be used in the .metadata segment");
				} else {
					if (pass == CALCULATE_REFERENCES) {
						if (pe_metadata.netpename[0] == '\0')
							strncpy (pe_metadata.netpename, (yyvsp[(2) - (2)].id), MAX_NETPE_NAME);
						else
							nvmparser_error("NetPE name redefined");
					}
				}
			}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 848 "../../assembler/nvm_gramm.y"
    {
				if (cur_seg->flags != BC_METADATA_SCN) {
					nvmparser_error("The .infopart_size directive can only be used in the .metadata segment");
				} else {
					if (pass == CALCULATE_REFERENCES) {
						if (pe_metadata.infopart_size != -1)
							nvmparser_error("redeclaration of infopart_size");
						else
							if ((yyvsp[(2) - (2)].number) < 0)
								nvmparser_error("cannot declare a negative infopart_size");
						else
							pe_metadata.infopart_size = (yyvsp[(2) - (2)].number);
					}
				}
			}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 865 "../../assembler/nvm_gramm.y"
    {
				(yyval.number)=(yyvsp[(0) - (2)].number);

				if (pass == CALCULATE_REFERENCES){
					Output_1 ("Coprocessor: name=%s\n", (yyvsp[(2) - (2)].id));
					id = add_copro ((yyvsp[(2) - (2)].id), -1);
					Output_1 ("Assigned ID: %d\n", id);

					strncpy (pe_metadata.copros[pe_metadata.copros_no], (yyvsp[(2) - (2)].id), MAX_COPRO_NAME);
					pe_metadata.copros_no++;

					emitm(cur_seg, (uint32_t) strlen ((yyvsp[(2) - (2)].id)), 4);
					for (id = 0; id < strlen((yyvsp[(2) - (2)].id)); id++)
						emitm(cur_seg, (yyvsp[(2) - (2)].id)[id], 1);
				}
			}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 896 "../../assembler/nvm_gramm.y"
    {
				if (cur_seg->flags != BC_METADATA_SCN) {
					nvmparser_error("The .datamem_size directive can only be used in the .metadata segment");
				} else {
					if (pass == CALCULATE_REFERENCES) {
						if (pe_metadata.datamem_size != -1)
							nvmparser_error("redeclaration of datamem_size");
						else
							if ((yyvsp[(2) - (2)].number) < 0)
								nvmparser_error("cannot declare a negative datamem_size");
						else
							pe_metadata.datamem_size = (yyvsp[(2) - (2)].number);
					}
				}
			}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 914 "../../assembler/nvm_gramm.y"
    {
							if(pass == CALCULATE_REFERENCES)
							{
								if (cur_seg->locals_num != -1)
									nvmparser_error("redeclaration of locals");
								else
								if ((yyvsp[(2) - (2)].number) < 0)
									nvmparser_error("cannot declare a negative number of locals");
								else
									cur_seg->locals_num = (yyvsp[(2) - (2)].number);
							}
						}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 929 "../../assembler/nvm_gramm.y"
    {
							if(pass == CALCULATE_REFERENCES)
							{
								if (cur_seg->max_stack_size != -1)
									nvmparser_error("redeclaration of max stack size");
								else
								if ((yyvsp[(2) - (2)].number) < 0)
									nvmparser_error("cannot declare a negative number of max stack size");
								else
									cur_seg->max_stack_size = (yyvsp[(2) - (2)].number);
							}
						}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 944 "../../assembler/nvm_gramm.y"
    {warn("Empty code segment\n");}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 948 "../../assembler/nvm_gramm.y"
    {
				if(pass != CALCULATE_REFERENCES)
				{
					//first 8 bytes of the segment are reserved for maxstacksize and locals
					emit_code (ip_to_lines_seg, cur_seg->cur_ip - 8, 4);
					emit_code (ip_to_lines_seg, eline, 4);
				}
				cur_seg->num_instr++;
			}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 969 "../../assembler/nvm_gramm.y"
    {warn("empty port table\n");}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 979 "../../assembler/nvm_gramm.y"
    {(yyval.number)=(yyvsp[(1) - (2)].number);}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 980 "../../assembler/nvm_gramm.y"
    {}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 984 "../../assembler/nvm_gramm.y"
    {(yyval.number)=(yyvsp[(0) - (1)].number);}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 989 "../../assembler/nvm_gramm.y"
    {
				(yyval.number)=(yyvsp[(0) - (1)].number);

				if(pass == CALCULATE_REFERENCES){
					Output_2("port: name=%s, type=%d\n", (yyvsp[(1) - (1)].id), (yyvsp[(0) - (1)].number));
					add_port((yyvsp[(1) - (1)].id), (yyvsp[(0) - (1)].number));
				}

				emitm(cur_seg, (yyvsp[(0) - (1)].number), 4);
			}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 1001 "../../assembler/nvm_gramm.y"
    {
								if(pass == CALCULATE_REFERENCES){
									pref lr;
									lr = insert_ref((yyvsp[(1) - (2)].id));
									lr->target = cur_seg->cur_ip;
									Output_2("label %s, target=%d\n", (yyvsp[(1) - (2)].id), lr->target);
								}
							}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 1011 "../../assembler/nvm_gramm.y"
    {
							Output_2("Equivalence %s=%d\n", (yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].number));
							if(pass == CALCULATE_REFERENCES) insert_var((yyvsp[(1) - (3)].id),(yyvsp[(3) - (3)].number));
							}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 1039 "../../assembler/nvm_gramm.y"
    {
				if (pass == CALCULATE_REFERENCES) {
					emitm(cur_seg, (char)(yyvsp[(1) - (2)].number), 1);
					emitm(cur_seg, 0, 4);
				} else {
					pport dport;

					Output_1("push port instruction, port name=%s\n", (yyvsp[(2) - (2)].id));
					dport = search_port((yyvsp[(2) - (2)].id));
					if (dport == NULL) {
						nvmparser_error("referenced port not found");
						break;
					}
					if (!(nvmFLAG_ISSET(dport->type, nvmPORT_COLLECTOR) && \
								nvmFLAG_ISSET(dport->type, nvmCONNECTION_PUSH)))
						nvmparser_error("instruction can be issued only on an output push port");
					emitm(cur_seg, (char) (yyvsp[(1) - (2)].number), 1);
					emitm(cur_seg, dport->number, 4);
					//Output_1 ("emitted port %d\n", dport -> number);
				}
			}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 1062 "../../assembler/nvm_gramm.y"
    {
				if (pass == CALCULATE_REFERENCES) {
					emitm(cur_seg, (char) (yyvsp[(1) - (4)].number), 1);	// Opcode
					emitm(cur_seg, 0, 4);		// Coprocessor ID
					emitm(cur_seg, 0, 4);		// Coprocessor register or operation ID
				} else {
					pcopro dcopro;
					Output_2("Coprocessor I/O instruction, copro name=%s, register/op=%d\n", (yyvsp[(2) - (4)].id), (yyvsp[(4) - (4)].number));
					dcopro = search_copro ((yyvsp[(2) - (4)].id));
					if (dcopro == NULL) {
						nvmparser_error("referenced coprocessor not found");
						break;
					}
					emitm(cur_seg, (char) (yyvsp[(1) - (4)].number), 1);
					emitm(cur_seg, dcopro->number, 4);
					emitm(cur_seg, (uint32_t) (yyvsp[(4) - (4)].number), 4);
					//Output_1 ("emitted coprocessor %d\n", dcopro -> number);
				}
			}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 1081 "../../assembler/nvm_gramm.y"
    {
				if (pass == CALCULATE_REFERENCES) {
					emitm(cur_seg, (char) (yyvsp[(1) - (4)].number), 1);   // Opcode
					emitm(cur_seg, 0, 4);           // Coprocessor ID
					emitm(cur_seg, 0, 4);           // Offset in inited_mem
				} else {
					pcopro dcopro;
					uint32_t target;

					if (!search_dataval ((yyvsp[(4) - (4)].id), &target)) {
						nvmparser_error ("Undefined dval");
						break;
					}

					Output_2("Coprocessor init instruction, copro name=%s, offset=%d\n", (yyvsp[(2) - (4)].id), target);
					dcopro = search_copro ((yyvsp[(2) - (4)].id));
					if (dcopro == NULL) {
						nvmparser_error("referenced coprocessor not found");
						break;
					}
					emitm(cur_seg, (char) (yyvsp[(1) - (4)].number), 1);
					emitm(cur_seg, dcopro->number, 4);
					emitm(cur_seg, (uint32_t) target, 4);
					//Output_1 ("emitted coprocessor %d\n", dcopro -> number);
				}
			}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 1110 "../../assembler/nvm_gramm.y"
    {

											if(pass == CALCULATE_REFERENCES){
												emitm(cur_seg, (char)(yyvsp[(1) - (2)].number), 1);
												emitm(cur_seg, 0, 4);
											}
											else{
												pport dport;

												Output_1("push port intruction, port name=%s\n", (yyvsp[(2) - (2)].id));
												dport = search_port((yyvsp[(2) - (2)].id));
												if(dport==NULL){
													nvmparser_error("referenced port not found");
													break;
												}
												if ( !(nvmFLAG_ISSET(dport->type, nvmPORT_EXPORTER) && nvmFLAG_ISSET(dport->type, nvmCONNECTION_PULL)) ) nvmparser_error("instruction can be issued only on an input pull port");
												emitm(cur_seg, (char)(yyvsp[(1) - (2)].number), 1);
												emitm(cur_seg, dport->number, 4);
											}
										}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 1133 "../../assembler/nvm_gramm.y"
    {
									emitm(cur_seg, (char)(yyvsp[(1) - (1)].number), 1);
								}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 1138 "../../assembler/nvm_gramm.y"
    {
											emitm(cur_seg, (char)(yyvsp[(1) - (2)].number), 1);
											emitm(cur_seg, (char)(yyvsp[(2) - (2)].number), 1);
										}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 1144 "../../assembler/nvm_gramm.y"
    {
											emitm(cur_seg, (char)(yyvsp[(1) - (2)].number), 1);
											emitm(cur_seg, (short)(yyvsp[(2) - (2)].number), 2);
										}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 1150 "../../assembler/nvm_gramm.y"
    {
											emitm(cur_seg, (char)(yyvsp[(1) - (2)].number), 1);
											emitm(cur_seg, (int)(yyvsp[(2) - (2)].number), 4);
										}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 1156 "../../assembler/nvm_gramm.y"
    {
											emitm(cur_seg, (char)(yyvsp[(1) - (4)].number), 1);
											emitm(cur_seg, (int)(yyvsp[(2) - (4)].number), 4);
											emitm(cur_seg, (int)(yyvsp[(4) - (4)].number), 4);
										}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 1163 "../../assembler/nvm_gramm.y"
    {
									if(pass == CALCULATE_REFERENCES){
										emitm(cur_seg, (char)(yyvsp[(1) - (2)].number), 1);
										emitm(cur_seg, 0, 4);
									}
									else{
										pref jr;

										jr = search_ref((yyvsp[(2) - (2)].id));
										if(jr==NULL){
											nvmparser_error("target label not found");
											emitm(cur_seg, (char)(yyvsp[(1) - (2)].number), 1);
											emitm(cur_seg, 0, 4);
										}
										else{
											emitm(cur_seg, (char)(yyvsp[(1) - (2)].number), 1);
											emitm(cur_seg, jr->target-cur_seg->cur_ip-4, 4);
											Output_3("simple jmp, label=%s, target=%d, cur_pos=%d\n", (yyvsp[(2) - (2)].id), jr->target, cur_seg->cur_ip);
										}
									}
								}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 1186 "../../assembler/nvm_gramm.y"
    {
									if(pass == CALCULATE_REFERENCES){
										emitm(cur_seg, (char)(yyvsp[(1) - (2)].number), 1);
										emitm(cur_seg, 0, 1);
									}
									else{
										pref jr;

										jr = search_ref((yyvsp[(2) - (2)].id));
										if(jr==NULL){
											nvmparser_error("target label not found");
											emitm(cur_seg, (char)(yyvsp[(1) - (2)].number), 1);
											emitm(cur_seg, 0, 1);
										}
										else if(jr->target-cur_seg->cur_ip - 4 > 255){
											nvmparser_error("jump out of range");
											emitm(cur_seg, (char)(yyvsp[(1) - (2)].number), 1);
											emitm(cur_seg, 0, 1);
										}
										else{
											emitm(cur_seg, (char)(yyvsp[(1) - (2)].number), 1);
											emitm(cur_seg, jr->target-cur_seg->cur_ip-1, 1);
											Output_3("short jmp, label=%s, target=%d, cur_pos=%d\n", (yyvsp[(2) - (2)].id), jr->target, cur_seg->cur_ip);
										}
									}
								}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 1215 "../../assembler/nvm_gramm.y"
    {
											if(pass == CALCULATE_REFERENCES){
												emitm(cur_seg, (char)(yyvsp[(1) - (4)].number), 1);
												emitm(cur_seg, 0, 4);
												emitm(cur_seg, 0, 1);
											}
											else{
												pref jr;

												jr = search_ref((yyvsp[(4) - (4)].id));
												if(jr==NULL) nvmparser_error("target label not found");
												emitm(cur_seg, (char)(yyvsp[(1) - (4)].number), 1);
												emitm(cur_seg, jr->target-cur_seg->cur_ip-4, 4);
												emitm(cur_seg, *(char*)&((yyvsp[(4) - (4)].id)), 1);
												Output_3("byte jmp, label=%s, target=%d, cur_pos=%d\n", (yyvsp[(4) - (4)].id), jr->target, cur_seg->cur_ip);
											}
										}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 1235 "../../assembler/nvm_gramm.y"
    {
											if(pass == CALCULATE_REFERENCES){
												emitm(cur_seg, (char)(yyvsp[(1) - (4)].number), 1);
												emitm(cur_seg, 0, 4);
												emitm(cur_seg, 0, 2);
											}
											else{
												pref jr;

												jr = search_ref((yyvsp[(4) - (4)].id));
												if(jr==NULL) nvmparser_error("target label not found");
												emitm(cur_seg, (char)(yyvsp[(1) - (4)].number), 1);
												emitm(cur_seg, jr->target-cur_seg->cur_ip-4, 4);
												emitm(cur_seg, *(char*)&((yyvsp[(4) - (4)].id)), 2);
												Output_3("word jmp, label=%s, target=%d, cur_pos=%d\n", (yyvsp[(4) - (4)].id), jr->target, cur_seg->cur_ip);
											}
										}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 1255 "../../assembler/nvm_gramm.y"
    {
											if(pass == CALCULATE_REFERENCES){
												emitm(cur_seg, (char)(yyvsp[(1) - (4)].number), 1);
												emitm(cur_seg, 0, 4);
												emitm(cur_seg, 0, 4);
											}
											else{
												pref jr;

												jr = search_ref((yyvsp[(4) - (4)].id));
												if(jr==NULL) nvmparser_error("target label not found");
												emitm(cur_seg, (char)(yyvsp[(1) - (4)].number), 1);
												emitm(cur_seg, jr->target-cur_seg->cur_ip-4, 4);
												emitm(cur_seg, *(char*)&((yyvsp[(4) - (4)].id)), 4);
												Output_3("int jmp, label=%s, target=%d, cur_pos=%d\n", (yyvsp[(4) - (4)].id), jr->target, cur_seg->cur_ip);
											}
										}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 1274 "../../assembler/nvm_gramm.y"
    {
										if(pass == CALCULATE_REFERENCES){
												emitm(cur_seg, (char)(yyvsp[(1) - (4)].number), 1); /*opcode*/
												sw_current->sw_npairs = (yyvsp[(2) - (4)].number);
												if (sw_current->sw_npairs != sw_current->sw_pair_cnt)
													nvmparser_error("wrong number of cases");
												if (sw_current->sw_npairs > MAX_SW_CASES)
													nvmparser_error("too many cases in switch instruction");
												emitm(cur_seg, 0, 4); /*default target*/
												emitm(cur_seg, 0, 4); /*number of match pairs*/
												emitm(cur_seg, 0, 8 * sw_current->sw_npairs); /*value: label for sw_npairs times*/
												sw_current->sw_next_inst_ip = cur_seg->cur_ip;
												//!\todo OM risistemare questa roba dopo aver verificato memory leaks!!!
												//sw_cases = calloc(sw_npairs, sizeof (case_pair));
												//if (sw_current->sw_cases == NULL)
												//	nvmparser_error("mem allocation failure");
												sw_current->sw_pair_cnt = 0;
												isnewswitch = 1;
											}
											else{
												int i=0;
												emitm(cur_seg, (char)(yyvsp[(1) - (4)].number), 1);
												if (sw_current->defaultcase.target == 0)
													emitm(cur_seg, 0, 4);
												else
													emitm(cur_seg, sw_current->defaultcase.target, 4);
												emitm(cur_seg, sw_current->sw_npairs, 4);
												for (i = 0; i < sw_current->sw_npairs; i++)
												{
													emitm(cur_seg, sw_current->sw_cases[i].key, 4);
													emitm(cur_seg, sw_current->sw_cases[i].target, 4);
												}
												//if (sw_cases)
												//	free (sw_cases);
												sw_current = sw_current->next;
											}
							}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 1318 "../../assembler/nvm_gramm.y"
    {
								if(pass == CALCULATE_REFERENCES)
								{
									if (isnewswitch)
									{
										new_swinfo();
										isnewswitch = 0;
									}
									sw_current->sw_pair_cnt++;
								}
								else
								{
									pref jr;
									sw_current->sw_cases[sw_current->sw_pair_cnt].key = (int)(yyvsp[(1) - (3)].number);
									jr = search_ref((yyvsp[(3) - (3)].id));
									if(jr==NULL)
										nvmparser_error("target label not found");
									sw_current->sw_cases[sw_current->sw_pair_cnt].target = jr->target - sw_current->sw_next_inst_ip;
									sw_current->sw_pair_cnt++;
								}
							}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1340 "../../assembler/nvm_gramm.y"
    {
								if(pass == CALCULATE_REFERENCES)
								{
									if (isnewswitch)
									{
										new_swinfo();
										isnewswitch = 0;
									}
									if (sw_current->sw_default_ok)
										nvmparser_error("only one default case is allowed for a switch instruction");
								/*
									memset(sw_current->sw_default_label, 0, LBL_MAX_SZ);
									strncpy(sw_current->sw_default_label, (char*) $3, LBL_MAX_SZ - 1);
								*/
									sw_current->sw_default_ok = 1;
								}
								else
								{
									pref jr;
									jr = search_ref((yyvsp[(3) - (3)].id));
									if(jr==NULL)
										nvmparser_error("target label not found");
									sw_current->defaultcase.target = jr->target - sw_current->sw_next_inst_ip;
								}
							}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1367 "../../assembler/nvm_gramm.y"
    {
				if (pass == CALCULATE_REFERENCES) {
					Output_2 ("DB at offset %d, label=%s\n", cur_seg->cur_ip, (yyvsp[(1) - (3)].id));

					insert_dataval ((yyvsp[(1) - (3)].id), cur_seg -> cur_ip);

					emitm(cur_seg, (uint8_t) (yyvsp[(3) - (3)].number), 1);
				} else {
					emitm(cur_seg, (uint8_t) (yyvsp[(3) - (3)].number), 1);
				}
			}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 1378 "../../assembler/nvm_gramm.y"
    {
				int i, len;

				len = -1;
				c_string_unescape ((yyvsp[(3) - (3)].id), &len);

				if (pass == CALCULATE_REFERENCES) {
					Output_3 ("DB string (len=%d) at offset %d, label=%s\n", len, cur_seg->cur_ip, (yyvsp[(1) - (3)].id));

					insert_dataval ((yyvsp[(1) - (3)].id), cur_seg -> cur_ip);

					for (i = 0; i < len; i++)
						emitm(cur_seg, (uint8_t) (yyvsp[(3) - (3)].id)[i], 1);
				} else {
					for (i = 0; i < len; i++)
						emitm(cur_seg, (uint8_t) (yyvsp[(3) - (3)].id)[i], 1);
				}
			}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1398 "../../assembler/nvm_gramm.y"
    {
				uint16_t val;

				if (pass == CALCULATE_REFERENCES) {
					Output_3 ("DW at offset %d, value=%hd label=%s\n", cur_seg->cur_ip, (yyvsp[(3) - (3)].number), (yyvsp[(1) - (3)].id));

					insert_dataval ((yyvsp[(1) - (3)].id), cur_seg -> cur_ip);

					val = 0;	// Don't care for now
				} else {
					val = (uint16_t) (yyvsp[(3) - (3)].number);

					/* Adjust endianness */
					if (cur_seg -> endianness == SEGMENT_BIG_ENDIAN)
						val = bo_my2big_16 (val);
					else if (cur_seg -> endianness == SEGMENT_LITTLE_ENDIAN)
						val = bo_my2little_16 (val);
				}

				emitm(cur_seg, val, 2);
			}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1421 "../../assembler/nvm_gramm.y"
    {
				uint32_t val;

				if (pass == CALCULATE_REFERENCES) {
					Output_3 ("DD at offset %d, value=%d label=%s\n", cur_seg->cur_ip, (yyvsp[(3) - (3)].number), (yyvsp[(1) - (3)].id));

					insert_dataval ((yyvsp[(1) - (3)].id), cur_seg -> cur_ip);

					val = 0;	// Don't care for now
				} else {
					val = (uint32_t) (yyvsp[(3) - (3)].number);

					/* Adjust endianness */
					if (cur_seg -> endianness == SEGMENT_BIG_ENDIAN)
						val = bo_my2big_32 (val);
					else if (cur_seg -> endianness == SEGMENT_LITTLE_ENDIAN)
						val = bo_my2little_32 (val);
				}

				emitm(cur_seg, val, 4);
			}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 1453 "../../assembler/nvm_gramm.y"
    {(yyval.number) = (yyvsp[(1) - (3)].number) + (yyvsp[(3) - (3)].number);}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1454 "../../assembler/nvm_gramm.y"
    {(yyval.number) = (yyvsp[(1) - (3)].number) - (yyvsp[(3) - (3)].number);}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 1455 "../../assembler/nvm_gramm.y"
    {(yyval.number) = (yyvsp[(1) - (3)].number) * (yyvsp[(3) - (3)].number);}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1456 "../../assembler/nvm_gramm.y"
    {(yyval.number) = (yyvsp[(1) - (3)].number) / (yyvsp[(3) - (3)].number);}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1457 "../../assembler/nvm_gramm.y"
    {(yyval.number) = (yyvsp[(2) - (3)].number);}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1458 "../../assembler/nvm_gramm.y"
    {(yyval.number) = -(yyvsp[(2) - (2)].number);}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1459 "../../assembler/nvm_gramm.y"
    {(yyval.number) = (yyvsp[(1) - (1)].number);}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1460 "../../assembler/nvm_gramm.y"
    {
					pvar evar;
					evar = search_var((yyvsp[(1) - (1)].id));

					if(evar == NULL){
						char errstr[64];
						strcpy(errstr, "Variable '");
						strcat(errstr, (yyvsp[(1) - (1)].id));
						strcat(errstr, "' not found");
						nvmparser_error(errstr);
						(yyval.number) = 1;
					}
					else{
						(yyval.number) = evar->val;
					}
				}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1476 "../../assembler/nvm_gramm.y"
    {(yyval.number)=(yyvsp[(1) - (1)].number);}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1477 "../../assembler/nvm_gramm.y"
    {(yyval.number)=(yyvsp[(1) - (1)].number);}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1481 "../../assembler/nvm_gramm.y"
    {
#ifdef _MSC_VER
					struct addrinfo *res;
					res = nametoaddrinfo((yyvsp[(2) - (2)].id));
					if(res != NULL)
					{
						(yyval.number) = ntohl((((struct sockaddr_in*)res->ai_addr))->sin_addr.S_un.S_addr);
						Output_2("addr %s - %d\n", (yyvsp[(2) - (2)].id), (yyval.number));
					}
					else
					{
						if(pass == CALCULATE_REFERENCES)
							nvmparser_error("Unable to find host");
						else
							nvmparser_error(NULL);
					}

#else
							nvmparser_error("This version of the NetVM assembler doesn't support ip address resolution");
#endif
					}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1504 "../../assembler/nvm_gramm.y"
    {strcpy((yyval.id),(yyvsp[(1) - (1)].id));}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1505 "../../assembler/nvm_gramm.y"
    {strcpy((yyval.id),(yyvsp[(1) - (1)].id));}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1508 "../../assembler/nvm_gramm.y"
    {
											/*
								#ifndef ARCH_RUNTIME_OCTEON
											struct servent *s;
											if((s = getservbyname($2, NULL)) != NULL)
											{
												//int i=ntohs(s->s_port);
												$$ =  ntohs(s->s_port);
											}
											else
											{
												nvmparser_error("Unable to resolve port");
											}
								#endif
								*/
										}
    break;



/* Line 1806 of yacc.c  */
#line 3173 "../../assembler/nvm_gramm.tab.c"
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
#line 1529 "../../assembler/nvm_gramm.y"


void warn(const char *s)
{
	fprintf (stderr, "NetIL parser WARNING at line %d\n", eline);

	if (warnbuf != NULL)
	{
		if (s != NULL)
			warnbufpos += snprintf(warnbuf + warnbufpos, warnbufsize-warnbufpos, "Line %d - %s\n", eline, s);
		else
			warnbufpos += snprintf(warnbuf + warnbufpos, warnbufsize-warnbufpos, "Line %d - Unknown\n", eline);
	}

	nwarns++;
}

/* [GM] Dato che mi sfugge la logica dietro alla bufferizzazione degli errori, ho modificato questa funzione in modo che
   stampi direttamente il messaggio. */
int nvmparser_error(const char *s)
{
	fprintf (stderr, "NetIL parser ERROR at line %d: %s\n", eline, s);

	if(errbuf != NULL)
	{
		if (s != NULL)
			errbufpos += snprintf(errbuf + errbufpos, errbufsize - errbufpos, "Line %d - %s\n", eline, s);
		else
			errbufpos += snprintf(errbuf + errbufpos, errbufsize - errbufpos, "Line %d - Unknown\n", eline);
		nerrs++;
	}

	return 1;
}

void yy_set_error_buffer(const char *buffer, int buffer_size)
{
	errbuf = (char*) buffer;
	errbufpos = 0;
	errbufsize = buffer_size;
}

void yy_set_warning_buffer(const char *buffer, int buffer_size)
{
	warnbuf = (char*) buffer;
	warnbufpos = 0;
	warnbufsize = buffer_size;
}

pseg yy_assemble(char* program, int debug)
{
	/*!\todo Cleanup code, is there anything more to clean up? [GM]  */
	var_head = NULL;
	ref_head = NULL;
	seg_head = NULL;
	port_head = NULL;
	copro_head = NULL;
	if (htval) {
		hash_table_destroy (htval, free, free);
		htval = NULL;
	}
	n_ports = 0;
	n_copros = 0;
	eline = 1;
	sw_head = NULL;
	sw_current = NULL;
	isnewswitch = 1;

	pass = CALCULATE_REFERENCES;
	netvm_lex_init(program ? program : "");

	nvmparser_debug = debug;
	nvmparser_parse();

	if(nerrs != 0)
	{
		fprintf (stderr, "%d errors detected while calculating references\n", nerrs);
		wsockcleanup();

		return NULL;
	}
	//fprintf (stderr, "First pass done\n");

	eline = 1; // reset the lines counter

	netvm_lex_cleanup();
	pass = EMIT_CODE;
	sw_current = sw_head;
	netvm_lex_init(program ? program : "");
	nvmparser_parse();
	if(nerrs != 0)
	{
		fprintf (stderr, "%d errors detected while emitting code\n", nerrs);
		wsockcleanup();

		return NULL;
	}

	netvm_lex_cleanup();
	wsockcleanup();

	return seg_head;
}

