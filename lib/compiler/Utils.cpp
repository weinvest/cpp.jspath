#include "compiler/Utils.h"

namespace jspath
{

size_t SkipString(const std::string& input, size_t pos)
{
	return Skip2(input, pos, '"');
//    size_t escapeCount = 0;
//    for(; pos < input.length(); ++pos)
//    {
//        char c = input[pos];
//        if('"' == c && (0 == (escapeCount % 2)))
//        {
//            return pos + 1;
//        }
//        else if('\\' == c)
//        {
//            ++escapeCount;
//        }
//        else
//        {
//            escapeCount = 0;
//        }
//    }
//
//    return std::string::npos;
}

size_t Skip2(const std::string& input, size_t pos, char c)
{
    size_t escapeCount = 0;
    for(; pos < input.length(); ++pos)
    {
        char c = input[pos];
        if(c == c && (0 == (escapeCount % 2)))
        {
            return pos + 1;
        }
        else if('\\' == c)
        {
            ++escapeCount;
        }
        else
        {
            escapeCount = 0;
        }
    }

    return std::string::npos;
}
}

