#ifndef _JSPATH_CONTEXT_H
#define _JSPATH_CONTEXT_H
#include <vector>
#include <memory>
#include <boost/property_tree/ptree.hpp>
namespace jspath
{
    using boost::property_tree::ptree;
    class Context
    {
    public:
	typedef std::vector<const ptree*> StepContext;
	Context(const ptree& root);

	StepContext& getInput() { return *mStepContexts.back(); }
	StepContext& getOutput() { return *mOutputContext; }
	StepContext& newStep();

	auto& getStepContexts() { return mStepContexts; }

    private:
        std::vector<std::shared_ptr<StepContext>> mStepContexts;
	std::shared_ptr<StepContext> mOutputContext;
    };
}
#endif

