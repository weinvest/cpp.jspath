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

    bool eval(const Context& cxt, const json& input) override;
};

class StrictlyEqual: public CompareBase
{
public:
    using CompareBase::CompareBase;

    bool eval(const Context& cxt, const json& input) override;
};

class NonEqual: public CompareBase
{
public:
    using CompareBase::CompareBase;

    bool eval(const Context& cxt, const json& input) override;
};

class StrictlyNonEqual: public CompareBase
{
public:
    using CompareBase::CompareBase;

    bool eval(const Context& cxt, const json& input) override;
};

class GreatThan: public CompareBase
{
public:
    using CompareBase::CompareBase;
    bool eval(const Context& cxt, const json& input) override;
};

class GreatEqual: public CompareBase
{
public:
    using CompareBase::CompareBase;
    bool eval(const Context& cxt, const json& input) override;
};

class LessThan: public CompareBase
{
public:
    using CompareBase::CompareBase;
    bool eval(const Context& cxt, const json& input) override;
};

class LessEqual: public CompareBase
{
public:
    using CompareBase::CompareBase;
    bool eval(const Context& cxt, const json& input) override;
};

int Compare(std::shared_ptr<Operand> op1
	, std::shared_ptr<Operand> op2
	, const Context& cxt
	, const json& input
	, Operand::type t);
}
#endif

