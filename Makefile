all: compile run

compile: main.c lexer.c
	cc -Wall -Wextra -ggdb -o main main.c lexer.c parser.c util.c semantic.c

run: main
	./main
