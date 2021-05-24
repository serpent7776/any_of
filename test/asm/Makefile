CXXFLAGS=-std=c++17 -O2 -Wall -Wextra -pedantic -pipe -I../../include -I/usr/local/include
ASMFLAGS=-S -mllvm --x86-asm-syntax=intel 
DIFFFLAGS=-u --ignore-matching-lines '\s*\.file\s*'

.PHONY: all
all: asm_4int asm_1string asm_3strings

.PHONY: clean
clean:
	rm -f *.s

.PHONY: asm_%
asm_%: plain_%.s anyof_%.s
	diff ${DIFFFLAGS} $^

plain_%.s: plain_%.cpp
	${CXX} ${CXXFLAGS} ${ASMFLAGS} $<

anyof_%.s: anyof_%.cpp
	${CXX} ${CXXFLAGS} ${ASMFLAGS} $<
