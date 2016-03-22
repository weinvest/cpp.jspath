#include <boost/algorithm/string/predicate.hpp>
#include "predicate/Comparator.h"
namespace jspath
{

//=================================equal==============================
bool Equal::eval(const Context &cxt, const boost::property_tree::ptree &input)
{
    return false;
}

//=================================strictly equal==============================
bool StrictlyEqual::eval(const Context &cxt, const boost::property_tree::ptree &input)
{
    if(mOperand1->getType() != mOperand2->getType()
      && Operand::Location != mOperand1->getType()
      && Operand::Location != mOperand2->getType())
    {
        return false;
    }

    switch(mOperand1->getType())
    {
    case Operand::Numeric:
        break;
    case Operand::String:
    {
        auto str1 = mOperand1->getStringValue(cxt, input);
        auto str2 = mOperand2->getStringValue(cxt, input);
        return boost::algorithm::equals(str1, str2);
    }
    case Operand::Location:
    {

    }
    }

    return false;
}

//=================================non equal==============================
bool NonEqual::eval(const Context &cxt, const boost::property_tree::ptree &input)
{
    return false;
}

//=================================strictly non equal==============================
bool StrictlyNonEqual::eval(const Context &cxt, const boost::property_tree::ptree &input)
{
    return false;
}

//=================================great than==============================
bool GreatThan::eval(const Context &cxt, const boost::property_tree::ptree &input)
{
    return false;
}

//=================================great equal==============================
bool GreatEqual::eval(const Context &cxt, const boost::property_tree::ptree &input)
{
    return false;
}

//=================================less than ==============================
bool LessThan::eval(const Context &cxt, const boost::property_tree::ptree &input)
{
    return false;
}

//=================================less equal ==============================
bool LessEqual::eval(const Context &cxt, const boost::property_tree::ptree &input)
{
    return false;
}
}
