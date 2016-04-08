#ifndef _JSPATH_2DOT_LOCATION_PATH_H
#define _JSPATH_2DOT_LOCATION_PATH_H
#include "LocationPath.h"
namespace jspath
{

class TwoDotLocationPath: public LocationPath
{
public:
    TwoDotLocationPath();

protected:
    void doApply(Context& cxt, const json& variables);
    void doApply(Context& cxt, const json& variables, const json& input);
};

}
#endif
