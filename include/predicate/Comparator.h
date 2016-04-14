#ifndef _JSPATH_COMPARATOR_H
#define _JSPATH_COMPARATOR_H
#include <tuple>
#include "predicate/Operand.h"
#include "predicate/BinaryOperator.hpp"
namespace jspath
{

class CompareBase: public BinaryOperator<Operand, Predicate>
{
public:
    typedef std::tuple<Operand::type, Operand::type, Operand::type> CompareAtT;
    CompareAtT compareAt(const Context& cxt, const json& variables);
};

class Equal: public CompareBase
{
public:
    using CompareBase::CompareBase;

    bool eval(const Context& cxt, const json& variables) override;
};

class StrictlyEqual: public CompareBase
{
public:
    using CompareBase::CompareBase;

    bool eval(const Context& cxt, const json& variables) override;
};

class NonEqual: public CompareBase
{
public:
    using CompareBase::CompareBase;

    bool eval(const Context& cxt, const json& variables) override;
};

class StrictlyNonEqual: public CompareBase
{
public:
    using CompareBase::CompareBase;

    bool eval(const Context& cxt, const json& variables) override;
};

class GreatThan: public CompareBase
{
public:
    using CompareBase::CompareBase;
    bool eval(const Context& cxt, const json& variables) override;
};

class GreatEqual: public CompareBase
{
public:
    using CompareBase::CompareBase;
    bool eval(const Context& cxt, const json& variables) override;
};

class LessThan: public CompareBase
{
public:
    using CompareBase::CompareBase;
    bool eval(const Context& cxt, const json& variables) override;
};

class LessEqual: public CompareBase
{
public:
    using CompareBase::CompareBase;
    bool eval(const Context& cxt, const json& variables) override;
};

int Compare(std::shared_ptr<Operand> op1
	, std::shared_ptr<Operand> op2
	, const Context& cxt
	, const json& input
	, Operand::type t);
}
#endif
