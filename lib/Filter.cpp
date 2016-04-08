#include "Filter.h"
#include "Context.h"
namespace jspath
{

Filter::Filter(std::shared_ptr<Predicate> predicate):
    mPredicate(predicate)
{}

void Filter::doApply(Context& cxt, const json& variables)
{
   if( mPredicate->eval(cxt, variables))
   {
       cxt.getOutput()->push_back(&variables);
   }
}
}
