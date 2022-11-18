

whodunit:whodunit.c mySource.c
	clang -ggdb3 -Wall -Werror -o whodunit whodunit.c mySource.c -lm

fifteen: fifteen.c helper.c helper.h
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o fifteen fifteen.c helper.c -lm

test:test.c mySource.c
	clang -ggdb -Wall -Werror -o test test.c mySource.c -lm
resize:resize.c
	clang -ggdb3 -Wall -Werror -o resize resize.c -lm	

clean:
	rm -f *.o a.out core fifteen log.txt
