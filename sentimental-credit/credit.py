# TODO
import sys

number = input("Number: ")
length = len(number)
if length != 15 and length != 13 and length != 16:
    print("INVALID")
    sys.exit(1)

digit_ls = []
for digit in number:
    digit = int(digit)
    if(digit >= 1 or digit <= 9):
        digit_ls.append(digit)
    else:
        print("INVALID")
        sys.exit(1)


digit_sum = 0
for digit in digit_ls[-2::-2]:
    two_digit = digit*2
    if two_digit > 9:
        digit_sum += 1+(two_digit-10)
    else:
        digit_sum += two_digit
for digit in digit_ls[::-2]:
    digit_sum += digit

while digit_sum >= 10:
    digit_sum -= 10
last_digit = digit_sum

if last_digit == 0:
    if number[0:2] == "34" or number[0:2] == "37":
        print("AMEX")
        sys.exit(0)
    elif number[0:2] == "51" or number[0:2] == "52" or number[0:2] == "53" or number[0:2] == "54" or number[0:2] == "55":
        print("MASTERCARD")
        sys.exit(0)
    elif number[0] == "4":
        print("VISA")
        sys.exit(0)
    else:
        sys.exit(1)
else:
    print("INVALID")
    sys.exit(1)
