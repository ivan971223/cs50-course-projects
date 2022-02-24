# TODO
from cs50 import get_int

height = get_int("Height: ")
while height < 1 or height > 8:
    height = get_int("Height: ")
for i in range(1, height+1):
    for x in range(height-i):
        print(" ", end="")
    for y in range(i):
        print("#", end="")
    for h in range(2):
        print(" ", end="")
    for k in range(i):
        print("#", end="")
    print("")
