#ifndef _JSPATH_STRING_OPERATOR_H
#define _JSPATH_STRING_OPERATOR_H
#include "predicate/Predicate.h"
#include "predicate/Operand.h"
#include "predicate/BinaryOperator.hpp"
namespace jspath
{

typedef BinaryOperator<Operand, Predicate> StringOperator;
class SensitiveEqual: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& input) override;
};

class InsensitiveEqual: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& input) override;
};

class StartsWith: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& input) override;
};

class InsensitiveStartsWith: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& input) override;
};

class EndsWith: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& input) override;
};

class InsensitiveEndsWith: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& input) override;
};

class Contains: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& input) override;
};

class InsensitiveContains: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& input) override;
};
}
#endif

