/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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

/* Line 2068 of yacc.c  */
#line 587 "../../assembler/nvm_gramm.y"

int	number;
char	id[1024];



/* Line 2068 of yacc.c  */
#line 99 "../../assembler/nvm_gramm.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE nvmparser_lval;


