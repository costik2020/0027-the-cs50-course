/**
 * argv-1.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Prints command-line arguments, one per line.
 *
 * Demonstrates use of argv.
 */


#include <stdio.h>

int main(int argc, char* argv[])
{
    // print arguments
    for (int i = 0; i < argc; i++)
    {
        printf("%s \n", argv[i]);
    }
}
