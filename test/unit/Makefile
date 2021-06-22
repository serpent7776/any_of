CXXFLAGS=-std=c++17 -O2 -Wall -Wextra -pedantic -pipe -I../../include -I/usr/local/include

test: any_of_basic_tests.o any_of_std__algorithm_tests.o none_of_basic_tests.o equals_to_any_of_tests.o main.o
	${CXX} -o test $^

.PHONY: clean
clean:
	rm -f *.o test

run_tests: test
	./test

deps:
	mkdep ${CXXFLAGS} *.cpp

-include .depend
