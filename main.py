from datetime import datetime
from collections import Counter

import sys

def anagrams():
    retval = []

    key = " ".join(sys.argv[2:])
    arg_len = len(key) + 1
    arg_counter = Counter(key)

    with open(sys.argv[1], encoding='ISO-8859-15') as file:
        for line in file:
            if len(line) != arg_len:
                continue

            line = line.rstrip()

            if Counter(line) == arg_counter:
                retval.append(line)

    return ",".join(retval)


if __name__ == "__main__":
    start = datetime.now()

    result = anagrams()

    end = datetime.now()
    print(str((end - start).microseconds) + "," + result)
