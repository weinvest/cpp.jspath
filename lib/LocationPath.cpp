#include "LocationPath.h"

namespace jspath
{
LocationPath::LocationPath(const std::string& path, bool isAbsolute)
    :mPath(path)
    ,mIsAbsolute(isAbsolute)
{}
}

