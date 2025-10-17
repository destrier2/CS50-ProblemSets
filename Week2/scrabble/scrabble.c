#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int getScore(string word);
int getCharScore(char c);

string alphabet = "abcdefghijklmnopqrstuvwxyz";
int values[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void) {
    string wordOne = get_string("Player 1: ");
    string wordTwo = get_string("Player 2: ");
    
    int one = getScore(wordOne);
    int two = getScore(wordTwo);
    if (one > two) {
        printf("Player 1 wins!\n");
    } else if (one == two) {
        printf("Tie!\n");
    } else {
        printf("Player 2 wins!\n");
    }

}

int getScore(string word){
    int score = 0;
    for (int i = 0 ; i < strlen(word); i++) {
        score+=getCharScore(word[i]);
    }
    return score;
}

int getCharScore(char c) {
    for(int i = 0; i < strlen(alphabet); i++) {
        if (alphabet[i] == tolower(c)) {
            return values[i];
        }
    }
    return 0;
}