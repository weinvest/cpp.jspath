#ifndef _JSPATH_DOT_LOCATION_PATH_H
#define _JSPATH_DOT_LOCATION_PATH_H
#include "LocationPath.h"
namespace jspath
{
class DotLocationPath: public LocationPath
{
public:
    DotLocationPath(const std::string& path);

protected:
    void doApply(Context& cxt) override;

};
}
#endif

