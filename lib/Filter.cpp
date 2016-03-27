#include "Filter.h"
#include "Context.h"
namespace jspath
{

Filter::Filter(std::shared_ptr<Predicate> predicate):
    mPredicate(predicate)
{}

void Filter::doApply(Context& cxt, const json& input)
{
    if( mPredicate->eval(cxt, input))
    {
        cxt.getOutput().push_back(&input);
    }
}
}
