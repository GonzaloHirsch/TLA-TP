.PHONY: clean

all:
	yacc -d kind.y
	lex grammar.l
	gcc lex.yy.c y.tab.h -o codeGenerator

clean:
	rm -f codeGenerator
