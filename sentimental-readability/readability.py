# TODO
import string

text = input("Text:")
num_letters = 0
num_words = 0
num_sentences = 0
alpha_ls = list(string.ascii_lowercase)

for char in text:
    char = char.lower()
    if char == " ":
        num_words += 1
    elif char == "." or char=="!" or char=="?":
        num_sentences += 1
    elif char in alpha_ls:
        num_letters += 1

index = round(0.0588 * num_letters/100 - 0.296 * num_sentences/100 - 15.8)
a = 0.0588 * num_letters/100
b = 0.296 * num_sentences/100
print(a)
print(b)
print(a-b)
print(index)
print(num_letters)
print(num_words)
print(num_sentences)
