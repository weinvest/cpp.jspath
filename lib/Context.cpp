#include "Context.h"

namespace jspath
{
Context::Context(const ptree& root)
    :mOutputContext(new StepContext())
{
    newStep();
    getInput().push_back(&root);
    mRootInputContext = mStepContexts.front();
}

Context::Context(std::shared_ptr<StepContext> input, std::shared_ptr<StepContext> rootInput)
    :mOutputContext(new StepContext())
{
    mStepContexts.push_back(input);

    if(nullptr == rootInput)
    {
        mRootInputContext = getInputPtr();
    }
    else
    {
        mRootInputContext = rootInput;
    }
}

Context::StepContext& Context::newStep()
{
    mStepContexts.push_back(mOutputContext);
    mOutputContext.reset(new StepContext);

    return *mOutputContext;
}

void Context::merge(const Context& other)
{
    getOutput().insert(getOutput().end(), other.getOutput().cbegin(), other.getOutput().cend());
}
}
