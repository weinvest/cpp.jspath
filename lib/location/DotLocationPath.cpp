#include <boost/algorithm/string.hpp>
#include "location/DotLocationPath.h"
#include "Context.h"
namespace jspath
{
DotLocationPath::DotLocationPath(const std::string& path)
    :LocationPath(boost::trim_copy(path))
{}

void DotLocationPath::doApply(Context& cxt, const json& input)
{
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
}
}

