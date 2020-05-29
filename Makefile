.PHONY: clean

all:
	yacc -d kind.y
	lex grammar.l
	gcc lex.yy.c y.tab.c symboltable.c utility.c -o codeGenerator 

clean:
	rm -f codeGenerator
