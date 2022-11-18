/**
 * compare-0.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Tries (and fails) to compare two strings.
 *
 * Demonstrates strings as pointers to arrays.
 */
       
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // get line of text
    printf("Say something: ");
    char * s ;
    s=malloc(sizeof(char)*20);
    scanf("%s",s);
 
    // get another line of text
    printf("Say something: ");
    char * t;
    t=malloc(sizeof(char)*20);
    scanf("%s",t);
 
    // try (and fail) to compare strings
    if (s == t)
    {
        printf("You typed the same thing!\n");
    }
    else
    {
        printf("You typed different things!\n");
    }
}
