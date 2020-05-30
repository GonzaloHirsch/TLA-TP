.PHONY: clean

all:
	yacc -d kind.y
	lex grammar.l
	gcc lex.yy.c y.tab.c symboltable.c utility.c -o codeGenerator
	./test.sh

clean:
	rm -f codeGenerator
