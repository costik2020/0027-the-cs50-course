

fifteen: fifteen.c helper.c helper.h
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o fifteen fifteen.c helper.c -lm

test:test.c mySource.c
	clang -ggdb -Wall -Werror -o test test.c mySource.c -lm

clean:
	rm -f *.o a.out core fifteen log.txt
