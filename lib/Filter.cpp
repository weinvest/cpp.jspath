#include "Filter.h"
#include "Context.h"
namespace jspath
{

Filter::Filter(std::shared_ptr<Predicate> predicate):
    mPredicate(predicate)
{}

void Filter::doApply(Context& cxt, const json& variables)
{
    for(auto& child : *cxt.getInput())
    {
        try
        {
            Context tmpCxt(child, cxt.getRootInput());
            if( mPredicate->eval(tmpCxt, variables))
            {
                cxt.getOutput()->push_back(child);
            }
        }
        catch(...)
        {
            //if eval throw an exception, child will be filtered
        }
    }
}
}
