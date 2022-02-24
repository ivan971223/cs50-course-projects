# TODO
text = input("Text: ")
num_letters = 0
num_words = 0
for char in text:
    if char == " ":
        num_words += 1
    else:
        num_letters += 1
print(num_letters)
print(num_words)
