#ifndef _HELPERS_H
#define _HELPERS_H

#include "Defines\Common.h"
#include <string>

uint32 GetUInt32();
char GetChar();
std::string GetString(std::string defaultText);

std::string EscapeString(char* unescapedString);
std::string EscapeString(std::string unescapedString);

#endif