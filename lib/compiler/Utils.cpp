#include <stdexcept>
#include <algorithm>
#include <boost/xpressive/xpressive.hpp>
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
    fromPos = skipSpace(input, fromPos, endPos);
    while(fromPos < endPos && '(' == input.at(fromPos))
    {
        while(endPos > fromPos && std::isspace(input[endPos - 1]))
        {
            --endPos;
        }

        if(')' == input[endPos - 1])
        {
            --endPos;
            ++fromPos;
            fromPos = skipSpace(input, fromPos, endPos);
        }
        else
        {
            break;
        }
    }
}

bool isMatch(const std::string& str, const std::string& pattern, bool caseInsensitive)
{
    using namespace boost::xpressive;
    sregex regex;
    if(caseInsensitive)
    {
        regex = icase(pattern);
    }
    else
    {
        regex = sregex::compile(pattern);
    }

    smatch what;
    if(regex_match(str, what, regex))
    {
        return true;
    }

    return false;
}

bool iequal(const std::string& str, size_t from, size_t to, const std::string& str2)
{
    if((to - from) == str2.length())
    {
        size_t iFirst = from, iSecond = 0;
        for(; iFirst < to; ++iFirst, ++iSecond)
        {
            char c1 = str[iFirst];
            char c2 = str2[iSecond];
            if((c1 != c2) && std::toupper(c1) != std::toupper(c2))
            {
                return false;
            }
        }

        return true;
    }
    return false;
}

static const std::string trueLexical("true");
static const std::string falseLexical("false");
bool isBool(const std::string& str, size_t from, size_t to)
{
    if(to == (1 + from))
    {
        if('1' == str[from])
        {
            return true;
        }

        if('0' == str[0])
        {
            return true;
        }
    }
    else if(iequal(str, from, to, trueLexical))
    {
        return true;
    }
    else if(iequal(str, from, to, falseLexical))
    {
        return true;
    }

    return false;
}

bool isInt(const std::string& str, size_t from, size_t to)
{
    if(from < to)
    {
        if('+' == str[from] || '-' == str[to])
        {
            ++from;
        }

        return std::all_of(str.begin() + from, str.begin() + to, [](char c) { return std::isdigit(c);});
    }

    return false;
}

bool isReal(const std::string& str, size_t from, size_t to)
{
    if(from < to)
    {
        if('+' == str[from] || '-' == str[to])
        {
            ++from;
        }

        for(; from < to && std::isdigit(str[from]); ++from)
        {}

        if(from < to && '.' == str[from])
        {
            ++from;
        }
        return std::all_of(str.begin() + from, str.begin() + to, [](char c) { return std::isdigit(c);});
    }

    return false;
}

bool convert2Bool(const std::string& str, size_t from, size_t to)
{
    if(1 == str.length())
    {
        if('1' == str[0])
        {
            return true;
        }

        if('0' == str[0])
        {
            return false;
        }
    }
    else if(iequal(str, from, to, trueLexical))
    {
        return true;
    }
    else if(iequal(str, from, to, falseLexical))
    {
        return false;
    }

    throw std::logic_error(str + " could not be interpreted as bool");
}

int convert2Int(const std::string& str, size_t from, size_t to)
{
    int value = 0, sign = 1;
    if('-' == str.at(from))
    {
        sign = -1;
        ++from;
    }
    else if('+' == str.at(from))
    {
        ++from;
    }

    for(; from < to && std::isdigit(str.at(from)); ++from)
    {
        value *= 10;
        value += (str.at(from) - '0');
    }
    value *= sign;

    if(from == to)
    {
        return value;
    }
    throw std::logic_error(str + " could not be interpreted as int");
}

double convert2Real(const std::string& str, size_t from, size_t to)
{
    double value = 0.0, sign = 1.0, bits = 1.0;
    if('-' == str[from])
    {
        sign = -1.0;
        ++from;
    }
    else if('+' == str[from])
    {
        ++from;
    }

    for(; from < to && std::isdigit(str[from]); ++from)
    {
        value *= 10.0;
        value += (str[from] - '0');
    }

    if(from < to && '.' == str[from])
    {
        ++from;
    }

    for(; from < to && std::isdigit(str[from]); ++from)
    {
        bits *= 10.0;
        value *= 10.0;
        value += (str[from] - '0');
    }

    value *= sign;

    if(from == to)
    {
        return value / bits;
    }

    throw std::logic_error(str + " could not be interpreted as real");
}
}
