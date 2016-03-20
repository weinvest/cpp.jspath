#include "Context.h"

namespace jspath
{
    Context::Context(const ptree& root)
	:mOutputContext(new StepContext())
    {
	newStep();
        getInput().push_back(&root);
    }

    Context::StepContext& Context::newStep()
    {
	mStepContexts.push_back(mOutputContext);
	mOutputContext.reset(new StepContext);

	return *mOutputContext;
    }
}
