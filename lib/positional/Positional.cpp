#include "positional/Positional.h"
#include "Context.h"
namespace jspath
{

Positional::Positional(IndexRange range)
    :mRange(range)
{}

void Positional::apply(Context& cxt)
{
    int begin = mRange.begin(cxt.getInput().size());
    int end = mRange.end(cxt.getInput().size());

    if(begin < end)
    {
        for(int iCur = begin; iCur != end; ++iCur)
        {
            cxt.getOutput().push_back(cxt.getInput()[iCur]);
        }
    }
}

void Positional::doApply(Context& cxt, const json& input)
{
    int begin = mRange.begin(input.size());
    int end = mRange.end(input.size());

    if(begin < end)
    {
        static auto walk2 = [](const json& input, int begin)
        {
            auto itCur = input.begin();
            while(0 != (begin--))
            {
                ++itCur;
            }
            return itCur;
        };

        int count = end - begin;
        int curCount = 0;
        for(auto itCur = walk2(input, begin); curCount < count && itCur != input.end(); ++itCur, ++curCount)
        {
            cxt.getOutput().push_back(&(itCur.value()));
        }
    }
}
}
