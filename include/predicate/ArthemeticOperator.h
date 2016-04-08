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
    int getIntValue(const Context& cxt, const json& variables) override;
    double getRealValue(const Context& cxt, const json& variables) override;

private:
    template <typename T>
    T apply(T lhs, T rhs)
    {
        switch(mOperator)
        {
        case OP_Add: return lhs + rhs;
        case OP_Sub: return lhs - rhs;
        case OP_Mul: return lhs * rhs;
        default: return rhs / rhs;
        }
    }

    Operator mOperator;
};

class Add: public ArthemeticOperator
{
public:
    Add();

    bool getBoolValue(const Context& cxt, const json& variables) override;
    const std::string& getStringValue(const Context& cxt, const json& variables) override;

private:
    std::string mTemp;    //ToDO: thread safe
};

class Sub: public ArthemeticOperator
{
public:
    using ArthemeticOperator::ArthemeticOperator;
    Sub();

    bool getBoolValue(const Context& cxt, const json& variables) override;
    const std::string& getStringValue(const Context& cxt, const json& variables) override;
};

class Multiply: public ArthemeticOperator
{
public:
    using ArthemeticOperator::ArthemeticOperator;
    Multiply();

    bool getBoolValue(const Context& cxt, const json& variables) override;
    const std::string& getStringValue(const Context& cxt, const json& variables) override;
};

class Divide: public ArthemeticOperator
{
public:
    using ArthemeticOperator::ArthemeticOperator;
    Divide();

    bool getBoolValue(const Context& cxt, const json& variables) override;
    const std::string& getStringValue(const Context& cxt, const json& variables) override;
};

class Module: public BinaryOperator<Operand, Operand>
{
public:
    Operand::type getType(const Context& cxt, const json& variables) const override;
    bool getBoolValue(const Context& cxt, const json& variables) override;
    int getIntValue(const Context& cxt, const json& variables) override;
    double getRealValue(const Context& cxt, const json& variables) override;
    const std::string& getStringValue(const Context& cxt, const json& variables) override;
};
}
#endif
