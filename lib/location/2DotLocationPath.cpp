#include "location/2DotLocationPath.h"
#include "Context.h"
namespace jspath
{
TwoDotLocationPath::TwoDotLocationPath()
    :LocationPath("..")
{

}

void TwoDotLocationPath::doApply(Context &cxt)
{
    doApply(cxt, *cxt.getInput());
}

void TwoDotLocationPath::doApply(Context &cxt, const json& input)
{
    if(!input.is_array())
    {
        cxt.getOutput()->push_back(input);
    }

    if(!input.is_primitive())
    {
        for(auto& child : input)
        {
            doApply(cxt, child);
        }
    }
}
}
