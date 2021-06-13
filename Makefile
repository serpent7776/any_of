.PHONY: help
help:
	@echo available targets:
	@echo "clean  clean build files"
	@echo "test   run unit tests"
	@echo "bench  run benchmark tests"
	@echo "asm    run asm generation tests"
	@echo "deps   generate deps files"

.PHONY: clean
clean:
	${MAKE} -C test clean
	${MAKE} -C test/bench clean
	${MAKE} -C test/asm clean

.PHONY: test
test:
	${MAKE} -C test/unit run_tests

.PHONY: bench
bench:
	${MAKE} -C test/bench run_bench

.PHONY: asm
asm:
	${MAKE} -C test/asm all

deps:
	${MAKE} -C test deps
	${MAKE} -C test/bench deps
