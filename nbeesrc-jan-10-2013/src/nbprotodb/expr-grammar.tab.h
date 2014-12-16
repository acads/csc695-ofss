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
     OPERAND_NUMBER = 258,
     OPERAND_STRING = 259,
     OPERAND_BOOLEAN = 260,
     OPERAND_VARIABLE_NUMBER = 261,
     OPERAND_VARIABLE_STRING = 262,
     OPERAND_VARIABLE_LOOKUPTABLE = 263,
     FUNCTION_HASSTRING = 264,
     FUNCTION_EXTRACTSTRING = 265,
     FUNCTION_DEBUG = 266,
     FUNCTION_BUFFER2INT = 267,
     FUNCTION_INT2BUFFER = 268,
     FUNCTION_ISPRESENT = 269,
     FUNCTION_ISASN1TYPE = 270,
     FUNCTION_CHANGEBYTEORDER = 271,
     FUNCTION_ASCII2INT = 272,
     FUNCTION_CHECKLOOKUPTABLE = 273,
     FUNCTION_UPDATELOOKUPTABLE = 274,
     OPERAND_PROTOFIELD = 275,
     OR = 276,
     AND = 277,
     NEQ = 278,
     EQ = 279,
     LT = 280,
     LE = 281,
     GT = 282,
     GE = 283,
     BWOR = 284,
     BWAND = 285,
     SUB = 286,
     ADD = 287,
     MOD = 288,
     DIV = 289,
     MUL = 290,
     BWNOT = 291,
     NOT = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif




