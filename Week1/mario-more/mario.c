#include <stdio.h>
#include <cs50.h>

int main(void) {
    int height = get_int("Height: ");
    while (height <= 0 || height > 8) {
        height = get_int("Height: ");
    }

    for (int i = 0; i < height; i++) {
        for(int a = 0; a < height-i-1; a++) {
            printf(" ");
        }
        for (int a = 0; a <= i; a++) {
            printf("#");
        }
        printf("  ");
        for(int a = 0; a <= i; a++) {
            printf("#");
        }
        printf("\n");
        //printf("%*c%  -*c\n", height, '#', height, '#');
    }
}