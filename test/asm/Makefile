CXXFLAGS=-std=c++17 -O2 -Wall -Wextra -pedantic -pipe -I../../include -I/usr/local/include
ASMFLAGS=-S -mllvm --x86-asm-syntax=intel 
DIFFFLAGS=-u --ignore-matching-lines '\s*\.file\s*'

.PHONY: all
all: asm_4int asm_1string

.PHONY: asm_4int
asm_4int:
	${CXX} ${CXXFLAGS} ${ASMFLAGS} plain_4int.cpp
	${CXX} ${CXXFLAGS} ${ASMFLAGS} anyof_4int.cpp
	diff ${DIFFFLAGS} plain_4int.s anyof_4int.s

.PHONY: asm_1string
asm_1string:
	${CXX} ${CXXFLAGS} ${ASMFLAGS} plain_1string.cpp
	${CXX} ${CXXFLAGS} ${ASMFLAGS} anyof_1string.cpp
	diff ${DIFFFLAGS} plain_1string.s anyof_1string.s
