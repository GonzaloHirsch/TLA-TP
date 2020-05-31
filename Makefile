.PHONY: clean

all:
	yacc -d kind.y --debug -Wconflicts-rr
	lex grammar.l
	gcc -g lex.yy.c y.tab.c symboltable.c utility.c node2.c -o codeGenerator

test:
	make all
	./test.sh

clean:
	rm -f codeGenerator
	rm -rf tests/*.c tests/*results

debug:
	yacc -d kind.y --debug -Wconflicts-rr
	lex grammar.l
	gcc -g lex.yy.c y.tab.c symboltable.c utility.c node2.c -o codeGenerator
	./debug.sh tests/test11-firstparseable.tst