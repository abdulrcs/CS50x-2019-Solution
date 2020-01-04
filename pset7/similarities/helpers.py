from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    # Make a list of splitted version of a
    sx = a.split("\n")
    # Make a list of splitted version of b
    sy = b.split("\n")
    # Initialize a list for the line
    lines = list()

    x = set()
    # Add the split list into set
    for i in sx:
        x.add(i)

    y = set()
    # Add the split list into set
    for i in sy:
        y.add(i)
    # For every line in y
    for i in y:
        # Check if that current line is IN x, if do then append that i into list
        if i in x:
            lines.append(i)
    return lines


def sentences(a, b):
    """Return sentences in both a and b"""
    # Tokenize to sentences using nltk
    sx = sent_tokenize(a)
    sy = sent_tokenize(b)
    sentences = list()

    x = set()
    for i in sx:
        x.add(i)
    y = set()
    for i in sy:
        y.add(i)
    for i in y:
        if i in x:
            sentences.append(i)
    return sentences


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    suba = list()
    subb = list()
    substrings = list()
    # Loop through the length of a
    for i in range(len(a)):
        # If the length is same as n
        if len(a[i:n + i]) == n:
            # Add the substring into list of substring and remove spaces
            suba.append(a[i:n + i].strip(" "))
    for i in range(len(b)):
        # If the length is same as n
        if len(b[i:n + i]) == n:
            # Add the substring into list of substring and remove spaces
            subb.append(b[i:n + i].strip(" "))
    # Loop through the substring of a
    for i in suba:
        # If the current substring a is IN substring of b and also avoid duplicate
        if i in subb and i not in substrings:
            # Add that into the result of substring in common
            substrings.append(i)
    return substrings