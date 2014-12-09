CXX_FLAGS = -Wall --debug --std=c++0x -I./include/
CC_FLAGS = -Wall --debug  -I./include/
LD_FLAGS =  -lpthread -lm -L./lib/ -Wl,-rpath=../lib,-rpath=./lib
CXX = g++
CC = gcc
#STATIC =-static

OUTPUT = bin/hooiberg

all: $(OUTPUT)

lib/hooiberg.o: src/hooiberg.cc
	$(CXX) -c src/hooiberg.cc -o lib/hooiberg.o $(CXX_FLAGS)

lib/ExpressionTree.o: src/ExpressionTree.cc
	$(CXX) -c src/ExpressionTree.cc -o lib/ExpressionTree.o $(CXX_FLAGS)
	
lib/ExpressionAtom.o: src/ExpressionAtom.cc
	$(CXX) -c src/ExpressionAtom.cc -o lib/ExpressionAtom.o $(CXX_FLAGS)
	
$(OUTPUT): lib/hooiberg.o lib/ExpressionTree.o lib/ExpressionAtom.o
	$(CXX) $(STATIC) lib/hooiberg.o lib/ExpressionTree.o lib/ExpressionAtom.o -o $(OUTPUT) $(LD_FLAGS)

clean: 
	rm -f lib/*.o
	rm -f $(OUTPUT)

