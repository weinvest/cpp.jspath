#include <boost/algorithm/string/predicate.hpp>
#include "predicate/Comparator.h"
namespace jspath
{

//=================================equal==============================
Equal::Equal(std::shared_ptr<Operand> pOperand1, std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

bool Equal::eval(const Context &cxt, const boost::property_tree::ptree &input)
{
    return false;
}

//=================================strictly equal==============================
StrictlyEqual::StrictlyEqual(std::shared_ptr<Operand> pOperand1, std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

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
NonEqual::NonEqual(std::shared_ptr<Operand> pOperand1, std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

bool NonEqual::eval(const Context &cxt, const boost::property_tree::ptree &input)
{
    return false;
}

//=================================strictly non equal==============================
StrictlyNonEqual::StrictlyNonEqual(std::shared_ptr<Operand> pOperand1, std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

bool StrictlyNonEqual::eval(const Context &cxt, const boost::property_tree::ptree &input)
{
    return false;
}

//=================================great than==============================
GreatThan::GreatThan(std::shared_ptr<Operand> pOperand1, std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

bool GreatThan::eval(const Context &cxt, const boost::property_tree::ptree &input)
{
    return false;
}

//=================================great equal==============================
GreatEqual::GreatEqual(std::shared_ptr<Operand> pOperand1, std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

bool GreatEqual::eval(const Context &cxt, const boost::property_tree::ptree &input)
{
    return false;
}

//=================================less than ==============================
LessThan::LessThan(std::shared_ptr<Operand> pOperand1, std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

bool LessThan::eval(const Context &cxt, const boost::property_tree::ptree &input)
{
    return false;
}

//=================================less equal ==============================
LessEqual::LessEqual(std::shared_ptr<Operand> pOperand1, std::shared_ptr<Operand> pOperand2)
    :mOperand1(pOperand1)
    ,mOperand2(pOperand2)
{}

bool LessEqual::eval(const Context &cxt, const boost::property_tree::ptree &input)
{
    return false;
}
}
