#include "positional/Positional.h"
#include "Context.h"
namespace jspath
{

Positional::Positional(IndexRange range)
    :mRange(range)
{}

void Positional::apply(Context& cxt)
{
    auto size = cxt.getInput().size();
    int begin = mRange.begin(size);
    int end = mRange.end(size);

    if((begin < end) && (mRange.getStep() > 0))
    {
        for(int iCur = begin; iCur < end && iCur < size; iCur += mRange.getStep())
        {
            cxt.getOutput().push_back(cxt.getInput()[iCur]);
        }
    }
    else if((begin > end) && (mRange.getStep() < 0))
    {
        for(int iCur = begin; iCur > end && iCur >= 0; iCur += mRange.getStep())
        {
            cxt.getOutput().push_back(cxt.getInput()[iCur]);
        }
    }
}

void Positional::doApply(Context& cxt, const json& input)
{
}
}
