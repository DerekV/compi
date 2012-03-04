/*******************************************************/
/*                     VOID PARSER                     */
/*                                                     */
/*******************************************************/

/*********************DEFINITIONS***********************/
%{

#ifndef NULL
#define NULL 0
#endif 
#define CON 10
#include <cstdio>

int yyerror(char*);
extern int yylex();
int yyparse(void);

#include <string>
#include "ast.h"

#define YYERROR_VERBOSE
  /* #define YYSTYPE ast_node; */


%}

%start program



%token			O_AND		1
%token			O_ARRAY		2
%token			O_BEGIN		3
%token			O_CHARACTER 	5
%token			O_DO 		6
%token			O_ELSE 		7
%token			O_END 		8
%token			O_FLOAT   	9
%token			O_FUNCTION 	10
%token			O_IF 		11
%token			O_INTEGER 	12 
%token			O_NOT 		13
%token			O_OF 		14
%token			O_OR 		15
%token			O_PROCEDURE 	16
%token			O_PROGRAM 	17
%token			O_READ 		18
%token			O_THEN 		19
%token			O_VAR 		20
%token			O_WHILE         21
%token			O_WRITE	        22
%token			O_LBRACE 	23
%token			O_RBRACE 	24
%token			O_CONSTANT 	25
%token			O_LE 		26
%token			O_LT 		27
%token			O_GE 		28
%token			O_GT 		29
%token			O_EQ 		30
%token			O_NE 		31
%token			O_ASSIGN 	32
%token			O_COLON 	33
%token			O_SEMICOLON	34
%token			O_COMMA 	35
%token			O_LBRACKET 	36
%token			O_RBRACKET 	37
%token			O_LPAREN 	38
%token			O_RPAREN 	39
%token			O_DOTDOT 	40
%token			O_PLUS 		41
%token			O_TIMES 	42
%token	<cstringt>	O_IDENTIFER 	43
%token			O_MOD           44
%token			O_RETURN	45
%token	<cstringt>	O_CHAR    	46
%token	<cstringt>	O_STRING	47 // try switching cstringt to stringt 
%token	<cstringt>	O_INT    	48 // sometime
%token	<cstringt>	O_FLOATCON 	49
%token			O_MINUS		50
%token			O_CASE		51

%left O_THEN
%left O_ELSE
%left O_IF
%left O_OR
%left O_AND
%left O_NOT
%left O_LT,O_LE,O_GT,O_GE,O_NE,O_EQ
%left O_PLUS,O_MINUS
%left O_TIMES,O_MOD


%union
{
  ast::program* programt;


  vector<ast::decl*>* declistt;
  vector<ast::subprogram*>* subprogramdeclistt;
  vector<string*>* stringlistt;
  vector<ast::statement*>* statementlistt;
  vector<ast::expression*>* expressionlistt;
  vector<ast::constant*>* constantlistt;
  vector<ast::caseelement*>* caseelementlistt;



  ast::statement*	statementt;
  ast::compound*	compoundt;
  ast::node*		nodet;
  ast::expression*	expressiont;
  ast::dualexpr*	dualexprt;	
  ast::invocation*	invocationt;
  ast::monoexpr*	monoexprt;
  ast::varref*		varreft;
  ast::constant*	constantt;
  ast::write* 		writet;
  ast::writestring*	writestringt;
  ast::read*		readt;
  ast::ifstatement*	ifst;
  ast::whilestatement*  whilest;
  ast::casestatement*   casest;
  ast::caseelement*	caseelementt; 
  ast::assignment*	assignmentt;
  ast::returnstatement* returnst;
  ast::type*		typet;
  ast::subprogram*	subprogramt;

  int intt;
  string* stringt;
  char* cstringt;
}

%type <programt> 		program
%type <compoundt> 		compoundstatement
%type <subprogramdeclistt> 	subprogramdecls
%type <subprogramt>		subprogramdecl
%type <declistt>		decls



%type <stringt> 		identifier
%type <stringlistt> 		identifierlist
%type <declistt> 		decllist
%type <declistt>		parameterlist
%type <declistt>		arguments


%type <typet>			type
%type <typet>			standardtype
%type <typet>			arraytype

%type <expressiont> 		factor

%type <expressiont>		rexpr
%type <expressiont> 		expr
%type <expressionlistt>		exprlist
%type <varreft>			variable
%type <constantt>		constant
%type <intt>			intnum
%type <stringt>			charconstant
%type <stringt>			floatconstant
%type <stringt>			stringconstant
%type <returnst>		returnstatement



%type <statementt>		statement
%type <statementlistt> 		statementlist

%type <invocationt> 		procedureinvocation

%type <assignmentt> 		assignment

%type <casest>			casestatement
%type <constantlistt>		caselabels
%type <caseelementt>		caseelement
%type <caseelementlistt>	cases

%type <ifst>			ifstatement
%type <whilest>			whilestatement
%type <statementt>		iostatement


/***********************PRODUCTIONS****************************/
%%

program: O_PROGRAM identifier O_SEMICOLON decls subprogramdecls compoundstatement
	{	
	
	ast::gprog = new ast::program( $<stringt>2, $<declistt>4, $<subprogramdeclistt>5, 
	$<compoundt>6 ); 

	};
	

decls:	/*empty*/  { $$ = new vector<ast::decl*>;} // empty
	|	O_VAR decllist
	{ $$ = $2; };
	

decllist:	identifierlist O_COLON type O_SEMICOLON 
	{
	  $$ = new vector<ast::decl*>;
 	  for(int i = 0; i < $1->size(); i++)
            $$->push_back( new ast::vardecl( (* $1 )[i], $3 )); }
	|	decllist identifierlist O_COLON type O_SEMICOLON

	{ 
	  $$ = $1;
	  for(int i = 0; i < ($2)->size(); i++)
	      ($$)->push_back( new ast::vardecl( (* ($2) )[i], ($4))); 
	};

identifierlist:	identifier {($$ = new vector<string*>)->push_back($1);}
	|	identifierlist O_COMMA identifier 
	{($$ = $1)->push_back($3);};

type:		standardtype { $$ = $1; }
	|	arraytype { $$ = $1; };


standardtype:	O_INTEGER { $$ = new ast::type(ast::tINTEGER);}
	|	O_FLOAT { $$ = new ast::type(ast::tFLOAT);}
	|	O_CHARACTER {$$ = new ast::type(ast::tCHAR);} ;

arraytype:	O_ARRAY O_LBRACKET intnum O_DOTDOT intnum 
			O_RBRACKET O_OF standardtype
		{$$ = ast::type::new_array( *$8, $3, $5, ast::tINTEGER);}
	|	O_ARRAY O_LBRACKET charconstant O_DOTDOT charconstant
			O_RBRACKET O_OF standardtype
		{$$ = ast::type::new_array( *$8, (int)$3, (int)$5, ast::tCHAR);};
// this is going to be really funny untill the different constants have real types

subprogramdecls: /*empty*/ { $$ = new vector<ast::subprogram*>;}
	|	subprogramdecls subprogramdecl
	{ ($$ = $1)->push_back($2);};

subprogramdecl:	O_FUNCTION identifier  arguments O_COLON standardtype 
			O_SEMICOLON decls compoundstatement O_SEMICOLON
		{ $$ = new ast::subprogram( $2, $7, $8, $3, $5 ); }		

	|	O_PROCEDURE identifier arguments O_SEMICOLON  
			decls compoundstatement O_SEMICOLON
		{ $$ = new ast::subprogram( $2, $5, $6, $3, 
					new ast::type(ast::tVOID) );};

arguments:	/*empty*/ { $$ = new vector<ast::decl*>;}
	|	O_LPAREN parameterlist O_RPAREN {$$ = $2;};


parameterlist:	identifierlist O_COLON type 
			{
	  		  $$ = new vector<ast::decl*>;
 	  		  for(int i = 0; i < $1->size(); i++)
              		  $$->push_back( new ast::paramdecl( (* $1 )[i], $3 )); 
			}
	|	parameterlist O_SEMICOLON
			identifierlist O_COLON type 
			{ 
	  		  $$ = $1;
	  		  for(int i = 0; i < ($3)->size(); i++)
	      		  ($$)->push_back( new ast::paramdecl( (* ($3) )[i], ($5))); 
			};

statement:	assignment {$$ = $1}
	|	ifstatement {$$ = $1}
	|	whilestatement {$$ = $1}
	|	casestatement {$$ = $1}
	|	procedureinvocation {$$ = $1}
	|	iostatement {$$ = $1}
	|	compoundstatement {$$ = $1}
	|	returnstatement {$$ = $1};

assignment:	variable O_ASSIGN expr { $$ = new ast::assignment($1, $3);};

ifstatement:	O_IF expr
			O_THEN statement
			O_ELSE statement { $$ = new ast::ifstatement( $2, $4, $6 );}
	|	O_IF expr O_THEN statement {$$ = new ast::ifstatement( $2, $4); };

whilestatement:	O_WHILE expr O_DO statement 
	{ $$ = new ast::whilestatement($2, $4); };


casestatement:	O_CASE expr O_OF cases O_END
	{ $$ = new ast::casestatement($2, $4); };


cases:		/*empty*/ {$$ = new vector<ast::caseelement*>;}	
	|	caseelement 
		{ ($$ = new vector<ast::caseelement*>)->push_back($1);}
	|	cases O_SEMICOLON caseelement 
		{ ($$ = $1)->push_back($3); };



caseelement:	// /*empty*/ {$$ = ;} | 
	caselabels O_COLON statement 
	{$$ = new ast::caseelement($1, $3 );};


caselabels:	constant {($$ = new vector<ast::constant*>)->push_back($1);}
	|	caselabels O_COMMA constant {($$ = $1)->push_back($3);};


procedureinvocation:
		identifier O_LPAREN O_RPAREN          
			{$$ = new ast::invocation($1, new vector<ast::expression*>);}
	|	identifier O_LPAREN exprlist O_RPAREN 
			{$$ = new ast::invocation($1, $3);};


iostatement:	O_READ O_LPAREN variable O_RPAREN   {$$ = new ast::read($3);}
	|	O_WRITE	 O_LPAREN expr O_RPAREN {$$ = new ast::write($3);}
	|	O_WRITE	 O_LPAREN stringconstant O_RPAREN 
	{$$ = new ast:: writestring($3);}; 


compoundstatement:	O_BEGIN
	statementlist O_END
	{$$ = new ast::compound($2);};


statementlist:	statement {($$ = new vector<ast::statement*>)->push_back($1);}
	|	statementlist O_SEMICOLON statement {($$ = $1)->push_back($3);};


returnstatement: O_RETURN expr {$$ = new ast::returnstatement($2);};


exprlist:	expr {($$ = new vector<ast::expression*>)->push_back($1);}
	|	exprlist O_COMMA expr {($$ = $1)->push_back($3);};

expr:		rexpr	      		{ $$ = $1; }
	| 	expr O_TIMES 	rexpr	{ $$ = new ast::multiplication($1, $3 ); }
	| 	expr O_MOD 	rexpr	{ $$ = new ast::modulus     ($1, $3 ); }
	| 	expr O_LT 	rexpr 	{ $$ = new ast::lessthan    ($1, $3 ); }
	| 	expr O_GT 	rexpr	{ $$ = new ast::greaterthan ($1, $3 ); }
	| 	expr O_LE 	rexpr	{ $$ = new ast::complement(
						new ast::greaterthan($1, $3 )); }
	| 	expr O_GE 	rexpr	{ $$ = new ast::complement(
						new ast::lessthan($1, $3 )); }
	| 	expr O_NE 	rexpr	{ $$ = new ast::complement(
						new ast::equivalence($1, $3 )); }
	| 	expr O_EQ 	rexpr	{ $$ = new ast::equivalence ($1, $3 ); }
	| 	expr O_PLUS 	rexpr	{ $$ = new ast::addition    ($1, $3, false);}
	| 	expr O_MINUS 	rexpr	{ $$ = new ast::addition    ($1, $3, true );}
	| 	expr O_AND 	rexpr	{ $$ = new ast::logicaland  ($1, $3 ); }
	| 	expr O_OR 	rexpr	{ $$ = new ast::logicalor   ($1, $3 ); };


rexpr:		O_NOT expr {$$ = new ast::complement($2);}
	|	factor { $$ = $1; };


factor:		variable { $$ = $1;}
	|	constant { $$ = $1;}
	|	O_LPAREN expr O_RPAREN { $$ = new ast::monoexpr($2);}
	|	procedureinvocation { $$ = $1; };


variable:	identifier { $$ = new ast::varref($1);}
	|	identifier O_LBRACKET expr O_RBRACKET 
		{
		ast::varref* foo = new ast::varref($1);
		  $$ = 
		    (ast::varref*) new ast::subscript(foo, $3); 
		};


stringconstant:	O_STRING {$$ = new string($1);};


intnum:		O_INT {$$ = atoi($1);};


floatconstant:	O_FLOATCON {$$ = new string($1);};


charconstant:	O_CHAR {$$ = new string($1);};


constant:	charconstant { $$ = new ast::stringconstant($1); }
	|	floatconstant { $$ = new ast::stringconstant($1);}
	|	intnum { $$ = new ast::intconstant($1);};


identifier:	O_IDENTIFER {$$ = new string($1);};

%%
/*********************EXTERNAL DECLARATIONS***********************/


extern char yytext[];
extern FILE  *yyin;
extern int yylineno;
int errcount=0;




/********************C ROUTINES *********************************/
int yyerror(char *s)
{

  printf("Parse error[%d]: %s\n",yylineno,s);
}




/******************END OF C ROUTINES**********************/







/* old expression syntax 
expr:		expr op rexpr
	|	rexpr {$$ = 0;};


rexpr:		O_NOT expr {$$ = 0;}
	|	factor { $$ = 0; };


op:		mulop { $$ = new ast::dummyop(); } 
	|	relop { $$ = new ast::dummyop(); }
	|	addop { $$ = $1; }
	|	logop { $$ = new ast::dummyop(); };


mulop:		O_TIMES
	|	O_MOD;


relop:		O_LT
	|	O_GT
	|	O_LE
	|	O_GE
	|	O_NE
	|	O_EQ;


addop:		O_PLUS 
	|	O_MINUS ;


logop:		O_AND
	|	O_OR;

*/
