//
//  main.cpp
//  AnagramFinder
//
//  Created by Alar Kirikal on 01/03/2019.
//  Copyright © 2019 Alar Kirikal. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>

#include <time.h>

#define NO_OF_CHARS 256

bool isAnagram(char* str1, char* str2)
{
    int count[NO_OF_CHARS] = { 0 };
    int i;

    for (i = 0; str1[i] && str2[i]; i++) {
        count[str1[i]]++;
        count[str2[i]]--;
    }

    if (str1[i] || str2[i])
        return false;

    // See if there is any non-zero value in count array
    for (i = 0; i < NO_OF_CHARS; i++)
        if (count[i])
            return false;
    return true;
}

int main(int argc, const char * argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    std::string key;
    for (int i = 2; i < argc; ++i) {
        if (i != 2)
        {
            key.append(" ");
        }

        key.append(argv[i]);
    }

    std::sort(key.begin(), key.end());
    char *keycstr = new char[key.length() + 1];
    strcpy(keycstr, key.c_str());

    // List
    std::string matches;
    std::string line;

    std::ifstream f((std::string(argv[1])));
    while (std::getline(f,line))
    {
        std::string::size_type pos = 0;
        while ((pos = line.find("\r",pos)) != std::string::npos)
        {
            line.erase(pos, 1);
        }

        if (line.length() != key.length()) continue;

        char *linecstr = new char[line.length() + 1];
        strcpy(linecstr, line.c_str());

        if (isAnagram(keycstr, linecstr))
        {
            matches.append(",");
            matches.append(line);
        }
    }

    // Time Stop
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    // Print result
    printf("%lld%s\n",microseconds, matches.c_str());

    return 0;
}
