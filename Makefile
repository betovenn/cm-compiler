.PHONY: all clean dirs

all: dirs

	bison -d -o parser/parser.tab.c src/parser.y

	flex -o lexer/lexer.yy.c src/lexer.l

	gcc \
	parser/parser.tab.c \
	lexer/lexer.yy.c \
	src/ast.c \
	-I./src \
	-o bin/compiler

	./bin/compiler tests/prueba16.txt

dirs:
	mkdir -p parser
	mkdir -p lexer
	mkdir -p bin
	mkdir -p output

clean:

	rm -f parser/parser.tab.c
	rm -f parser/parser.tab.h
	rm -f lexer/lexer.yy.c
	rm -f bin/compiler
