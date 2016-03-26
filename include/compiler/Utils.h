#ifndef _JSPATH_COMPILER_UTILS_H
#define _JSPATH_COMPILER_UTILS_H
#include <string>
namespace jspath
{
    size_t SkipString(const std::string& input, size_t pos);
    size_t Skip2(const std::string& input, size_t pos, char c);
}
#endif

