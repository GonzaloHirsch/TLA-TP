.PHONY: clean

all:
	yacc -d traduce.y
	lex scanner.l
	gcc lex.yy.c y.tab.h -o codeGenerator

clean:
	rm -f codeGenerator
