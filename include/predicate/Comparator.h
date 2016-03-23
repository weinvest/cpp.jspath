#ifndef _JSPATH_COMPARATOR_H
#define _JSPATH_COMPARATOR_H

#include "predicate/Operand.h"
#include "predicate/BinaryOperator.hpp"
namespace jspath
{

typedef BinaryOperator<Operand, Predicate> CompareBase;
class Equal: public CompareBase
{
public:
    using CompareBase::CompareBase;

    bool eval(const Context& cxt, const ptree& input) override;
};

class StrictlyEqual: public CompareBase
{
public:
    using CompareBase::CompareBase;

    bool eval(const Context& cxt, const ptree& input) override;
};

class NonEqual: public CompareBase
{
public:
    using CompareBase::CompareBase;

    bool eval(const Context& cxt, const ptree& input) override;
};

class StrictlyNonEqual: public CompareBase
{
public:
    using CompareBase::CompareBase;

    bool eval(const Context& cxt, const ptree& input) override;
};

class GreatThan: public CompareBase
{
public:
    using CompareBase::CompareBase;
    bool eval(const Context& cxt, const ptree& input) override;
};

class GreatEqual: public CompareBase
{
public:
    using CompareBase::CompareBase;
    bool eval(const Context& cxt, const ptree& input) override;
};

class LessThan: public CompareBase
{
public:
    using CompareBase::CompareBase;
    bool eval(const Context& cxt, const ptree& input) override;
};

class LessEqual: public CompareBase
{
public:
    using CompareBase::CompareBase;
    bool eval(const Context& cxt, const ptree& input) override;
};

int Compare(std::shared_ptr<Operand> op1
	, std::shared_ptr<Operand> op2
	, const Context& cxt
	, const ptree& input
	, Operand::type t);
}
#endif

