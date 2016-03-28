#include "compiler/Utils.h"

namespace jspath
{

size_t skipString(const std::string& input, size_t pos, size_t endPos)
{
    return skip2(input, pos, '"', endPos);
}

size_t skip2(const std::string& input, size_t pos, char c, size_t endPos)
{
    size_t escapeCount = 0;
    for(; pos < endPos; ++pos)
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

    return endPos;
}

size_t skip2Any(const std::string& input, size_t pos, const std::string& eodChars, size_t endPos)
{
    size_t escapeCount = 0;
    for(; pos < endPos; ++pos)
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

    return endPos;
}
}

