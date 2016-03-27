#ifndef _JSPATH_COMPILER_UTILS_H
#define _JSPATH_COMPILER_UTILS_H
#include <string>
namespace jspath
{
    size_t skipString(const std::string& input, size_t pos);
    size_t skip2(const std::string& input, size_t pos, char c, size_t defEndPos = std::string::npos);
    size_t skip2Any(const std::string& input, size_t pos, const std::string& eodChars, size_t defEndPos);
}
#endif

