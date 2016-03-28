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

void MultiLocationPath::apply(Context& cxt)
{
    for(auto pChild : mChildren)
    {
        if(nullptr == pChild->getSuccessor() && !pChild->isAbsolute())
        {
            pChild->apply(cxt);
        }
        else
        {
            auto input = pChild->isAbsolute() ? cxt.getRootInputPtr() : cxt.getInputPtr();
            Context tmpCxt(input, cxt.getRootInputPtr());
            pChild->apply(tmpCxt);
            cxt.merge(tmpCxt);
        }
    }

    LocationPath::apply(cxt);
}

void MultiLocationPath::doApply(Context &/*cxt*/, const json &/*input*/)
{
}
}
