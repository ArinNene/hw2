CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS=amazon.o user.o db_parser.o product.o product_parser.o util.o book.o clothing.o movie.o mydatastore.o

all: amazon

amazon: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

amazon.o: amazon.cpp db_parser.cpp datastore.h mydatastore.cpp product_parser.cpp 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c amazon.cpp
mydatastore.o: mydatastore.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c mydatastore.cpp
user.o: user.cpp user.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c user.cpp
db_parser.o: db_parser.cpp db_parser.h product.h product_parser.h user.h datastore.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c db_parser.cpp
product.o: product.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product.cpp
product_parser.o: product_parser.cpp product_parser.h product.h book.h clothing.h movie.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product_parser.cpp
util.o: util.h util.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c util.cpp
book.o: book.h book.cpp product.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c book.cpp
clothing.o: clothing.h clothing.cpp product.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c clothing.cpp
movie.o: movie.h movie.cpp product.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c movie.cpp



clean:
	rm -f *.o amazon
