#include "positional/Positional.h"
#include "Context.h"
namespace jspath
{

Positional::Positional(IndexRange range)
    :mRange(range)
{}

void Positional::apply(Context& cxt, const json& variables)
{
    if(!cxt.getInput()->is_array())
    {
        return;
    }


    int size = cxt.getInput()->size();
    int begin = mRange.begin(size);
    int end = mRange.end(size);

    if(!mRange.isRange())
    {
        if(begin >= 0 && begin < size)
        {
            cxt.getOutput() =Context::StepOutput(&(cxt.getInput()->at(begin)), [](void*){});
        }
    }
    else if((begin < end) && (mRange.getStep() > 0))
    {
        for(int iCur = begin; iCur < end && iCur < size; iCur += mRange.getStep())
        {
            cxt.getOutput()->push_back(cxt.getInput()->at(iCur));
        }
    }
    else if((begin > end) && (mRange.getStep() < 0))
    {
        for(int iCur = std::min(begin, size - 1); iCur > end && iCur >= 0; iCur += mRange.getStep())
        {
            cxt.getOutput()->push_back(cxt.getInput()->at(iCur));
        }
    }
    else
    {
        return;
    }

    return Expression::apply(cxt, variables);
}

void Positional::doApply(Context& /*cxt*/, const json& /*variables*/)
{
}
}
