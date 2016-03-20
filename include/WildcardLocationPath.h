#ifndef _JSPATH_WIILDCARD_LOCATION_PATH_H
#define _JSPATH_WIILDCARD_LOCATION_PATH_H
#include "RegexLocationPath.h"
namespace jspath
{
    class WildcardLocationPath: public RegexLocationPath
    {
    public:
	WildcardLocationPath(const std::string& path);

    private:
	std::string wildcard2Regex(const std::string& wildcard);
    };
}
#endif

