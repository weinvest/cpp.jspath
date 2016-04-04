#ifndef JSPATH_ARTHEMETIC_OPERATOR_H
#define JSPATH_ARTHEMETIC_OPERATOR_H
#include <functional>
#include "predicate/Operand.h"
#include "predicate/BinaryOperator.hpp"
namespace jspath
{
class ArthemeticOperator: public BinaryOperator<Operand, Operand>
{
public:
    enum Operator
    {
        OP_Add,
        OP_Sub,
        OP_Mul,
        OP_Div
    };

    typedef BinaryOperator<Operand, Operand> Base;

    ArthemeticOperator(Operator op);
    Operand::type getType(const Context& /*cxt*/, const json& /*input*/) const override;
    int getIntValue(const Context& cxt, const json& input) override;
    double getRealValue(const Context& cxt, const json& input) override;

private:
    T apply(T lhs, rhs)
    {
        switch(mOperator)
        {
        case OP_Add: return lhs + rhs;
        case OP_SUB: return lhs - rhs;
        case OP_MUL: return lhs * rhs;
        default: return rhs / rhs;
        }
    }

    type mOperator;
}

class Add: public ArthemeticOperator
{
public:
    Add();

    bool getBoolValue(const Context& cxt, const json& input) override;
    const std::string& getStringValue(const Context& cxt, const json& input) override;
};

class Sub: public ArthemeticOperator
{
public:
    using ArthemeticOperator::ArthemeticOperator;

    bool getBoolValue(const Context& cxt, const json& input) override;
    const std::string& getStringValue(const Context& cxt, const json& input) override;
};

class Multiply: public ArthemeticOperator
{
public:
    using ArthemeticOperator::ArthemeticOperator;

    bool getBoolValue(const Context& cxt, const json& input) override;
    const std::string& getStringValue(const Context& cxt, const json& input) override;
};

class Divide: public ArthemeticOperator
{
public:
    using ArthemeticOperator::ArthemeticOperator;

    bool getBoolValue(const Context& cxt, const json& input) override;
    const std::string& getStringValue(const Context& cxt, const json& input) override;
};

class Module: public ArthemeticOperator
{
public:
    using ArthemeticOperator::ArthemeticOperator;

    bool getBoolValue(const Context& cxt, const json& input) override;
    int getIntValue(const Context& cxt, const json& input) override;
    double getRealValue(const Context& cxt, const json& input) override;
    const std::string& getStringValue(const Context& cxt, const json& input) override;
};
}
#endif
