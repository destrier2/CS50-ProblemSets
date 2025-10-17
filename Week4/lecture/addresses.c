#include <stdio.h>
#include <string.h>
#include <stdlib.h> //Allows malloc
#include <ctype.h>

int main(void) {
    /*
    int n = 50;
    printf("%i\n", n);
    int *p = &n; //Make it an address of an integer (not the integer)
    printf("%p\n", p);
    printf("%p\n", &n);
    printf("%i\n", *p); //Actually go to the location of the integer
    */
    /*
    char *one = "AB";
    char *two = "BA";
    printf("%i\n", strcmp(one, two));
    */

    //To copy a string: (OR just use strlen(destination, source);)
    /*
    char *s = "hello World";
    char *t = malloc(strlen(s)+1); //Allocate space in memory for this data (include the )
    if (t == NULL) { //If malloc doesn't have any space in memory
        return 1; 
    }
    for (int i = 0, n = strlen(s); i < n; i++) { //Copy all of s into t
        t[i] = s[i];
    }
    if (strlen(s) > 0) {
        t[0] = toupper(t[0]); //Capitalize first character of t and t only (not s as well)
    }
    printf("S is %s\n", s);
    printf("T is %s\n", t);

    free(t); //Return the memory to the computer
    */

    /*
    int *x = malloc(3*sizeof(int)); //Allocate space for 3 integers
    x[0] = 72;
    x[1] = 73;
    x[2] = 33;
    free(x);
    */

    char *s;
    printf("s: "); //Prompt user for input
    scanf("%s", s); //Read in a string
    printf("s: %s\n", s);
}