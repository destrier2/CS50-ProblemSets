#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void) {
    string text = get_string("Text: ");
    //Count words & sentences
    int words = 1;
    int sentences = 0;
    int charCount = 0; // to calculate the average length of each word

    for(int i = 0; i < strlen(text); i++) {
        if (text[i] == ' ') {
            words++;
        } else if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            sentences++;
        } else if (text[i] != ',' && text[i] != '0' && text[i] != '1' && text[i] != '2' && text[i] != '3' && text[i] != '4' && text[i] != '5' && text[i] != '6' && text[i] != '7' && text[i] != '8' && text[i] != '9' && text[i] != '-' && text[i] != '"' && text[i] != '\'' && text[i] != ';' && text[i] != ':' && text[i] != '(' && text[i] != ')' && text[i] != "'" ) {
            charCount++;
        }
    }

    //printf("%d words, %d sentences, and %d characters in total\n", words, sentences, charCount);
    double l = (charCount*100.0/words);
    double s = (sentences*100.0/words);
    double index = 0.0588 * l - 0.296 * s - 15.8;
    //printf("L is %f and s is %f\n", l, s);
    if (index > 16) {
        printf("Grade 16+\n");
    } else if (index < 1) {
        printf("Before Grade 1\n");
    } else {
        printf("Grade %d\n", (int)(index+0.5));
    }
    // L is the average number of letters per 100 words in the text
    // S is the average number of sentences per 100 words in the text
}