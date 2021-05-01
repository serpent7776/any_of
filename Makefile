.PHONY: test
test:
	${MAKE} -C test run_tests

deps:
	${MAKE} -C test deps
