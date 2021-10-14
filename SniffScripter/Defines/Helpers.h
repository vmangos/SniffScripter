#ifndef _HELPERS_H
#define _HELPERS_H

#include "Common.h"
#include <string>

uint32 GetUInt32();
char GetChar();
std::string GetString(std::string defaultText);

std::string EscapeString(char* unescapedString);
std::string EscapeString(std::string unescapedString);

std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);

#endif