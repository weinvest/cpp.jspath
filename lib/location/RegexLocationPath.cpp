#include "location/RegexLocationPath.h"
#include "Context.h"
namespace jspath
{
RegexLocationPath::RegexLocationPath(const std::string& regex)
    :LocationPath(regex)
{
    mPattern = sregex::compile(regex);
}

void RegexLocationPath::doApply(Context& cxt)
{
    using namespace boost::xpressive;
    smatch what;

    auto &input = cxt.getInput();
    if(input->is_object())
    {
        for(auto itChild = input->begin(); itChild != input->end(); ++itChild)
        {
            if(regex_match(itChild.key(), what, mPattern))
            {
                cxt.getOutput()->push_back(itChild.value());
            }
        }//foreach field
    }
    else if(input->is_array())
    {
        for(auto& child : *input)
        {
            for(auto itChild = child.begin(); itChild != child.end(); ++itChild)
            {
                if(regex_match(itChild.key(), what, mPattern))
                {
                    cxt.getOutput()->push_back(itChild.value());
                }
            }
        }//foreach child
    }
}
}//namespace jspath

