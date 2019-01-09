# Chaitanya Ingle
# Sec. 1002
# Ast. 08

OBJS	= mazeSolver.o maze.o
CC	= g++ -Wall -pedantic -g -std=c++11
DEPS	= priorityQueue.h mazeSolver.h
DEPS1	= priorityQueue.h

all:  pqTest maze

#hashTable.o: hashTable.cpp $(DEPS1)
#	$(CC) -c hashTable.cpp

pqTest.o: pqTest.cpp $(DEPS1)
	$(CC) -c pqTest.cpp

pqTest: pqTest.o  $(DEPS1)
	$(CC) -o pqTest pqTest.o

mazeSolver.o: mazeSolver.cpp $(DEPS)
	$(CC) -c mazeSolver.cpp

maze.o: maze.cpp mazeSolver.o $(DEPS)
	$(CC) -c maze.cpp

maze: maze.o $(DEPS)
	$(CC) -o maze $(OBJS)

# -----
# clean by removing object files.
	@rm	$(OBJS) pqTest.o

