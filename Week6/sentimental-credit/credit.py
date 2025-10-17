from cs50 import get_string
from re import fullmatch
from array import array 

number = get_string("Number: ")
while (bool(fullmatch(r'^\d+$', number)) == False):
    number = get_string("Number")

digits = [None]*len(number)
for i in range (len(number)):
    digits[i] = int(number[i])
#Get the sum from every other digit, starting with the second-to last digit
sum = 0
for i in range(len(number)-2, -2, -2):
    if (i > -1) :
        tempTwo = digits[i]*2
        if (tempTwo >= 10):
            temp = str(tempTwo) #convert to string
            sum += int(temp[0]) + int(temp[1])
        else:
            sum += tempTwo
#Get sum of the rest of the digits
for i in range (len(number)-1, -2, -2):
    if (i > -1):
        sum += digits[i]
valid = False #set a boolean to false (turn true if proven valid)
if (sum % 10 == 0):
    if (digits[0] == 4):
        if ((len(number) == 13 or len(number) == 16)):
            print("VISA")
            valid = True
    elif (digits[0] == 3 and len(number) == 15):
        if (digits[1] == 4 or digits[1] == 7):
            print("AMEX")
            valid = True
    elif (digits[0] == 5 and len(number) == 16) :
        if (digits[1] > 0 and digits[1] < 6) :
            print("MASTERCARD")
            valid = True
if (not valid):
    print("INVALID")