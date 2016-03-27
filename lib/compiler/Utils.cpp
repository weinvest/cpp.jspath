#include "compiler/Utils.h"

namespace jspath
{

size_t skipString(const std::string& input, size_t pos)
{
    return skip2(input, pos, '"');
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

size_t skip2(const std::string& input, size_t pos, char c, size_t defEndPos)
{
    size_t escapeCount = 0;
    for(; pos < input.length(); ++pos)
    {
        char cc = input[pos];
        if(cc == c && (0 == (escapeCount % 2)))
        {
            return pos;
        }
        else if('\\' == cc)
        {
            ++escapeCount;
        }
        else
        {
            escapeCount = 0;
        }
    }

    return defEndPos;
}

size_t skip2Any(const std::string& input, size_t pos, const std::string& eodChars, size_t defEndPos)
{
    size_t escapeCount = 0;
    for(; pos < input.length(); ++pos)
    {
        char cc = input[pos];
        if((std::string::npos != eodChars.find(cc)) && (0 == (escapeCount % 2)))
        {
            return pos;
        }
        else if('\\' == cc)
        {
            ++escapeCount;
        }
        else
        {
            escapeCount = 0;
        }
    }

    return defEndPos;
}
}

