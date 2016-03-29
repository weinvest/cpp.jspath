#ifndef _JSPATH_ROOT_LOCATION_PATH
#define _JSPATH_ROOT_LOCATION_PATH
#include "LocationPath.h"
namespace jspath
{
class RootLocationPath: public LocationPath
{
public:
    RootLocationPath();

protected:
    void doApply(Context& cxt) override;
};
}
#endif
