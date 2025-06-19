all: compile run

compile: supernova.c lexer.c
	cc -Wall -Wextra -ggdb -o supernova main.c lexer.c parser.c util.c semantic.c

run: supernova
	./supernova
