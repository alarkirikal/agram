from datetime import datetime
from collections import Counter

import sys

def anagrams():
    lines = []

    key = " ".join(sys.argv[2:])
    arg_len = len(key)
    arg_counter = Counter(key)

    with open(sys.argv[1], encoding='ISO-8859-15') as file:
        for line in file:
            line = line.rstrip()

            if len(line) != arg_len:
                continue

            if Counter(line) == arg_counter:
                lines.append(line)

    return lines


if __name__ == "__main__":
    start = datetime.now()

    result = anagrams()

    end = datetime.now()
    print((end - start).microseconds, ",".join(result), sep=",")
