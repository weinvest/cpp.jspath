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
    cxt.getOutput() = std::make_shared<json>(json::array());
    smatch what;

    auto &input = cxt.getInput();
    if(input->is_primitive())
    {}
    else if(input->is_object())
    {
        for(auto itChild = input->begin(); itChild != input->end(); ++itChild)
        {
            if(regex_match(itChild.key(), what, mPattern))
            {
                add2(cxt, itChild.value());
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
                    add2(cxt, itChild.value());
                }
            }
        }//foreach child
    }
}

void RegexLocationPath::add2(Context& cxt, json& ele)
{
    if(ele.is_array())
    {
        cxt.getOutput()->insert(cxt.getOutput()->end(), ele.begin(), ele.end());
    }
    else
    {
        cxt.getOutput()->push_back(ele);
    }
}
}//namespace jspath

