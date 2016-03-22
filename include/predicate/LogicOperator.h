#ifndef _JSPATH_LOGIC_OPERATOR_H
#define _JSPATH_LOGIC_OPERATOR_H
#include <memory>
#include "predicate/Predicate.h"
namespace jspath
{
class And: public Predicate
{
public:
    And(std::shared_ptr<Predicate> pred1, std::shared_ptr<Predicate> pred2);
    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Predicate> mChildPred1;
    std::shared_ptr<Predicate> mChildPred2;
};

class Or: public Predicate
{
public:
    Or(std::shared_ptr<Predicate> pred1, std::shared_ptr<Predicate> pred2);
    bool eval(const Context& cxt, const ptree& input) override;

private:
    std::shared_ptr<Predicate> mChildPred1;
    std::shared_ptr<Predicate> mChildPred2;
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

