#include "predicate/LogicOperator.h"
namespace jspath
{
bool And::eval(const Context& cxt, const ptree& input)
{
    return mOperand1->eval(cxt, input) && mOperand2->eval(cxt, input);
}

bool Or::eval(const Context& cxt, const ptree& input)
{
    return mOperand1->eval(cxt, input) || mOperand2->eval(cxt, input);
}

Not::Not(std::shared_ptr<Predicate> pred)
    :mChildPred(pred)
{}

bool Not::eval(const Context& cxt, const ptree& input)
{
    return !mChildPred->eval(cxt, input);
}

}
