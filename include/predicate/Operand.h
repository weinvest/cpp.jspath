#ifndef _JSPATH_OPERAND_H
#define _JSPATH_OPERAND_H
#include "Predicate.h"
namespace jspath
{
class Operand: public Predicate
{
public:
    enum type
    {
        Numeric,
        String,
        Array,
        Location,
        Other
    };

    Operand(type t);
    virtual ~Operand();

    virtual double getNumericValue(const Context& cxt, const ptree& input, bool convert = false);
    virtual std::string getStringValue(const Context& cxt, const ptree& input, bool convert = false);

    type getType() const { return mType; }
private:
    type mType;
};

class NumericOperand: public Operand
{
public:
   NumericOperand(); 
};

class StringOperand: public Operand
{
public:
    StringOperand();
};

class ArrayOperand: public Operand
{
public:
    ArrayOperand();
};

class LocationOperand: public Operand
{
public:
    LocationOperand();
};


}
#endif

