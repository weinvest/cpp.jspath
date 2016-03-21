#include "Filter.h"
#include "Context.h"
namespace jspath
{

void Filter::doApply(Context& cxt, const ptree& input)
{
    //if( (input))
    {
        cxt.getOutput().push_back(&input);
    }
}
}
