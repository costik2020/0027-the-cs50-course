/**
 * hello-2.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Says hello to whomever.
 *
 * Demonstrates use of CS50's library and standard input.
 */
       
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("State your name: ");
    char name[20];
    scanf("%s",name); 
    printf("hello, %s\n", name);
}
