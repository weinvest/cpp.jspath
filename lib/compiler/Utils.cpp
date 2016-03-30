#include <stdexcept>
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

bool matchRange(std::stack<char>& unmatched, const std::string& input, size_t& fromPos, size_t endPos)
{
    char c = input[fromPos];
    switch (c)
    {
    case '(':
    case '[':
    case '{':
        unmatched.push(c);
        break;
    case ')':
        if(unmatched.empty() || '(' != unmatched.top())
        {
            throw std::logic_error("')' unmatched");
        }
        else
        {
            unmatched.pop();
        }
        break;
    case ']':
        if(unmatched.empty() || '[' != unmatched.top())
        {
            throw std::logic_error("']' unmatched");
        }
        else
        {
            unmatched.pop();
        }
        break;
    case '}':
        if(unmatched.empty() || '{' != unmatched.top())
        {
            throw std::logic_error("'}' unmatched");
        }
        else
        {
            unmatched.pop();
        }
        break;
    case '"':
        {
            auto toPos = skipString(input, fromPos + 1, endPos);
            if(toPos >= endPos)
            {
                throw std::logic_error("'\"' not found");
            }
            fromPos = toPos;
        }
        break;

    default:
        return false;
    };
    return true;
}

size_t skipSpace(const std::string& input, size_t pos, size_t endPos)
{
    while(pos < endPos && std::isspace(input[pos]))
    {
        ++pos;
    }

    return pos;
}

void unpackBrackets(const std::string& input, size_t& fromPos, size_t& endPos)
{
    fromPos = kipSpace(input, pos, endPos);
    while(fromPos < endPos && 'c' == input.at(fromPos))
    {
        while(endPos > fromPos && std::isspace(input[endPos]))
        {
            --endPos;
        }

        if(')' == input[endPos])
        {
            --endPos;
            ++fromPos;
            skipSpace(input, fromPos, endPos);
        }
        else
        {
            break;
        }
    }
}
}
