# TODO
text = input("Text: ")
num_letters = 0
num_words = 0
num_sentences = 0

for char in text:
    char = char.lower()
    if char == " ":
        num_words += 1
    elif char == "." or char=="!" or char=="?":
        num_sentences += 1
    else:
        num_letters += 1

print(num_letters)
print(num_words)
print(num_sentences)
