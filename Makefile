# Atajos para descomentar y comentar código en Visual Studio Code:
# - Windows: Ctrl + K, Ctrl + C (comentar) / Ctrl + K
# Ctrl + U (descomentar)


# # # Makefile Version Windows MSYS2
# .PHONY: all clean dirs

# all: dirs

# 	bison -d -o parser/parser.tab.c src/parser.y

# 	flex -o lexer/lexer.yy.c src/lexer.l

# 	gcc \
# 	parser/parser.tab.c \
# 	lexer/lexer.yy.c \
# 	src/ast.c \
# 	src/semantic.c \
# 	src/codegen.c \
# 	-I./src \
# 	-o bin/compiler

# 	./bin/compiler tests/116425_ejemplo.txt

# dirs:
# 	mkdir -p parser
# 	mkdir -p lexer
# 	mkdir -p bin
# 	mkdir -p output

# clean:

# 	rm -f parser/parser.tab.c
# 	rm -f parser/parser.tab.h
# 	rm -f lexer/lexer.yy.c
# 	rm -f bin/compiler



# # # # Makefile Version Linux
.PHONY: all clean dirs

CC = gcc

CFLAGS = -I./src

LDFLAGS = -lfl

TARGET = bin/compiler

all: dirs $(TARGET)

$(TARGET):

	bison -d -o parser/parser.tab.c src/parser.y

	flex -o lexer/lexer.yy.c src/lexer.l

	$(CC) \
	parser/parser.tab.c \
	lexer/lexer.yy.c \
	src/ast.c \
	src/semantic.c \
	src/codegen.c \
	$(CFLAGS) \
	$(LDFLAGS) \
	-o $(TARGET)

	./$(TARGET) tests/116425_ejemplo.txt

dirs:
	mkdir -p parser
	mkdir -p lexer
	mkdir -p bin
	mkdir -p output

clean:
	rm -f parser/parser.tab.c
	rm -f parser/parser.tab.h
	rm -f lexer/lexer.yy.c
	rm -f $(TARGET)



# Direcciones de test para Windows MSYS2 ó Ubuntu WSL:
# cd C:\Users\Admin\Desktop\cm-compiler-main\cm-compiler-main1
# cd /c/Users/Admin/Desktop/cm-compiler-main/cm-compiler-main1
# cd /mnt/c/Users/Admin/Desktop/cm-compiler-main/cm-compiler-main1

