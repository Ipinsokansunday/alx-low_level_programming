#include <stdio.h>

/**
 * Purpose a program that prints the alphabet in lowercase, 
 * and then in uppercase, followed by a new line.
 * main - Entry poin
 * Return 0 each time
 */

int main(void) 
{
    char x = 'a';
    char X = 'A';

    while (x <= 'z') 
    {
        putchar(x);
        x++;
    }

    while (X <= 'Z') 
    {
        putchar(X);
        X++;
    }

    putchar('\n');

    return 0;
}
