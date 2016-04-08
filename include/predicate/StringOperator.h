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
    bool eval(const Context& cxt, const json& variables) override;
};

class InsensitiveEqual: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& variables) override;
};

class StartsWith: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& variables) override;
};

class InsensitiveStartsWith: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& variables) override;
};

class EndsWith: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& variables) override;
};

class InsensitiveEndsWith: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& variables) override;
};

class Contains: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& variables) override;
};

class InsensitiveContains: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& variables) override;
};

class Match: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& variables) override;
};

class InsensitiveMatch: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& variables) override;
};

class NonMatch: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& variables) override;
};

class InsensitiveNonMatch: public StringOperator
{
public:
    using StringOperator::StringOperator;
    bool eval(const Context& cxt, const json& variables) override;
};
}
#endif
