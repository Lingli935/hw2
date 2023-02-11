CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

SRC=amazon.cpp book.cpp clothing.cpp db_parser.cpp movie.cpp mydatastore.cpp product.cpp product_parser.cpp user.cpp util.cpp 

all: amazon

amazon: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@

clean:
	rm -f *.o amazon

