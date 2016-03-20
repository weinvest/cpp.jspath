#ifndef _JSPATH_LOCATION_PATH_H
#define _JSPATH_LOCATION_PATH_H
#include "Expression.h"
namespace jspath
{
    class LocationPath: public Expression
    {
    public:
	LocationPath(const std::string& path);

        const std::string& getPath() const { return mPath; }

    private:
	std::string mPath;
    };
}
#endif

