#ifndef _JSPATH_LOCATION_PATH_H
#define _JSPATH_LOCATION_PATH_H
#include "Expression.h"
namespace jspath
{
class LocationPath: public Expression
{
public:
    LocationPath(const std::string& path, bool isAbsolute = false);

    const std::string& getPath() const { return mPath; }

    bool isAbsolute() const { return mIsAbsolute; }
private:
    std::string mPath;
    bool mIsAbsolute;
};
}
#endif

