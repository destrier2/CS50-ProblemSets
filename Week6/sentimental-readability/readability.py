from cs50 import get_string
import re

#For further comments see readability.c (Week2)

text = get_string("Text: ")
words = 1
sentences = 0
charCount = 0

for i in range(len(text)):
    if (bool(re.match(r'\s', text[i]))):
        words+=1
    elif (text[i] == '.' or text[i] == '!' or text[i] == '?'):
        sentences+=1
    elif (bool(re.match(r'\w', text[i])) and not bool(re.match(r'\d', text[i]))):
        charCount+=1
l = charCount*100.0/words
s = sentences*100.0/words
index = 0.0588 * l - 0.296 * s - 15.8
if (index > 16):
    print("Grade 16+")
elif (index < 1):
    print("Before Grade 1")
else:
    print(f"Grade {int(index+0.5)}")