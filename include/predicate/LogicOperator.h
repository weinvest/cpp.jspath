#ifndef _JSPATH_LOGIC_OPERATOR_H
#define _JSPATH_LOGIC_OPERATOR_H
#include <memory>
#include "predicate/Predicate.h"
#include "predicate/BinaryOperator.hpp"
namespace jspath
{
typedef BinaryOperator<Predicate, Predicate> LogicBase;
class And: public LogicBase
{
public:
    using LogicBase::LogicBase;
    bool eval(const Context& cxt, const ptree& input) override;
};

class Or: public LogicBase
{
public:
    using LogicBase::LogicBase;
    bool eval(const Context& cxt, const ptree& input) override;
};

class Not: public Predicate
{
public:
    Not(std::shared_ptr<Predicate> pred);

    bool  eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Predicate> mChildPred;
};
}
#endif

