#ifndef JSPATH_ARTHEMETIC_OPERATOR_H
#define JSPATH_ARTHEMETIC_OPERATOR_H
#include "predicate/Operand.h"
#include "predicate/BinaryOperator.hpp"
namespace jspath
{

class Add: public BinaryOperator<Operand, Operand>
{
public:
    using BinaryOperator<Operand, Operand>::BinaryOperator;

    double getNumericValue(const Context& cxt, const ptree& input, bool convert) override;
    std::string getStringValue(const Context& cxt, const ptree& input, bool convert) override;

};
}
#endif

