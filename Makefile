.PHONY: lexer clean
lexer:
	flex -o lexer/lexer.yy.c src/lexer.l 	
	gcc lexer/lexer.yy.c -lfl -o bin/lexer
	./bin/lexer tests/test.txt
clean:
	rm -f bin/lexer lexer/lexer.yy.c
