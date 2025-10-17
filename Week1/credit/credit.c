#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdbool.h>

int countLength (long number) {
    int count = 0;
    while (number != 0) {
        number /= 10;
        count++;
    }
    return count;
}

void getDigits (long number, int length, int digits[]) {
    long temp = number;
    for (int i = 0; i < length; i++) {
        digits[i] = temp % 10;
        temp -= digits[i];
        temp /= 10;
    }
}

int main(void) {
    long number = get_long("Number: ");
    int length = countLength(number);
    int digits[length];
    getDigits(number, length, digits);
    //Get the sum of every other digit starting with the number's second-to-last digit
    int sum = 0;
    for (int i = 1; i < length; i +=2) {
        int tempTwo = digits[i]*2;
        if (tempTwo >= 10) {
            int tempArray[countLength(tempTwo)]; //Even though length must be 2
            getDigits(tempTwo, countLength(tempTwo), tempArray);
            for(int j = 0; j < countLength(tempTwo); j++) {
                sum += tempArray[j];
            }
        } else {
            sum += tempTwo;
        }
    }
    for(int i = 0; i < length; i +=2) {
        sum += digits[i];
    }
    bool valid = false;
    if (sum % 10 == 0) {
        if (digits[length-1] == 4 && (length == 13 || length == 16)) { //Visa number
            printf("VISA\n");
            valid = true;
        } else if (digits[length-1] == 3 && length == 15) {
            if (digits[length-2] == 4 || digits[length-2] == 7) {
                printf("AMEX\n");
                valid = true;
            }
        } else if (digits[length-1] == 5 && length == 16) {
            if (digits[length-2] > 0 && digits[length-2] < 6) {
                printf("MASTERCARD\n");
                valid = true;
            }
        }
    } 
    if (!valid) {
        printf("INVALID\n");
    }
}