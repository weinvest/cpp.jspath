#include "location/DotLocationPath.h"
#include "Context.h"
namespace jspath
{
DotLocationPath::DotLocationPath(const std::string& path)
    :LocationPath(path)
{}

void DotLocationPath::doApply(Context& cxt, const json& input)
{
#if 0
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
#else
    if(input.count(getPath()))
    {
        auto& result = input[getPath()];
        if(result.is_array())
        {
            for(auto& child : result)
            {
                cxt.getOutput().push_back(&child);
            }
        }
        else
        {
            cxt.getOutput().push_back(&result);
        }
    }
#endif
}
}

