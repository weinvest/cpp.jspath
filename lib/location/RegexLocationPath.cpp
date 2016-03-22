#include "location/RegexLocationPath.h"
#include "Context.h"
namespace jspath
{
RegexLocationPath::RegexLocationPath(const std::string& regex)
    :LocationPath(regex)
{
    mPattern = sregex::compile(regex);
}

void RegexLocationPath::doApply(Context& cxt, const ptree& input)
{
    using namespace boost::xpressive;
    smatch what;

    for(const auto& child : input)
    {
        if(regex_match(child.first, what, mPattern))
        {
            cxt.getOutput().push_back(&child.second);
        }
    }//foreach child
}
}//namespace jspath

