#include "location/RootLocationPath.h"
#include "Context.h"
namespace jspath
{
RootLocationPath::RootLocationPath()
    :LocationPath("")
{}

void RootLocationPath::doApply(Context& cxt, const json& variables)
{
    *cxt.getOutput() = *cxt.getInput();
}
}
