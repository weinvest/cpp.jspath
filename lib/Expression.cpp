#include "Expression.h"

namespace jspath
{
void Expression::setSuccessor(std::shared_ptr<Expression> pSuccessor)
{
    mSuccessor = pSuccessor;
}

void Expression::apply(Context &cxt)
{
    doApply(cxt);
    if(nullptr != mSuccessor)
    {
        mSuccessor->apply(cxt);
    }
}
}
