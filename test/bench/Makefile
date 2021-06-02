CXXFLAGS=-std=c++17 -O2 -Wall -Wextra -pedantic -pipe -I../../include -I/usr/local/include
LDFLAGS=-L/usr/local/lib -lbenchmark

run_bench: bench
	./simple_bench

bench: simple_bench.o
	${CXX} -o simple_bench simple_bench.o ${LDFLAGS}

.PHONY: clean
clean:
	rm -f *.o simple_bench

deps:
	mkdep ${CXXFLAGS} *.cpp
