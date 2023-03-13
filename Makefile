findAngular: src/main.c src/utility.c unit_tests 
	gcc -g src/main.c src/utility.c -o findAngular -lpthread -lm -fPIC -mcmodel=large
	make test

unit_tests: unit-tests/main.c unit-tests/utest.h src/utility.c src/utility.h 
	gcc unit-tests/main.c src/utility.c -lm -o unit-test -fPIC -mcmodel=large

test: unit_tests
	./unit-test

clean:
	rm ./findAngular ./unit_tests



