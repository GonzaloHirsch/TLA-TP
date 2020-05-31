.PHONY: clean

all:
	yacc -d kind.y --debug
	lex grammar.l
	gcc lex.yy.c y.tab.c symboltable.c utility.c node2.c -o codeGenerator
	./test.sh

clean:
	rm -f codeGenerator
	rm -rf tests/*.c tests/*results