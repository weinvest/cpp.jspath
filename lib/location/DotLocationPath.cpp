#include "location/DotLocationPath.h"
#include "Context.h"
namespace jspath
{
DotLocationPath::DotLocationPath(const std::string& path)
    :LocationPath(path)
{}

void DotLocationPath::doApply(Context& cxt, const json& input)
{
    if(input.is_array())
    {
        for(auto& child : input)
        {
            if(child.count(getPath()))
            {
                cxt.getOutput().push_back(&child[getPath()]);
            }
        }
    }
    else if(input.is_object())
    {
        if(input.count(getPath()))
        {
            cxt.getOutput().push_back(&input[getPath()]);
        }
    }
}
}

