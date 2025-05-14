all: compile run

compile: main.c lexer.c
	cc -Wall -Wextra -ggdb -o main main.c lexer.c

run: main
	./main
