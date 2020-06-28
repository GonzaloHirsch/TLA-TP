.PHONY: clean

all:
	yacc -d kind.y -Wconflicts-rr
	lex grammar.l
	gcc -g lex.yy.c y.tab.c translation/*.c node.c -o codeGenerator

clean:
	rm -f codeGenerator
	rm -rf tests/*.c tests/*results

debug:
	yacc -d kind.y --debug -Wconflicts-rr
	lex grammar.l
	gcc -g lex.yy.c y.tab.c translation/*.c node.c -o codeGenerator
	./debug.sh tests/test12-multiplication.tst