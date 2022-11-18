#
# Makefile
#
# Computer Science 50
# Problem Set 3
#

all: find generate

test:test.c mySource.c
	clang -ggdb -Wall -Werror -o test test.c mySource.c

find: find.c helpers.c helpers.h
	clang -ggdb -Wall -Werror -o find find.c helpers.c mySource.c -lm

generate: generate.c
	clang -ggdb -Wall -Werror -o generate generate.c mySource.c

clean:
	rm -f *.o a.out core find generate
