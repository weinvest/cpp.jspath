#include "predicate/LogicOperator.h"
namespace jspath
{
And::And(std::shared_ptr<Predicate> pred1, std::shared_ptr<Predicate> pred2)
    :mChildPred1(pred1)
    ,mChildPred2(pred2)
{}

bool And::eval(const Context& cxt, const ptree& input)
{
    return mChildPred1->eval(cxt, input) && mChildPred2->eval(cxt, input);
}

Or::Or(std::shared_ptr<Predicate> pred1, std::shared_ptr<Predicate> pred2)
    :mChildPred1(pred1)
    ,mChildPred2(pred2)
{}

bool Or::eval(const Context& cxt, const ptree& input)
{
    return mChildPred1->eval(cxt, input) || mChildPred2->eval(cxt, input);
}

Not::Not(std::shared_ptr<Predicate> pred)
    :mChildPred(pred)
{}

bool Not::eval(const Context& cxt, const ptree& input)
{
    return !mChildPred->eval(cxt, input);
}

}
