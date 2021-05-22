.PHONY: test
test:
	${MAKE} -C test run_tests

.PHONY: bench
bench:
	${MAKE} -C test/bench run_bench

.PHONY: asm
asm:
	${MAKE} -C test/asm all

deps:
	${MAKE} -C test deps
	${MAKE} -C test/bench deps
