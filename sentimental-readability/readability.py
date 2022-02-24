# TODO
text = input("Text: ")
num_letters = len(text)
num_words = 0
for char in text:
    if char == " ":
        num_words += 1
print(num_letters)
print(num_words)
