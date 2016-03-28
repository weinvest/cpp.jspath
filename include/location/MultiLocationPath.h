#ifndef _JSPATH_MULTI_LOCATION_PATH_H
#define _JSPATH_MULTI_LOCATION_PATH_H
#include "LocationPath.h"

namespace jspath
{

class MultiLocationPath: public LocationPath
{
public:
    MultiLocationPath();
    void addChild(std::shared_ptr<Expression> pChild);
    void apply(Context& cxt) override;

protected:
    void doApply(Context &cxt, const json &input);

    std::vector<std::shared_ptr<Expression>> mChildren;
};
}
#endif
