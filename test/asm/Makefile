CXXFLAGS=-std=c++17 -O2 -Wall -Wextra -pedantic -pipe -I../../include -I/usr/local/include
ASMFLAGS=-S -masm=intel
DIFFFLAGS=-u --ignore-matching-lines '\s*\.file\s*' --ignore-matching-lines '^\.L[a-zA-Z_0-9]*:'

.PHONY: all
all: asm_4int asm_1string asm_3strings

.PHONY: clean
clean:
	rm -f *.s

.PHONY: asm_%
asm_%: plain_%.s anyof_%.s
	diff ${DIFFFLAGS} $^

.cpp.s:
	${CXX} ${CXXFLAGS} ${ASMFLAGS} $<
