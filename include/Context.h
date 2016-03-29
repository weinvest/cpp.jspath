#ifndef _JSPATH_CONTEXT_H
#define _JSPATH_CONTEXT_H
#include <vector>
#include <memory>
#include "json.hpp"
namespace jspath
{
using nlohmann::json;
class Context
{
public:
    typedef std::shared_ptr<json> StepInput;
    typedef std::shared_ptr<json> StepOutput;

    Context(const json& root);

    Context(StepInput input, StepInput rootInput = nullptr);

    const StepInput& getInput() const { return mStepContexts.back(); }
    const StepOutput& getOutput() const { return mOutputContext; }
    const StepInput& getRootInput() const { return mRootInputContext; }

    StepInput& getInput() { return mStepContexts.back(); }
    StepOutput& getOutput() { return mOutputContext; }
    StepInput& getRootInput() { return mRootInputContext; }

    StepOutput& newStep();

    auto& getStepContexts() { return mStepContexts; }

    void merge(const Context& other);
private:
    Context(const Context&) = delete;

    std::allocator<json> mAllocator;
    std::vector<StepInput> mStepContexts;
    StepInput mRootInputContext;
    StepOutput mOutputContext;
};
}
#endif

