import csv
import sys


def main():
    sequence = []
    dna_ls = []
    str_tag = []
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Error! Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as file:
        reader = csv.reader(file)
        for row in reader:
            str_tag = row[1:]
            break
        print(str_tag)
        i = 0
        for row in reader:
            dict = {}
            for j in range(len(str_tag)):
                dict.update({str_tag[j]: row[j+1]})
            dna_ls.append({row[0]: dict})
            i += 1
    print(dna_ls)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        reader = csv.reader(file)
        k = 0
        for row in reader:
            dna_length = len(row[0])
            for k in range(dna_length):
                sequence.append(row[0][k])
                k += 1

    # TODO: Find longest match of each STR in DNA sequence
    str_match = {}
    for tag in str_tag:
        tag_ls = []
        for char in tag:
            tag_ls.append(char)
        str_match.update({tag: longest_match(sequence, tag_ls)})
    print(str_match)

    # TODO: Check database for matching profiles
    for i in range(len(dna_ls)):
        for tag in str_tag:
        dna_ls[i][tag]

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length
            # print(sequence[start:end])
            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
