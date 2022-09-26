#ifndef string_functions_h
#define string_functions_h

#include <iostream>
#include <vector>

std::string stringTolower(std::string word){
    for (size_t i = 0; i < word.length(); i++)
        word[i] = tolower(word[i]);

    return word;
}

std::vector<std::string> splitStringWithQuotes(std::string str) {
    std::vector<std::string> strings;
    std::string item;
    bool inWord = false;

    for (char c : str){
        if (c == '\''){
            inWord = !inWord;

            if (!inWord){
                strings.push_back(item);

                item.clear();
            } 

            continue;
        }

        if (inWord) item += c;
    }

    return strings;
}

std::vector<std::string> splitString(std::string str, std::string delimiter){
    std::vector<std::string> strings;
    int start = 0;
    int end = str.find(delimiter);

    while (end != -1){
        strings.push_back(str.substr(start, end - start));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }

    strings.push_back(str.substr(start, end - start));

    return strings;
}

std::string removeChar(std::string str, char ch){
    str.erase(remove(str.begin(), str.end(), ch), str.end());

    return str;
}

#endif