from cs50 import get_int

height = get_int("Height: ")
if (height < 1 or height > 8):
    height = get_int("Height: ")
for i in range(height):
    for a in range(height-i-1):
        print(" ", end="")
    for a in range(i+1):
        print("#", end="")
    print("  ", end="")
    for a in range(i+1):
        print("#", end="")
    print("")