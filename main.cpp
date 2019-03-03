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
#include <string>
#include <codecvt>
#include <locale>

#define NO_OF_CHARS 256

bool isAnagram(const char* str1, const char* str2)
{
    int count[NO_OF_CHARS] = { 0 };
    int i;

    for (i = 0; str1[i] && str2[i]; i++)
    {
        count[str1[i]]++;
        count[str2[i]]--;
    }

    if (str1[i] || str2[i])
        return false;

    for (i = 0; i < NO_OF_CHARS; i++)
    {
        if (count[i])
        {
            return false;
        }
    }

    return true;
}

std::string wstr_to_utf8( const std::wstring& utf16 ) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t> > wcu8;
    return wcu8.to_bytes(utf16);
}

int main(int argc, const char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t> > wcu8;

    std::string key;
    for (int i = 2; i < argc; ++i) {
        if (i != 2)
        {
            key.append(" ");
        }

        key.append(argv[i]);
    }

    std::string matches;
    std::wifstream file;
    file.open(std::string(argv[1]));
    std::wstring line;

    while (std::getline(file,line))
    {
        line.erase(line.length() - 1, 1);

        std::string utf8line ( wcu8.to_bytes(line) );

        if (isAnagram(key.c_str(), utf8line.c_str()))
        {
            matches.append(",");
            matches.append(utf8line);
        }
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    printf("%lld%s\n",microseconds, matches.c_str());
    return 0;
}
