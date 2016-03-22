#ifndef JSPATH_ARTHEMETIC_OPERATOR_H
#define JSPATH_ARTHEMETIC_OPERATOR_H
#include "predicate/Operand.h"
#include "predicate/BinaryOperator.hpp"
namespace jspath
{
typedef BinaryOperator<Operand, Operand> ArthemeticOperator;
class Add: public ArthemeticOperator
{
public:
    using ArthemeticOperator::ArthemeticOperator;

    double getNumericValue(const Context& cxt, const ptree& input, bool convert) override;
    std::string getStringValue(const Context& cxt, const ptree& input, bool convert) override;
};

class Sub: public ArthemeticOperator
{
public:
    using ArthemeticOperator::ArthemeticOperator;

    double getNumericValue(const Context& cxt, const ptree& input, bool convert) override;
    std::string getStringValue(const Context& cxt, const ptree& input, bool convert) override;
};

class Multiply: public ArthemeticOperator
{
public:
    using ArthemeticOperator::ArthemeticOperator;

    double getNumericValue(const Context& cxt, const ptree& input, bool convert) override;
    std::string getStringValue(const Context& cxt, const ptree& input, bool convert) override;
};

class Divide: public ArthemeticOperator
{
public:
    using ArthemeticOperator::ArthemeticOperator;

    double getNumericValue(const Context& cxt, const ptree& input, bool convert) override;
    std::string getStringValue(const Context& cxt, const ptree& input, bool convert) override;
};

class Module: public ArthemeticOperator
{
public:
    using ArthemeticOperator::ArthemeticOperator;

    double getNumericValue(const Context& cxt, const ptree& input, bool convert) override;
    std::string getStringValue(const Context& cxt, const ptree& input, bool convert) override;
};
}
#endif

