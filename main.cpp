//
//  main.cpp
//  AnagramFinder
//
//  Created by Alar Kirikal on 01/03/2019.
//  Copyright © 2019 Alar Kirikal. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <cstring>

#include <time.h>

#define NO_OF_CHARS 256

std::string ISO8859ToUTF8(const char *str)
{
    std::string utf8("");
    utf8.reserve(2*strlen(str) + 1);

    for (; *str; ++str)
    {
        if (!(*str & 0x80))
        {
            utf8.push_back(*str);
        } else
        {
            utf8.push_back(0xc2 | ((unsigned char)(*str) >> 6));
            utf8.push_back(0xbf & *str);
        }
    }
    return utf8;
}

bool isAnagram(const char* str1, char* str2)
{
    int count[NO_OF_CHARS] = { 0 };
    int i;

    for (i = 0; str1[i] && str2[i]; i++) {
        count[str1[i]]++;
        count[str2[i]]--;
    }

    if (str1[i] || str2[i])
        return false;

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

    const char* keycstr = key.c_str();

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

        std::string utf8line (ISO8859ToUTF8(line.c_str()));

        char *linecstr = new char[utf8line.length() + 1];
        strcpy(linecstr, utf8line.c_str());

        if (isAnagram(keycstr, linecstr))
        {
            matches.append(",");
            matches.append(linecstr);
        }
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    printf("%lld%s\n",microseconds, matches.c_str());
    return 0;
}
