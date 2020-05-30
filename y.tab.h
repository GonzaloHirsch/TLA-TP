/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    ELSE_IF = 259,
    ELSE = 260,
    REPEAT = 261,
    WHILE = 262,
    UNTIL = 263,
    SET = 264,
    TO_BE = 265,
    AS = 266,
    DO = 267,
    THANK_YOU = 268,
    EXECUTE = 269,
    FUNCTION = 270,
    RECEIVING = 271,
    RETURNING = 272,
    RETURN = 273,
    COMMA = 274,
    SEMICOLON = 275,
    INT = 276,
    STR = 277,
    DOUBLE = 278,
    EQ = 279,
    GT = 280,
    GE = 281,
    LT = 282,
    LE = 283,
    NE = 284,
    NUMBER_LITERAL = 285,
    STRING_LITERAL = 286,
    VAR = 287,
    ADD = 288,
    SUBSTRACT = 289,
    PROD = 290,
    DIV = 291,
    MODULE = 292,
    AND = 293,
    OR = 294,
    NOT = 295,
    OPEN_B = 296,
    CLOSE_B = 297,
    OPEN_P = 298,
    CLOSE_P = 299,
    PRINT = 300,
    START = 301,
    END = 302,
    DEFINE = 303,
    PASSING = 304
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE_IF 259
#define ELSE 260
#define REPEAT 261
#define WHILE 262
#define UNTIL 263
#define SET 264
#define TO_BE 265
#define AS 266
#define DO 267
#define THANK_YOU 268
#define EXECUTE 269
#define FUNCTION 270
#define RECEIVING 271
#define RETURNING 272
#define RETURN 273
#define COMMA 274
#define SEMICOLON 275
#define INT 276
#define STR 277
#define DOUBLE 278
#define EQ 279
#define GT 280
#define GE 281
#define LT 282
#define LE 283
#define NE 284
#define NUMBER_LITERAL 285
#define STRING_LITERAL 286
#define VAR 287
#define ADD 288
#define SUBSTRACT 289
#define PROD 290
#define DIV 291
#define MODULE 292
#define AND 293
#define OR 294
#define NOT 295
#define OPEN_B 296
#define CLOSE_B 297
#define OPEN_P 298
#define CLOSE_P 299
#define PRINT 300
#define START 301
#define END 302
#define DEFINE 303
#define PASSING 304

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "kind.y"

    char character;
    int integer;
    double decimal;
    char string[240];

#line 162 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
