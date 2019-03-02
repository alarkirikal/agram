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

std::string UTF8toISO8859_1(const char * in) {
    std::string out;
    if (in == NULL)
        return out;

    unsigned int codepoint;
    while (*in != 0) {
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

        if (((*in & 0xc0) != 0x80) && (codepoint <= 0x10ffff)) {
            char outc;
            if (codepoint <= 255) {
                if (codepoint != 0xa4 && codepoint != 0xa6 && codepoint != 0xa8
                    && codepoint != 0xb4 && codepoint != 0xb8 && codepoint != 0xbc
                    && codepoint != 0xbd && codepoint != 0xbe) {
                    outc = static_cast<char>(codepoint);
                }
                else {
                    outc = '?';
                }
            }
            else {
                if (codepoint == 0x20AC) {
                    outc = 0xa4;
                }
                else if (codepoint == 0x0160) {
                    outc = 0xa6;
                }
                else if (codepoint == 0x0161) {
                    outc = 0xa8;
                }
                else if (codepoint == 0x017d) {
                    outc = 0xb4;
                }
                else if (codepoint == 0x017e) {
                    outc = 0xb8;
                }
                else if (codepoint == 0x0152) {
                    outc = 0xbc;
                }
                else if (codepoint == 0x0153) {
                    outc = 0xbd;
                }
                else if (codepoint == 0x0178) {
                    outc = 0xbe;
                }
                else {
                    outc = '?';
                }
            }
            out.append(1, outc);
        }
    }
    return out;
}

bool isAnagram(const char* str1, const char* str2)
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

    const char* keycstr = UTF8toISO8859_1(key.c_str()).c_str();

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

        if (isAnagram(keycstr, line.c_str()))
        {
            matches.append(",");
            matches.append(line);
        }
    }

    const char* convertedMatches = ISO8859ToUTF8(matches.c_str()).c_str();

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    printf("%lld%s\n",microseconds, convertedMatches);
    return 0;
}
