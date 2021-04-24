CXXFLAGS=-std=c++17 -O2 -Wall -Wextra -pedantic -pipe -I../include -I/usr/local/include

test: tests.o main.o
	${CXX} -o test tests.o main.o

run_tests: test
	./test
