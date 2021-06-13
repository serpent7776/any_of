CXXFLAGS=-std=c++17 -O2 -Wall -Wextra -pedantic -pipe -I../../include -I/usr/local/include

test: tests.o main.o
	${CXX} -o test tests.o main.o

.PHONY: clean
clean:
	rm -f *.o test

run_tests: test
	./test

deps:
	mkdep ${CXXFLAGS} *.cpp
