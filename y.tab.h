/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     ASIGN = 258,
     IF = 259,
     ELSE_IF = 260,
     ELSE = 261,
     REPEAT = 262,
     WHILE = 263,
     UNTIL = 264,
     SET = 265,
     TO_BE = 266,
     AS = 267,
     DO = 268,
     THANK_YOU = 269,
     EXECUTE = 270,
     FUNCTION = 271,
     RECEIVING = 272,
     RETURNING = 273,
     RETURN = 274,
     COMMA = 275,
     SEMICOLON = 276,
     INT = 277,
     STR = 278,
     DOUBLE = 279,
     EQ = 280,
     GT = 281,
     GE = 282,
     LT = 283,
     LE = 284,
     NE = 285,
     NUMBER_LITERAL = 286,
     STRING_LITERAL = 287,
     VAR = 288,
     ADD = 289,
     SUBSTRACT = 290,
     PROD = 291,
     DIV = 292,
     MODULE = 293,
     AND = 294,
     OR = 295,
     NOT = 296,
     OPEN_B = 297,
     CLOSE_B = 298,
     OPEN_P = 299,
     CLOSE_P = 300,
     PRINT = 301,
     START = 302,
     END = 303,
     DEFINE = 304,
     PASSING = 305
   };
#endif
/* Tokens.  */
#define ASIGN 258
#define IF 259
#define ELSE_IF 260
#define ELSE 261
#define REPEAT 262
#define WHILE 263
#define UNTIL 264
#define SET 265
#define TO_BE 266
#define AS 267
#define DO 268
#define THANK_YOU 269
#define EXECUTE 270
#define FUNCTION 271
#define RECEIVING 272
#define RETURNING 273
#define RETURN 274
#define COMMA 275
#define SEMICOLON 276
#define INT 277
#define STR 278
#define DOUBLE 279
#define EQ 280
#define GT 281
#define GE 282
#define LT 283
#define LE 284
#define NE 285
#define NUMBER_LITERAL 286
#define STRING_LITERAL 287
#define VAR 288
#define ADD 289
#define SUBSTRACT 290
#define PROD 291
#define DIV 292
#define MODULE 293
#define AND 294
#define OR 295
#define NOT 296
#define OPEN_B 297
#define CLOSE_B 298
#define OPEN_P 299
#define CLOSE_P 300
#define PRINT 301
#define START 302
#define END 303
#define DEFINE 304
#define PASSING 305




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 18 "kind.y"
{
    char character;
    int integer;
    double decimal;
    char* string;
    char value[256];
}
/* Line 1529 of yacc.c.  */
#line 157 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

