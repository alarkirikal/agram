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

std::string UTF8toISO8859_1(const char * in)
{
    std::string out;
    if (in == NULL)
        return out;

    unsigned int codepoint;
    while (*in != 0)
    {
        unsigned char ch = static_cast<unsigned char>(*in);
        if (ch <= 0x7f)
            codepoint = ch;
        else if (ch <= 0xbf)
            codepoint = (codepoint << 6) | (ch & 0x3f);
        else if (ch <= 0xdf)
            codepoint = ch & 0x1f;
        else if (ch <= 0xef)
            codepoint = ch & 0x0f;
        else
            codepoint = ch & 0x07;
        ++in;
        if (((*in & 0xc0) != 0x80) && (codepoint <= 0x10ffff))
        {
            if (codepoint <= 255)
            {
                out.append(1, static_cast<char>(codepoint));
            }
        }
    }

    return out;
}

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

    std::string isoKey ( UTF8toISO8859_1(key.c_str()) );

    std::sort(isoKey.begin(), isoKey.end());
    char *keycstr = new char[key.length() + 1];
    strcpy(keycstr, isoKey.c_str());

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

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    printf("%lld%s\n",microseconds, matches.c_str());
    return 0;
}
