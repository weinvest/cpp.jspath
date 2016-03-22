#include "location/2DotLocationPath.h"
#include "Context.h"
namespace jspath
{
TwoDotLocationPath::TwoDotLocationPath()
    :LocationPath("..")
{

}

void TwoDotLocationPath::doApply(Context &cxt, const boost::property_tree::ptree &input)
{
    cxt.getOutput().push_back(&input);

    for(auto& child : input)
    {
        doApply(cxt, child.second);
    }
}

}
