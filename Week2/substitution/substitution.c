#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void encode(string text, string key);
char encodeChar(char c, string key);

//Global variable: alphabet
string alphabet = "abcdefghijklmnopqrstuvwxyz";

int main(int argc, string argv[]) {
    if (argv[1] == NULL || strlen(argv[1]) != 26 || argc > 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    } else {
        for (int i = 0, n = strlen(argv[1]); i<n; i++) {
            if (argv[1][i] >= 65 && argv[1][i] <= 90) { //capital letter

            } else if (argv[1][i] >= 97 && argv[1][i] <= 122) { //lowercase letter
                
            } else {
                printf("Only include alphabetical characters in the key");
                return 1;
            }
        }

        for(int i = 0, n = strlen(argv[1]); i<n; i++) { //Check for duplicate characters
            for(int j = i+1; j<n; j++) {
                if (tolower(argv[1][i]) == tolower(argv[1][j])) {
                    printf("Don't include duplicate characters in the key\n");
                    return 1;
                }
            }
        }

        string text = get_string("plaintext: ");
        printf("ciphertext: ");
        encode(text, argv[1]);
    }
}

void encode(string text, string key) {
    char encoded[strlen(text)];
    for(int i = 0, n = strlen(text); i < n; i++) {
        encoded[i] = encodeChar(text[i], key);
    }
    encoded[strlen(text)] = '\0';
    printf("%s\n", encoded);
}

char encodeChar(char c, string key) {
    for(int i = 0; i < 26; i++) {
        if (alphabet[i] == c) {
            return tolower(key[i]);
        } else if (toupper(alphabet[i]) == c) {
            return toupper(key[i]);
        }
    }
    return c; //If not in the alphabet, return unchanged character
}