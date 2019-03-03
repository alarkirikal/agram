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

#define NO_OF_CHARS 256

bool isAnagram(const char* str1, const wchar_t* str2)
{
    int count[NO_OF_CHARS] = { 0 };
    int i;

    for (i = 0; str1[i] && str2[i]; i++)
    {
        count[str1[i]]++;
        count[str2[i]]--;
    }

    if (str1[i] || str2[i])
    {
        return false;
    }

    for (i = 0; i < NO_OF_CHARS; i++)
    {
        if (count[i])
        {
            return false;
        }
    }

    return true;
}

int main(int argc, const char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    std::locale::global(std::locale("en_US.utf8"));

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

    std::wifstream file;
    file.imbue(std::locale("en_US.utf8"));  // Maybe de_DE@euro or de_DE.ISO8859-15
    file.open((std::string(argv[1])));
    std::wstring line;

    while (std::getline(file,line))
    {
        line.erase(line.length() - 1, 1);

        if (isAnagram(keycstr, line.c_str()))
        {
            matches.append(",");
            std::wcout << "Found match: " << line << std::endl;
        }
    }

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    printf("%lld%s\n",microseconds, matches.c_str());
    return 0;
}
