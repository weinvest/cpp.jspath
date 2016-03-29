#include "Context.h"

namespace jspath
{
Context::Context(const json& root)
    :mOutputContext(std::allocate_shared<json>(mAllocator))
{
    mStepContexts.emplace_back(const_cast<json*>(&root), [](void*){});
    mRootInputContext = getInput();
}

Context::Context(StepInput input, StepInput rootInput)
    :mOutputContext(std::allocate_shared<json>(mAllocator))
{
    mStepContexts.push_back(input);

    if(nullptr == rootInput)
    {
        mRootInputContext = getInput();
    }
    else
    {
        mRootInputContext = rootInput;
    }
}

Context::StepOutput& Context::newStep()
{
    mStepContexts.push_back(mOutputContext);
    mOutputContext = std::allocate_shared<json>(mAllocator);

    return mOutputContext;
}

void Context::merge(const Context& other)
{
    getOutput()->insert(getOutput()->end(), other.getOutput()->begin(), other.getOutput()->end());
}
}
