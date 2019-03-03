from datetime import datetime
from collections import Counter

import sys


def anagrams():
    retval = []
    append = retval.append

    key = " ".join(sys.argv[2:]).replace("ž", "þ")
    arg_len = len(key) + 1
    arg_counter = Counter(key)

    with open(sys.argv[1], encoding='iso-8859-15') as file:
        for line in file:
            if len(line) != arg_len:
                continue

            line = line.rstrip()

            if Counter(line) == arg_counter:
                append(line)

    return ",".join(retval).replace("þ", "ž")


if __name__ == "__main__":
    start = datetime.now()
    result = anagrams()
    end = datetime.now()

    print("{0},{1}".format(str((end - start).microseconds), result))
