%option noyywrap
%option yylineno




WS	[ \t\n]

%{

/* This scanner approximates the Void specification.
 *
 * Major differences:
 *
 *  (1) the printed spec is wrong in about sixteen ways in its definition
 *	of numeric constants.  The scanner recognizes a fairly broad class
 * 	of things as constants - it allows both 0 and 1.0 as constants, where
 *	the document would not.
 *
 *      Feel free to accept the things that the scanner accepts as constants.
 *	The bug is in the original spec document.
 *
 *	Note: the scanner classifies all kinds of constants as "constant".
 *	It does not make a distinction between character, integer, and floating
 *	point constants.  I think of that distinction as something to look for
 *	in the type checker lab, not something that the grammar should enforce.
 *
 *
 * To hook this thing up to your parser, you will need to take the include
 * file of grammar terminals and relate them to the constants defined below.
 * You can either edit the flex spec or edit the constant defintions.  (Of
 * course, you should do that on your own copy!) 
 *
 */

#include "void.tab.h"
#include<string>
#include<iostream>


%}


%%


MOD                     { return O_MOD; }
AND 			{ return O_AND; }
ARRAY			{ return O_ARRAY; }
BEGIN			{ return O_BEGIN; }
CHARACTER		{ return O_CHARACTER; }
DO			{ return O_DO; }
ELSE			{ return O_ELSE; }
END 			{ return O_END; }
FLOAT			{ return O_FLOAT; }
FUNCTION		{ return O_FUNCTION; }
IF			{ return O_IF; }
INTEGER			{ return O_INTEGER; }
NOT			{ return O_NOT; }
OF			{ return O_OF; }
OR			{ return O_OR; }
PROCEDURE		{ return O_PROCEDURE; }
PROGRAM			{ return O_PROGRAM; }
READ			{ return O_READ; }
RETURN			{ return O_RETURN;  }
THEN			{ return O_THEN; }
VAR			{ return O_VAR; }
WHILE			{ return O_WHILE; }
WRITE			{ return O_WRITE; }
CASE			{ return O_CASE; }

\<=			{ return O_LE; }
\<			{ return O_LT; }
\>=			{ return O_GE; }
\>			{ return O_GT; }
\=			{ return O_EQ; }
\<>			{ return O_NE; }
\:=			{ return O_ASSIGN; }
\:			{ return O_COLON; }
\;			{ return O_SEMICOLON; }
\,			{ return O_COMMA; }
\[			{ return O_LBRACKET; }
\]			{ return O_RBRACKET; }
\(			{ return O_LPAREN; }
\)			{ return O_RPAREN; }
\.\.			{ return O_DOTDOT; }
\+			{ return O_PLUS; }
\-                      { return O_MINUS; }
\*			{ return O_TIMES; }

\'[^\']\'			{ yylval = (int)yytext; return O_CHAR; }
\'[^\']*\'			{ yylval = (int)yytext; return O_STRING; }
[a-zA-Z]([a-zA-Z]|[0-9])*	{/* the int cast is probably bad style */ 				
				yylval = (int)yytext;				
				return O_IDENTIFER; }


[0-9]+				{ yylval = (int)yytext; return O_INT; }

\{[^\}]*\}				{ ; }
{WS}					{ ; }

[0-9]*(\.)[0-9]+((e|E)(\+|\-)?[0-9]*)?/[^.$]   { yylval = (int)yytext; return O_FLOATCON; }

[0-9]+((e|E)(\+|\-)?[0-9]*)/[^.$]   { yylval = (int)yytext; return O_FLOATCON; }

.		{fprintf(stderr, "Scanner: lexical error '%s'.\n", yytext); }
%%


