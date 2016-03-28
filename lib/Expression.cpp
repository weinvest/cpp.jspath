#include "Expression.h"
#include "Context.h"
namespace jspath
{
Expression::Expression(bool isAbsolute)
    :mIsAbsolute(isAbsolute)
{}

void Expression::setSuccessor(std::shared_ptr<Expression> pSuccessor)
{
    mSuccessor = pSuccessor;
}

void Expression::apply(Context &cxt)
{
    for(auto pInput : cxt.getInput())
    {
        doApply(cxt, *pInput);
    }

    if(nullptr != mSuccessor && !cxt.getOutput().empty())
    {
        cxt.newStep();
        mSuccessor->apply(cxt);
    }
}
}
