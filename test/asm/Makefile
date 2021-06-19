DIFF=diff
VIEWDIFF=vimdiff
CXXFLAGS=-std=c++17 -O2 -Wall -Wextra -pedantic -pipe -I../../include -I/usr/local/include
ASMFLAGS=-S -masm=intel
DIFFFLAGS=-u --ignore-matching-lines '\s*\.file\s*' --ignore-matching-lines '^\.L[a-zA-Z_0-9]*:'

.PHONY: all
all: diff_4int diff_1string diff_3strings_small diff_3strings_big diff_find_if

.PHONY: clean
clean:
	rm -f *.s

.PHONY: diff_%
diff_%: plain_%.s anyof_%.s
	${DIFF} ${DIFFFLAGS} $^

.PHONY: view_%
view_%: plain_%.s anyof_%.s
	${VIEWDIFF} $^

.cpp.s:
	${CXX} ${CXXFLAGS} ${ASMFLAGS} $<

deps:
	mkdep ${CXXFLAGS} *.cpp
