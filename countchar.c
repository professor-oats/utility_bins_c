#include <stdio.h>

// Make a program that takes a string as input and counts the characters and then outputs the length when user press enter

int main(void) {
    char c;
    int i = 0;

    printf("Enter a string of chars to calculate the symbols:\n");
    while((c = getchar()) && c !='\n' && c != EOF) {
	i++;
    }

    printf("The amount of symbols in string is: %d\n", i);
    i = 0;
}
    
