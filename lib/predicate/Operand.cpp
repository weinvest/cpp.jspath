#include "predicate/Operand.h"

namespace jspath
{
Operand::Operand(type t)
    :mType(t)
{}

NumericOperand::NumericOperand()
    :Operand(Operand::Numeric)
{}

StringOperand::StringOperand()
    :Operand(Operand::String)
{}

ArrayOperand::ArrayOperand()
    :Operand(Operand::Array)
{}

LocationOperand::LocationOperand()
    :Operand(Operand::Location)
{}

}
