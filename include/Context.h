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

        Context(std::shared_ptr<StepContext> input, std::shared_ptr<StepContext> rootInput = nullptr);

        const StepContext& getInput() const { return *mStepContexts.back(); }
        const StepContext& getOutput() const { return *mOutputContext; }
        const StepContext& getRootInput() const { return *mRootInputContext; }

        StepContext& getInput() { return *mStepContexts.back(); }
        StepContext& getOutput() { return *mOutputContext; }
        StepContext& getRootInput() { return *mRootInputContext; }

	StepContext& newStep();

	auto& getStepContexts() { return mStepContexts; }

        auto getInputPtr() { return mStepContexts.back(); }
        auto getOutputPtr() { return mOutputContext; }
        auto getRootInputPtr() { return mRootInputContext; }

        void merge(const Context& other);
    private:
        Context(const Context&) = delete;

        std::vector<std::shared_ptr<StepContext>> mStepContexts;
        std::shared_ptr<StepContext> mRootInputContext;
	std::shared_ptr<StepContext> mOutputContext;
    };
}
#endif

