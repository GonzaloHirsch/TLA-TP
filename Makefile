.PHONY: clean

all:
	yacc -d yacc.y -Wconflicts-rr
	lex grammar.l
	gcc -g lex.yy.c y.tab.c translation/*.c node.c -o codeGenerator

clean:
	rm -f codeGenerator
	rm -rf tests/*.c tests/*results

debug:
	yacc -d yacc.y --debug -Wconflicts-rr
	lex grammar.l
	gcc -g lex.yy.c y.tab.c translation/*.c node.c -o codeGenerator
	./debug.sh tests/test12-multiplication.tst