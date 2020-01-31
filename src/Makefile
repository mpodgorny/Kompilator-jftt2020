CC = g++
FLAGS = -std=c++17

all: compiler

compiler: parser.o lexer.o logic.o operations.o conditions.o loops.o
	$(CC) $(FLAGS) -o compiler parser.o lexer.o logic.o operations.o conditions.o loops.o

loops.o: loops.cpp
	$(CC) $(FLAGS) -c loops.cpp

conditions.o: conditions.cpp
	$(CC) $(FLAGS) -c conditions.cpp

operations.o: operations.cpp
	$(CC) $(FLAGS) -c operations.cpp

logic.o: logic.cpp
	$(CC) $(FLAGS) -c logic.cpp

lexer.o: lexer.c	
	$(CC) $(FLAGS) -c lexer.c

parser.o: parser.tab.c
	$(CC) $(FLAGS) -c parser.tab.c -o parser.o

lexer.c: lexer.l
	flex -o lexer.c lexer.l

parser.tab.c: parser.y
	bison -d parser.y

clean:
	rm -f *.o *~ *.c *.tab.c *.tab.h
	rm -f compiler