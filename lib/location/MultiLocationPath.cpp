#include "location/MultiLocationPath.h"
#include "Context.h"
namespace jspath
{
MultiLocationPath::MultiLocationPath()
    :LocationPath("")
{}

void MultiLocationPath::addChild(std::shared_ptr<Expression> pChild)
{
    if(nullptr != pChild)
    {
        mChildren.push_back(pChild);
    }
}

void MultiLocationPath::apply(Context& cxt, const json& variables)
{
    cxt.getOutput() = std::make_shared<json>(json::array());
    for(auto pChild : mChildren)
    {
        auto input = pChild->isAbsolute() ? cxt.getRootInput() : cxt.getInput();
        Context tmpCxt(input, cxt.getRootInput());
        pChild->apply(tmpCxt, variables);
        if(tmpCxt.getOutput()->is_null())
        {}
        else if(tmpCxt.getOutput()->is_array())
        {
            cxt.merge(tmpCxt);
        }
        else
        {
            cxt.getOutput()->push_back(*tmpCxt.getOutput());
        }
    }

    LocationPath::apply(cxt, variables);
}

void MultiLocationPath::doApply(Context &/*cxt*/, const json& /*variable*/)
{
}
}
