/**
 * adder.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Adds two numbers.
 *
 * Demonstrates use of CS50's library.
 */
       

#include <stdio.h>

int main(void)
{
    // ask user for input 
    printf("Give me an integer: ");
    int x ;
	scanf("%i",&x);
    printf("Give me another integer: ");
    int y ;
	scanf("%i",&y);

    // do the math
    printf("The sum of %i and %i is %i!\n", x, y, x + y);
}
