#
# Makefile
#
# Computer Science 50
# Problem Set 3
#

fifteen: fifteen.c mySource.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o fifteen fifteen.c mySource.c -lm

test:test.c mySource.c
	clang -ggdb -Wall -Werror -o test test.c mySource.c

clean:
	rm -f *.o a.out core fifteen log.txt
