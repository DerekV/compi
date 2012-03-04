

TARGET = void
CFLAGS = -g
CC = g++
CCC = g++
OFILES =  lex.yy.o \
   const.o sparc.process.const.o void.typecheck.const.o \
   varref.o sparc.process.varref.o void.typecheck.varref.o\
   env.o instruction.o regprocessor.o \
   decl.o void.typecheck.decl.o sparc.process.decl.o \
   expression.o void.typecheck.expression.o sparc.process.expression.o \
   progseg.o void.typecheck.progseg.o sparc.process.progseg.o \
   statement.o sparc.process.statement.o void.typecheck.statement.o\
   type.o invocation.o \
   void.tab.o node.o main.o 

all: void



void: $(OFILES)
	$(CC) -o $(TARGET) $(OFILES)

main.C: env.h regprocessor.h node.h decl.h progseg.h type.h

void.tab.o: void.tab.c ast.h
	$(CC) $(CFLAGS) -c void.tab.c 

void.tab.c: void.y
	bison void.y

lex.yy.o: lex.yy.c void.tab.h
	$(CC) $(CFLAGS) -c lex.yy.c

lex.yy.c: void.l
	rm -f lex.yy.c; flex void.l

const.C: const.h env.h type.h 
sparc.process.const.C : const.h instruction.h env.h
void.typecheck.const.C : const.h env.h type.h

varref.C: varref.h 
void.typecheck.varref.C: varref.h env.h decl.h
sparc.process.varref.C: varref.h instruction.h env.h decl.h

env.C: env.h hash.h decl.h type.h instruction.h regprocessor.h 

type.C: type.h decl.h

decl.C: decl.h type.h
void.typecheck.decl.C: decl.h type.h 
sparc.process.decl.C: decl.h type.h env.h

expression.C: expression.h
void.typecheck.expression.C: expression.h env.h type.h
sparc.process.expression.C: expression.h env.h 

node.C: node.h env.h type.h instruction.h

progseg.C: progseg.h
void.typecheck.progseg.C: progseg.h type.h env.h
sparc.process.progseg.C: progseg.h env.h instruction.h

statement.C: statement.h
void.typecheck.statement.C:  statement.h type.h env.h
sparc.process.statement.C:  statement.h instruction.h env.h

invocation.C: invocation.h

instruction.C: instruction.h

regprocessor.C: regprocessor.h instruction.h

node.h: 

expression.h: node.h

const_varref.h: expression.h instruction.h

env.h: hash.h regprocessor.h

type.h:

decl.h: node.h

ast.h: node.h expression.h statement.h const_varref.h invocation.h \
	env.h progseg.h decl.h type.h regprocessor.h instruction.h

progseg.h: node.h

statement.h: node.h expression.h const.h varref.h

invocation.h: expression.h

instruction.h:


clean:
	rm -f *.o; rm -f void.tab.c; rm -f lex.yy.c
