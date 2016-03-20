#include <boost/algorithm/string.hpp>
#include "WildcardLocationPath.h"

namespace jspath
{
    WildcardLocationPath::WildcardLocationPath(const std::string& path)
	:RegexLocationPath(wildcard2Regex(path))
    {}

    std::string WildcardLocationPath::wildcard2Regex(const std::string& wildcard)
    {
	std::string regex(wildcard);
	boost::replace_all(regex, "*", ".*");
	regex += '$';
	return regex;
    }

}

