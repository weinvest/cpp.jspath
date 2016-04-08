#include "predicate/LogicOperator.h"
namespace jspath
{
bool And::eval(const Context& cxt, const json& variables)
{
    return mOperand1->eval(cxt, variables) && mOperand2->eval(cxt, variables);
}

bool Or::eval(const Context& cxt, const json& variables)
{
    return mOperand1->eval(cxt, variables) || mOperand2->eval(cxt, variables);
}

Not::Not(std::shared_ptr<Predicate> pred)
    :mChildPred(pred)
{}

bool Not::eval(const Context& cxt, const json& variables)
{
    return !mChildPred->eval(cxt, variables);
}

}
