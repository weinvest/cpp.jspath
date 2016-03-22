#ifndef _JSPATH_OPERAND_H
#define _JSPATH_OPERAND_H
#include "Predicate.h"
namespace jspath
{
class Operand: public Predicate
{
public:
    virtual ~Operand();

    virtual double getNumericValue(const Context& cxt, const ptree& input, bool convert = false);
    virtual std::string getStringValue(const Context& cxt, const ptree& input, bool convert = false);
};

class NumericOperand: public Operand
{
public:
   NumericOperand(); 
};

class StringOperand: public Operand
{
public:
};
}
#endif

