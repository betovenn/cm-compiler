main:
	gcc src/main.c -o bin/cmc
	bin/./cmc
clean:
	rm -f bin/cmc
