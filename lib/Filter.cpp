#include "Filter.h"
#include "Context.h"
namespace jspath
{

Filter::Filter(std::shared_ptr<Predicate> predicate):
    mPredicate(predicate)
{}

void Filter::doApply(Context& cxt)
{
//    if( mPredicate->eval(cxt))
//    {
//        cxt.getOutput()->push_back(&input);
//    }
}
}
