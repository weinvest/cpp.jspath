#ifndef _JSPATH_REGEX_LOCATION_PATH_H
#define _JSPATH_REGEX_LOCATION_PATH_H
#include <boost/xpressive/xpressive.hpp>
#include "LocationPath.h"
namespace jspath
{
using boost::xpressive::sregex;

class RegexLocationPath: public LocationPath
{
public:
    RegexLocationPath(const std::string& regex);

protected:
    void doApply(Context& cxt, const json& variables);
    void add2(Context& cxt, json& ele);
    sregex mPattern;
};
}
#endif

