import csv
import sys


def main():

    # TODO: Check for command-line usage
    if not len(sys.argv) == 3: #If there are not three arguments
        print("Usage: csv_file txt_file")
        return 1 #return its an error

    # TODO: Read database file into a variable
    file = open(sys.argv[1], "r")
    reader = csv.DictReader(file)
    header = reader.fieldnames #the header contains the subsequences to look for

    # TODO: Read DNA sequence file into a variable
    dnaFile = open(sys.argv[2], "r")
    dna = dnaFile.readline()

    rows = [] #all rows in the file
    for row in reader:
        rows.append(row)

    # TODO: Find longest match of each STR in DNA sequence
    nums = [None]*len(header)
    for i in range(len(header)):
        for a in range (1, len(header)):
            nums[i] = longest_match(dna, header[i])


    '''for row in rows:
        #temp = row.split(',')
        #name = temp[0]
        name = row[header[0]]
        right = 0 #Keep track of how many matches
        for i in range(1, len(header)-1):
            num = longest_match(dna, header[i])
            if (int(num) == int(row[header[i]])):
                right+=1
            print(f"{num} found for {name}: does(n't) match {row[header[i]]}")
        if (right == len(header)-1):
            print(name)
            return'''

    # TODO: Check database for matching profiles
    for row in rows:
        name = row[header[0]]
        correct = True
        for i in range(1, len(header)):
            if (nums[i] != int(row[header[i]])):
                correct = False
                #print(f"{nums[i]} is not equal to {row[header[i]]}")
        if (correct):
            print(name)
            return
    print("No match")
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
