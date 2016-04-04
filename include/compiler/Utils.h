#ifndef _JSPATH_COMPILER_UTILS_H
#define _JSPATH_COMPILER_UTILS_H
#include <string>
#include <stack>
namespace jspath
{
    size_t skipString(const std::string& input, size_t pos, size_t endPos);
    size_t skip2(const std::string& input, size_t pos, char c, size_t endPos);
    size_t skip2Any(const std::string& input, size_t pos, const std::string& eodChars, size_t endPos);
    size_t skipSpace(const std::string& input, size_t pos, size_t endPos);
    void unpackBrackets(const std::string& input, size_t& fromPos, size_t& endPos);
    bool matchRange(std::stack<char>& unmatched, const std::string& input, size_t& pos, size_t endPos);
    bool isMatch(const std::string& str, const std::string& pattern, bool caseInsensitive = false);
}

#endif
