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
    size_t skip2MatchParenthesis(std::stack<char>& unmatched, const std::string& input, size_t pos, size_t endPos);
    void unpackBrackets(const std::string& input, size_t& fromPos, size_t& endPos);
    bool matchRange(std::stack<char>& unmatched, const std::string& input, size_t& pos, size_t endPos);
    bool isMatch(const std::string& str, const std::string& pattern, bool caseInsensitive = false);

    bool iequal(const std::string& str, size_t from, size_t to, const std::string& str2);
    bool isBool(const std::string& str, size_t from, size_t to);
    bool isInt(const std::string& str, size_t from, size_t to);
    bool isReal(const std::string& str, size_t from, size_t to);
    bool isSpace(const std::string& str, int& from, int to, int step);

    bool convert2Bool(const std::string& str, size_t from, size_t to);
    int convert2Int(const std::string& str, size_t from, size_t to);
    double convert2Real(const std::string& str, size_t from, size_t to);
}

#endif
