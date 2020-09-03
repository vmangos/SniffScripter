#include "Defines\Common.h"
#include "Defines\Helpers.h"
#include "Database\Database.h"
#include <iostream>

uint32 GetUInt32()
{
    uint32 value = 0;
    scanf("%u", &value);
    return value;
}

char GetChar()
{
    fseek(stdin, 0, SEEK_END);
    char const chr = getchar();
    fseek(stdin, 0, SEEK_END);
    return chr;
}

std::string GetString(std::string defaultText)
{
    std::string text;
    fseek(stdin, 0, SEEK_END);
    getline(std::cin, text);
    fseek(stdin, 0, SEEK_END);
    if (text.empty())
        return defaultText;
    return text;
}

std::string EscapeString(char* unescapedString)
{
    char* escapedString = new char[strlen(unescapedString) * 2 + 1];
    mysql_escape_string(escapedString, unescapedString, strlen(unescapedString));
    std::string returnString = escapedString;
    delete[] escapedString;
    return returnString;
}

std::string EscapeString(std::string unescapedString)
{
    char* escapedString = new char[unescapedString.length() * 2 + 1];
    mysql_escape_string(escapedString, unescapedString.c_str(), unescapedString.length());
    std::string returnString = escapedString;
    delete[] escapedString;
    return returnString;
}